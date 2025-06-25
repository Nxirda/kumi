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

  auto nbrs       = kumi::record{"a"_f = 1, "b"_f = 2, "c"_f = 3};
  auto more_nbrs  = kumi::record{"d"_f = 0, "e"_f = nbrs, "g"_f = 4};
  auto ltrs       = kumi::record{"h"_f = 'a', "i"_f = 'b', "j"_f = 'c'};

  auto r = kumi::flatten( kumi::record{"id"_f = 3.5, "nbs"_f = nbrs, "data"_f = 'z',
                                      "suite"_f = more_nbrs, "x"_f = 5.35f, "alpha"_f = ltrs} );
  std::cout << r << "\n";

  void *ptr = r;
}
