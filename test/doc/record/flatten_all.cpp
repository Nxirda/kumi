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

  auto nbrs      = kumi::record{"nb1"_f = 1,"nb2"_f = 2ULL,"nb3"_f = 3};
  auto more_nbrs = kumi::record{"nb4"_f = short{0},"nbrs"_f = nbrs,"nb6"_f = 4.};
  auto ltrs      = kumi::record{"l1"_f = 'a',"l2"_f = 'b',"l3"_f = 'c'};

  auto r = kumi::flatten_all( kumi::record{"a"_f = 3.5,"numbers"_f = nbrs,"b"_f = 'z',
                                           "more_numbers"_f = more_nbrs, "m"_f = 5.35f, "letters"_f = ltrs} );
  std::cout << r << "\n";

  auto sz = kumi::flatten_all ( kumi::record{"a"_f = 3.5,"numbers"_f = nbrs,"b"_f = 'z',
                                            "more_numbers"_f = more_nbrs,"m"_f = 5.35f,"letters"_f = ltrs}
                              , [](auto e) { return sizeof(e); }
                              );
  std::cout << sz << "\n";
}
