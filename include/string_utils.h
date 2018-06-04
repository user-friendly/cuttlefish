/**
 * @file
 * Utility string declarations file.
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "std.h"
#include "types.h"

namespace cuttlefish
{
  template<typename NumT, typename StringT>
  inline void parseFloat(std::vector<NumT>& array, const StringT& str) {
    uint8_t len {0};
    for (auto iter = str.begin(); iter <= str.end(); iter++) {
      if (std::isdigit(*iter) || *iter == '-' || *iter == '.') {
        len++;
      }
      else {
        if (len > 0) {
          array.push_back(boost::lexical_cast<Float>(iter - len, len));
        }
        len = 0;
      }
    }
  }
}

#endif // STRING_UTILS_H
