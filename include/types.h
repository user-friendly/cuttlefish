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
  using FloatArray = std::vector<Float>;

  using IndexType = std::uint16_t;
  using IndexArray = std::vector<IndexType>;

  // Game wide character type. (Is this a good idea? Probably not.)
  using CharType = char;
  
  // String related.
  using String = std::basic_string<CharType>;
  using StringView = std::basic_string_view<CharType>;
}

#endif // TYPEALIAS_H
