/**
 * @file 
 * Type aliases declaration file.
 */

#ifndef TYPEALIAS_H
#define TYPEALIAS_H

#include "std.h"

namespace cuttlefish
{
  // Math related.
  using Float = float;
  using FloatArray = std::vector<float>;

  // Game wide character type. (Is this a good idea? Probably not.)
  using CharT = char;
  
  // String related.
  using String = std::basic_string<CharT>;
  using StringView = std::basic_string_view<CharT>;
}

#endif // TYPEALIAS_H
