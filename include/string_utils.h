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
  template<typename IntT, typename StringT>
  std::vector<IntT> parse_integers(const StringT str) {
    std::vector<IntT> nums;
    uint8_t len {0};
    for (auto iter = str.begin(); iter <= str.end(); iter++) {
      if (std::isdigit(*iter)) {
        len++;
      }
      else {
        if (len > 0) {
          nums.push_back(boost::lexical_cast<IntT>(iter - len, len));
        }
        len = 0;
      }
    }
    return std::move(nums);
  };
}


#endif // STRING_UTILS_H


