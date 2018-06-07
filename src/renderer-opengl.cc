/**
 * @file
 * Renderer definition file.
 */

#include "renderer-opengl.h"
#include "asset/resource.h"
#include "asset/collada.h"

namespace cuttlefish
{
  Renderer::Renderer()
  {
    {
      std::cout << "SDL running on platform: " << SDL_GetPlatform() << std::endl;

      SDL_version compiled;
      SDL_version linked;
      
      SDL_VERSION(&compiled);
      SDL_GetVersion(&linked);
      
      std::cout << (boost::format("Compiled against SDL version %1%.%2%.%3%.")
                    // All structure members are of Uint8 type.
                    % static_cast<std::uint16_t>(compiled.major)
                    % static_cast<std::uint16_t>(compiled.minor)
                    % static_cast<std::uint16_t>(compiled.patch)) << std::endl;
      std::cout << (boost::format("Linking against SDL version %1%.%2%.%3%.")
                    % static_cast<std::uint16_t>(linked.major)
                    % static_cast<std::uint16_t>(linked.minor)
                    % static_cast<std::uint16_t>(linked.patch)) << std::endl;
    }

    uint32_t init_flags = SDL_INIT_VIDEO
      | SDL_INIT_AUDIO
      | SDL_INIT_EVENTS
      | SDL_INIT_TIMER;
    if (SDL_Init(init_flags) != 0) {
      std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
      std::exit(1);
    }

    // @TODO Get current display, somehow.
    int displayIndex = 0; // SDL_GetWindowDisplayIndex(window);
    if (displayIndex < 0) {
      std::cerr << "SDL_GetWindowDisplayIndex Error: " << SDL_GetError() << std::endl;
      SDL_Quit();
      std::exit(1);
    }

    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(displayIndex, &dm) != 0) {
      std::cerr << "SDL_GetDesktopDisplayMode Error: " << SDL_GetError();
      SDL_Quit();
      std::exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    uint32_t window_flags = SDL_WINDOW_OPENGL
      // | SDL_WINDOW_BORDERLESS
      // | SDL_WINDOW_FULLSCREEN_DESKTOP
      ;
    window = SDL_CreateWindow("Cuttlefish Pre-Alpha",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    600, 400,
                                    // dm.w,
                                    // dm.h,
                                    window_flags);
    if (window == nullptr) {
      std::cerr << "SDL_CreateWindow Error: " << SDL_GetError();
      SDL_Quit();
      std::exit(1);
    }

    glcontext = SDL_GL_CreateContext(window);
    if (glcontext == nullptr) {
      std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError();
      SDL_DestroyWindow(window);
      SDL_Quit();
      std::exit(1);
    }
    // @TODO Use SDL_GL_SetSwapInterval() to set vsync.

    // Set generic colors.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    CheckForErrors("during general setup");

    // String imagePath = asset::getResourcePath() + "screen-test.bmp";

    LoadShaders();
    LoadMesh();
  };

