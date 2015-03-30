/*
 * File std.hpp
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

#ifndef STD_HPP_
#define STD_HPP_

// C++ STD headers.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
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

// POSIX headers?
#include <unistd.h>

// Boost headers.
#include <boost/utility.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#endif /* STD_HPP_ */
