/*
 * File std.h
 *
 * Standard template library header files.
 *
 *  Created on: Dec 27, 2013
 *      Author: Plamen Ivanov
 */

// TODO: During configuration, move this file from the includes directory
//       to a non-source directory, replacing it with a file of the same
//       name with a single '#error' preprocessor macro. Only do this if
//       the currently used compiler is GCC and can support PCHs.
//       See 3.20 Using Precompiled Headers of the GCC manual.

#ifndef STD_H_
#define STD_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// C++ STD headers.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
//#include <cinttypes>
#include <iterator>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <locale>
#include <stdexcept>
#include <typeinfo>

// OpenGL headers.
#if defined(HAVE_WINDOWS_H) && defined(_WIN32)
  #include <windows.h>
#endif

// SDL will take care of OS specific OpenGL headers.
// However, we still need to declare what version we'll need.
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
/* #ifdef HAVE_GL_GL_H */
/*   #include <GL/gl.h> */
/*   #include <GL/glext.h> */
/* #elif defined(HAVE_OPENGL_GL_H) */
/*   #include <OpenGL/gl.h> */
/*   #include <OpenGL/glext.h> */
/* #else */
/*   #error no gl.h */
/* #endif */

// OS specific headers.
#ifdef OS_WINDOWS
// Windows specific headers.
#include <windows.h>
#elif OS_LINUX
#include <unistd.h>
#endif

// Boost headers.
#include <boost/utility/string_view.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

// SDL2 headers.
#include <SDL.h>
#include <SDL_opengl.h>

// RapidXml
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_iterators.hpp>
#include <rapidxml/rapidxml_utils.hpp>
// TODO Only useful for debug builds.
#include <rapidxml/rapidxml_print.hpp>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Local systems that are widely used
// Generic types
#include "types.h"
// The logger
#include "log.h"

#endif // STD_H_