  void Renderer::LoadShaders()
  {
    String path {}, source {};
    int success {};
    
    // Load simple vertext shader.
    {
      path = asset::getResourcePath("shaders") + "simple.vert";
      std::ifstream file {path};
      file.seekg(0, std::ios::end);   
      source.reserve(file.tellg());
      file.seekg(0, std::ios::beg);
      source.assign((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
      
      simpleVertexShader = glCreateShader(GL_VERTEX_SHADER);
      const char* cp {source.c_str()};
      glShaderSource(simpleVertexShader, 1, &cp, NULL);
      glCompileShader(simpleVertexShader);
      // Verify the shader compiled successfully.
      glGetShaderiv(simpleVertexShader, GL_COMPILE_STATUS, &success);
      if (!success) {
        std::array<char, 1024> error_msg {};
        glGetShaderInfoLog(simpleVertexShader, error_msg.size(), NULL, &error_msg[0]);
        std::cerr << "Failed to compile shader: " << path << std::endl;
        std::cerr << "\tError: " << &error_msg[0] << std::endl;
      }
      CheckForErrors("loading vertex shaders");
    }
    
    // Load white pixel shader.
    {
      path = asset::getResourcePath("shaders") + "white.frag";
      std::ifstream file {path};
      file.seekg(0, std::ios::end);   
      source.reserve(file.tellg());
      file.seekg(0, std::ios::beg);
      source.assign((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());

      whiteFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      const char* cp {source.c_str()};
      glShaderSource(whiteFragmentShader, 1, &cp, NULL);
      glCompileShader(whiteFragmentShader);
      // Verify the shader compiled successfully.
      glGetShaderiv(whiteFragmentShader, GL_COMPILE_STATUS, &success);
      if (!success) {
        std::array<char, 1024> error_msg {};
        glGetShaderInfoLog(whiteFragmentShader, error_msg.size(), NULL, &error_msg[0]);
        std::cerr << "Failed to compile shader: " << path << std::endl;
        std::cerr << "\tError: " << &error_msg[0] << std::endl;
      }
      CheckForErrors("loading fragment shaders");
    }

    // Setup shader program.
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, simpleVertexShader);
    glAttachShader(shaderProgram, whiteFragmentShader);
    glLinkProgram(shaderProgram);
    // Vefiry shader program was linked.
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      std::array<char, 1024> error_msg {};
      glGetProgramInfoLog(whiteFragmentShader, error_msg.size(), NULL, &error_msg[0]);
      std::cerr << "Failed to linking shader program: " << std::endl;
      std::cerr << "\tError: " << &error_msg[0] << std::endl;
    }    
    CheckForErrors("linking shader program");
  }
  
  void Renderer::LoadMesh()
  {
        // Prepare the mesh to be displayed.
    mesh = asset::collada::getMeshFromResource("cube.dae");

    // for (int i = 0; mesh.vertices.size() > i; i++) {
    //   if ((i+1) % 3 == 0) {
    //     mesh.vertices[i] -= 2.0;
    //   }
    // }
    
    #ifdef DEBUG
    debugPrintMesh(mesh);
    #endif

    // Generate a vertex array.
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Setup vertex buffer.
    glGenBuffers(1, &vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.vertices[0]) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

    CheckForErrors("loading cube mesh into VBO");
    
    // Setup index buffer.
    glGenBuffers(1, &ibuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.vertIndices[0]) * mesh.vertIndices.size(), mesh.vertIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
		    Mesh::faceVertCount * sizeof(mesh.vertices[0]),       // stride
			(void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    CheckForErrors("loading cube mesh into video memory");
  }

  void Renderer::DrawExample()
  {
    // Draw to backbuffer.
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertIndices.size());
    
    glBindVertexArray(0);

    CheckForErrors("rendering a frame before flushing");

    glFlush();
  };

  void Renderer::Render() {
    DrawExample();
    // Present the backbuffer, removing the previous one from screen.
    SDL_GL_SwapWindow(window);
    // Clear backbuffer.
    // SDL_RenderClear(renderer);
  };
  
  void Renderer::WindowMinimize()
  {
    SDL_MinimizeWindow(window);
  };

  void Renderer::WindowFullscreen()
  {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  };
  
  Renderer::~Renderer()
  {
    std::cout << "Renderer: shutdown SDL." << std::endl;

    glDeleteBuffers(1, &vbuffer);
    glDeleteBuffers(1, &ibuffer);

    glDeleteShader(simpleVertexShader);
    glDeleteShader(whiteFragmentShader);
    
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
  };

  /**
   *  Created on: 2014/10/19
   *      Author: Dimitri Kourkoulis
   *     License: BSD 3-Clause License (see LICENSE file)
   */
  void Renderer::CheckForErrors(const String when) const {
    GLenum errorCode = glGetError();
    if (errorCode != GL_NO_ERROR) {
      std::cerr << "OpenGL error while " << when << std::endl;
      do {
        std::cerr << ErrorToString(errorCode) << std::endl;
        errorCode = glGetError();
      }
      while (errorCode != GL_NO_ERROR);
    }
  }
  
  /**
   * Convert error enum returned from OpenGL to a readable string error message.
   * @param error The error code returned from OpenGL
   *
   *  Created on: 2014/10/19
   *      Author: Dimitri Kourkoulis
   *     License: BSD 3-Clause License (see LICENSE file)
   */
  String Renderer::ErrorToString(GLenum error) const {
    String errorString;
    
    switch (error) {
    case GL_NO_ERROR:
      errorString = "GL_NO_ERROR: No error has been recorded. "
	"The value of this symbolic constant is guaranteed to be 0.";
      break;
    case GL_INVALID_ENUM:
      errorString = "GL_INVALID_ENUM: An unacceptable value is specified for "
	"an enumerated argument. The offending command is ignored and has no "
	"other side effect than to set the error flag.";
      break;
    case GL_INVALID_VALUE:
      errorString = "GL_INVALID_VALUE: A numeric argument is out of range. "
	"The offending command is ignored and has no other side effect than "
	"to set the error flag.";
      break;
    case GL_INVALID_OPERATION:
      errorString = "GL_INVALID_OPERATION: The specified operation is not "
	"allowed in the current state. The offending command is ignored "
	"and has no other side effect than to set the error flag.";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      errorString = "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer "
	"object is not complete. The offending command is ignored and has "
	"no other side effect than to set the error flag.";
      break;
    case GL_OUT_OF_MEMORY:
      errorString = "GL_OUT_OF_MEMORY: There is not enough memory left to "
	"execute the command. The state of the GL is undefined, except for "
	"the state of the error flags, after this error is recorded.";
      break;
    case GL_STACK_UNDERFLOW:
      errorString = "GL_STACK_UNDERFLOW: An attempt has been made to perform "
	"an operation that would cause an internal stack to underflow.";
      break;
    case GL_STACK_OVERFLOW:
      errorString = "GL_STACK_OVERFLOW: An attempt has been made to perform "
	"an operation that would cause an internal stack to overflow.";
      break;
    default:
      errorString = "Unknown error";
      break;
    }
    return errorString;
  }
}
