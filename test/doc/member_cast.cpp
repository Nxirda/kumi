/**
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <kumi/kumi.hpp>
#include <iostream>

int main()
{
  auto a = kumi::tuple{ 14.2f, 42, 'a', short{89}, kumi::tuple{ 3.33, long{222} }};
  
  auto b = kumi::recursive_member_cast<int>(a);

  std::cout << a << "\n";
  std::cout << b << "\n";
}
