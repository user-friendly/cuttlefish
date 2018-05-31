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
  template<typename FloatT, typename StringT>
  std::vector<FloatT>& impl_parse_floats(std::vector<FloatT>& nums, const StringT& str) {
    uint8_t len {0};
    for (auto iter = str.begin(); iter <= str.end(); iter++) {
      if (std::isdigit(*iter) || *iter == '-' || *iter == '.') {
        len++;
      }
      else {
        if (len > 0) {
          nums.push_back(boost::lexical_cast<FloatT>(iter - len, len));
        }
        len = 0;
      }
    }
    return nums;
  };

  template<typename StringT>
  std::vector<float>& operator<<(std::vector<float>& nums, const StringT& str) {
    return impl_parse_floats(nums, str);
  };

  template<typename StringT>
  std::vector<double>& operator<<(std::vector<double>& nums, const StringT& str) {
    return impl_parse_floats(nums, str);
  };

  template<typename StringT>
  std::vector<long double>& operator<<(std::vector<long double>& nums, const StringT& str) {
    return impl_parse_floats(nums, str);
  };
  
  template<typename IntT, typename StringT>
  std::vector<IntT>& operator<<(std::vector<IntT>& nums, const StringT& str) {
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
    return nums;
  };
}


#endif // STRING_UTILS_H


