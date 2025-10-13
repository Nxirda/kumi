/**
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include <kumi/kumi.hpp>
#include <iostream>

using namespace kumi::literals;

int main()
{
  auto lhs = kumi::record{"a"_f = 1  , "b"_f = 2  , "c"_f = 3  };
  auto rhs = kumi::record{"a"_f = 2.4, "b"_f = 4.6, "c"_f = 6.8};

  auto res = kumi::map_field( [](auto name, auto l, auto r) 
  { 
    if (name == "a")    return l + r;
    else                return 1000*+(l*r); 
  }
  , lhs, rhs
  );

  std::cout << res << "\n";
}