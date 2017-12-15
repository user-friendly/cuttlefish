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
#ifdef HAVE_GL_GL_H
  #include <GL/gl.h>
#elif defined(HAVE_OPENGL_GL_H)
  #include <OpenGL/gl.h>
#else
  #error no gl.h
#endif

// OS specific headers.
#ifdef OS_WINDOWS
// Windows specific headers.
#include <windows.h>
#elif OS_LINUX
#include <unistd.h>
#endif

// Guideline Support Library
#include <gsl/gsl>

// Boost headers.
#include <boost/format.hpp>

// SDL2 headers.
#include <SDL.h>

// RapidXml
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_iterators.hpp>
#include <rapidxml/rapidxml_utils.hpp>
// TODO Only useful for debug builds.
#include <rapidxml/rapidxml_print.hpp>

// Generic local types
#include "types.h"

#endif // STD_H_
