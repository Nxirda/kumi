/**
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <kumi/kumi.hpp>
#include <iostream>

int main()
{
  using target_t = kumi::tuple<int, bool, float, long, kumi::tuple<short, char>>;

  auto a = kumi::tuple{ 14.1f, 42, '7', short{89} , kumi::tuple{ 2.3,long{55} }};

  auto b = kumi::recursive_structural_cast<target_t>(a);

  std::cout << a << "\n";
  std::cout << b << "\n";
}
