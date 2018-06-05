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
  /**
   * Parse a character list into a standard vector.
   */
  template<typename NumT>
  inline void parseNumberList(std::vector<NumT>& array, const StringView& str) {
    uint8_t len {0};
    for (auto iter = str.begin(); iter <= str.end(); iter++) {
      if (std::isdigit(*iter) || *iter == '-' || *iter == '.' || *iter == 'e') {
        len++;
      }
      else {
        if (len > 0) {
          array.push_back(boost::lexical_cast<NumT>(iter - len, len));
        }
        len = 0;
      }
    }
  }

  /**
   * Parse a string into a standard vector.
   */
  template<typename NumT>
  inline void parseNumberList(std::vector<NumT>& array, const String& str) {
    uint8_t len {0};
    for (auto iter = str.begin(); iter <= str.end(); iter++) {
      if (std::isdigit(*iter) || *iter == '-' || *iter == '.') {
        len++;
      }
      else {
        if (len > 0) {
          array.push_back(boost::lexical_cast<NumT>(iter - len, len));
        }
        len = 0;
      }
    }
  }

  /**
   * Parse a null-terminated character list to a standard vector.
   */
  template<typename NumT>
  inline void parseNumberList(std::vector<NumT>& array, const CharType* pstr) {
    StringView sv {pstr};
    parseNumberList(array, sv);
  }
}

#endif // STRING_UTILS_H
