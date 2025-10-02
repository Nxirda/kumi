/**
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <kumi/kumi.hpp>
#include <iostream>

int main()
{
  using namespace kumi::literals;
  using target_t = kumi::tuple<int, bool, float, long, kumi::tuple<short, char>>;

  auto a = kumi::record{ "a"_f = 14.1f , "b"_f = 42, "c"_f = '7', "d"_f = short{89}, 
                         "e"_f = kumi::record{ "f"_f = 2.3, "g"_f = long{55} }};
   
  auto b = kumi::recursive_structural_cast<target_t>(a);

  std::cout << a << "\n";
  std::cout << b << "\n";
}
