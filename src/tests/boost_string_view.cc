/**
 * Boost String View tests
 * and experimentation
 */

#include "std.h"
#include "string_utils.h"

using namespace cuttlefish;

using int_t = uint16_t;
using vec_ti = std::vector<int_t>;
using vec_tf = std::vector<float>;
using str_t = boost::string_view;

template<typename NumT, typename CharT>
void boost_string_view_print(const std::vector<NumT>& nums, const boost::basic_string_view<CharT>& str) {
  std::cout << "parse str: " << str << "\nnumbers: ";
  for (const NumT& x : nums) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
}

void test_boost_string_view() {
  vec_ti numsi {};
  vec_tf numsf {};

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
    numsi.clear();
    try {
      boost_string_view_print(numsi << str, str);
    }
    catch (boost::bad_lexical_cast e) {
      std::cerr << "bad lexical cast: " << e.what() << std::endl;
      std::cerr << "failed to convert line: " << str << std::endl;
      break;
    }
  }

  lines.clear();
  lines = {
    {"-1.1 jjf -0.1 fjdf -9999.9999111 "},
    {"-1. -.00000001"},
    {"-.1"},
    {"-0."},
    {"-.0"}
  };

  for (auto str : lines) {
    numsf.clear();
    try {
      boost_string_view_print(numsf << str, str);
    }
    catch (boost::bad_lexical_cast e) {
      std::cerr << "bad lexical cast: " << e.what() << std::endl;
      std::cerr << "failed to convert line: " << str << std::endl;
      break;
    }
  }
}
