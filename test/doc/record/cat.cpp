/**
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <kumi/record.hpp>
#include <iostream>

int main()
{
  using namespace kumi::literals;

  kumi::record a = { "r"_f = 1,"g"_f = 2.3, "b"_f = 4.5f};
  kumi::record b = { "x"_f = '6' };
  kumi::record c = { "y"_f = "7", "z"_f = short{89} };

  auto abc = cat(a,b,c);

  std::cout << a << " " << b << " " << c << "\n";
  std::cout << abc << "\n";
    
  using x = kumi::common_product_type_or_t<kumi::tuple, std::remove_cvref_t<decltype(a)>, std::remove_cvref_t<decltype(b)>, std::remove_cvref_t<decltype(c)>>;
  x r;
  void *ptr = r;
  //void *ptr = abc;
  //static_assert(std::is_same_v<kumi::template_of_t<decltype(a)>, kumi::template_of_t<decltype(abc)>>);
}
