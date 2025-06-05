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

TTS_CASE("Check result::fill<Size, Tuple> behavior")
{
    using namespace kumi::literals;
    using tpl_t = kumi::tuple<int, int, int>;

    TTS_TYPE_IS((kumi::result::fill_t<3_c, int>) , (tpl_t));
};

TTS_CASE("Check result::fill<Size, Tuple> behavior on named tuples")
{
  using namespace kumi::literals;
    
  using fint    = decltype("z"_m = 1    );

  using tpl_t  = kumi::tuple<fint, fint, fint>;
  TTS_TYPE_IS((kumi::result::fill_t<3_c, fint>) , (tpl_t));
};

TTS_CASE("Check runtime kumi::fill behavior")
{
  using namespace kumi::literals;
  TTS_EQUAL ( kumi::fill<1>(1   ) , (kumi::tuple{1}                          ) );
  TTS_EQUAL ( kumi::fill<2>(2.f ) , (kumi::tuple{2.f, 2.f}                   ) );
  TTS_EQUAL ( kumi::fill<3>(3.  ) , (kumi::tuple{3.,3.,3.}                   ) );
  TTS_EQUAL ( kumi::fill<7>('7' ) , (kumi::tuple{'7','7','7','7','7','7','7'}) );
  TTS_EQUAL ( kumi::fill<3>("x"_m = 1.), (kumi::tuple{"x"_m = 1., "x"_m = 1., "x"_m = 1.}) );
};

TTS_CASE("Check constexpr kumi::fill behavior")
{
  using namespace kumi::literals;
  TTS_CONSTEXPR_EQUAL ( kumi::fill<1>(1   ) , (kumi::tuple{1}                          ) );
  TTS_CONSTEXPR_EQUAL ( kumi::fill<2>(2.f ) , (kumi::tuple{2.f, 2.f}                   ) );
  TTS_CONSTEXPR_EQUAL ( kumi::fill<3>(3.  ) , (kumi::tuple{3.,3.,3.}                   ) );
  TTS_CONSTEXPR_EQUAL ( kumi::fill<7>('7' ) , (kumi::tuple{'7','7','7','7','7','7','7'}) );
  TTS_CONSTEXPR_EQUAL ( kumi::fill<3>("x"_m = 1.), (kumi::tuple{"x"_m = 1., "x"_m = 1., "x"_m = 1.}) );
};
