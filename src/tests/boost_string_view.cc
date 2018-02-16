/**
 * Boost String View tests
 * and experimentation
 */

#include "std.h"
#include "string_utils.h"

using int_t = uint16_t;
using vec_t = std::vector<int_t>;
using str_t = boost::string_view;

template<typename IntT, typename CharT>
void boost_string_view_print(const std::vector<IntT>& nums, const boost::basic_string_view<CharT>& str) {
  std::cout << "parse str: " << str << "\nints: ";
  for (IntT x : nums) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
}

void test_boost_string_view() {
  vec_t nums {};

  std::vector<str_t> lines {
    {" 11b222j3333 12.233"},
    {"222 333 444 "},
    {"111"},
    {" 0 "},
    {" j "},
    {"   "},
    {"  "},
    {" "},
    {""},
  };

  for (auto str : lines) {
    nums = cuttlefish::parse_integers<uint16_t>(str);
    boost_string_view_print(nums, str);
  }
}
