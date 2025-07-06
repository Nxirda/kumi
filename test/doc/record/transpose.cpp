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

  auto values = kumi::record { "toto"_f = kumi::record{ "a"_f = 1, "b"_f = 'a', "c"_f = 0.1   }
                            ,  "tata"_f = kumi::record{ "a"_f = 2, "b"_f = 'b', "c"_f = 0.01  }
                            };

  auto r = kumi::transpose(values );
  std::cout << r << "\n";
}
