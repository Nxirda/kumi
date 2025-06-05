//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#define TTS_MAIN
#include <kumi/tuple.hpp>
#include <tts/tts.hpp>

constexpr auto t1 = [](auto &p){ return static_cast<int>(p);        };
constexpr auto t2 = [](auto   ){ return 2.f;                        };
constexpr auto t3 = [](auto  p){ return static_cast<double>(p);     };
constexpr auto t4 = [](auto   ){ return '7';                        };

using namespace kumi::literals;
constexpr auto t5 = [](auto p){ return "x"_m = static_cast<int>(p); };

TTS_CASE("Check result::generate<I,Tuple> behavior")
{ 
  using namespace kumi::literals; 
    
  using t1_t = decltype(kumi::tuple{"x"_m = 0, "x"_m = 1});

  TTS_TYPE_IS((kumi::result::generate_t<2_c,decltype(t5)>), t1_t);
  TTS_TYPE_IS((kumi::result::generate_t<2_c,decltype(t1)>), (kumi::tuple<int, int>));
};

TTS_CASE("Check runtime kumi::generate behavior")
{
  TTS_EQUAL ( kumi::generate<1>(t1 ) , (kumi::tuple{0}                          ) );
  TTS_EQUAL ( kumi::generate<2>(t2 ) , (kumi::tuple{2.f, 2.f}                   ) );
  TTS_EQUAL ( kumi::generate<9>(t3 ) , (kumi::tuple{0.,1.,2.,3.,4.,5.,6.,7.,8.} ) );
  TTS_EQUAL ( kumi::generate<7>(t4 ) , (kumi::tuple{'7','7','7','7','7','7','7'}) );
  TTS_EQUAL ( kumi::generate<2>(t5 ) , (kumi::tuple{"x"_m = 0, "x"_m = 1}       ) );
};

TTS_CASE("Check constexpr kumi::generate behavior")
{
  TTS_CONSTEXPR_EQUAL ( kumi::generate<1>(t1 ) , (kumi::tuple{0}                          ) );
  TTS_CONSTEXPR_EQUAL ( kumi::generate<2>(t2 ) , (kumi::tuple{2.f, 2.f}                   ) );
  TTS_CONSTEXPR_EQUAL ( kumi::generate<9>(t3 ) , (kumi::tuple{0.,1.,2.,3.,4.,5.,6.,7.,8.} ) );
  TTS_CONSTEXPR_EQUAL ( kumi::generate<7>(t4 ) , (kumi::tuple{'7','7','7','7','7','7','7'}) );
  TTS_CONSTEXPR_EQUAL ( kumi::generate<2>(t5 ) , (kumi::tuple{"x"_m = 0, "x"_m = 1}       ) );
};
