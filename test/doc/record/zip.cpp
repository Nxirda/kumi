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
    
  auto nbrs  = kumi::record{"a"_f = 1,"b"_f = 2,"c"_f = 3};
  auto ltrs  = kumi::record{"c"_f = 'a',"a"_f = 'b',"b"_f = 'c'};
  auto ratio = kumi::record{"b"_f = 0.1,"c"_f = 0.01,"a"_f = 0.001};

  auto r = kumi::zip( nbrs, ltrs, ratio );
  std::cout << r << "\n";
}
