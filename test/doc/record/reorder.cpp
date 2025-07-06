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

  auto values = kumi::record { "a"_f = 1, "b"_f = 'a', "c"_f = 0.1 };

  std::cout << values << "\n";
  std::cout << kumi::reorder<2,1,0>(values) << "\n";
  std::cout << kumi::reorder_fields<"b"_f,"a"_f,"c"_f>(values) << "\n";
}
