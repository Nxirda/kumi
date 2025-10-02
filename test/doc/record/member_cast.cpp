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

  auto a = kumi::record{ "a"_f = 14.2f, "b"_f = 42, "c"_f = 'a', "d"_f = short{89}
                       , "e"_f = kumi::record{ "g"_f = 3.33, "h"_f = long{222} }};
  
  auto b = kumi::recursive_member_cast<int>(a);

  std::cout << a << "\n";
  std::cout << b << "\n";
}
