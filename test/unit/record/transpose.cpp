//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#define TTS_MAIN
#include <array>
#include <kumi/record.hpp>
#include <tts/tts.hpp>
#include <vector>

TTS_CASE("Check result::transpose<record> behavior")
{

  using char_f          = kumi::field_capture<"a", char>;
  using short_f         = kumi::field_capture<"b", short>;
  using int_f           = kumi::field_capture<"c", int>;
  using long_double_f   = kumi::field_capture<"d", long double>;
  using double_f        = kumi::field_capture<"e", double>;
  using float_f         = kumi::field_capture<"f", float>;

  using record1_t = kumi::record<char_f,short_f,int_f>;
  using record2_t = kumi::record<long_double_f, double_f, float_f>;
  using record_t  = kumi::record<kumi::field_capture<"g", record1_t>, kumi::field_capture<"h", record2_t>>;

  TTS_TYPE_IS ( (kumi::result::transpose_t<record_t>), ( kumi::tuple< kumi::record<char_f, long_double_f>
                                                                    , kumi::record<short_f, double_f>
                                                                    , kumi::record<int_f, float_f>
                                                                    >
                                                      )
              );
};

TTS_CASE("Check record::transpose behavior")
{
  using namespace kumi::literals;

  auto numbers = kumi::record {"1"_f = 1, "2"_f = 2, "3"_f = 3, "4"_f = 4};
  auto letters = kumi::record {"a"_f = 'a', "b"_f = 'b', "c"_f = 'c', "d"_f = 'd'};
  auto ratio   = kumi::record {"1."_f = 1.f, "0.1"_f = 0.1f, "0.01"_f = 0.01f, "0.001"_f = 0.001f};

  TTS_EQUAL(kumi::transpose(kumi::record{}),kumi::record{});

  TTS_EQUAL((kumi::transpose(kumi::record{ "n"_f = numbers, "l"_f = letters, "r"_f = ratio })),
            (kumi::tuple {kumi::record {"1"_f = 1, "a"_f = 'a', "1."_f      = 1.f}, 
                          kumi::record {"2"_f = 2, "b"_f = 'b', "0.1"_f     = 0.1f}, 
                          kumi::record {"3"_f = 3, "c"_f = 'c', "0.01"_f    = 0.01f}, 
                          kumi::record {"4"_f = 4, "d"_f = 'd', "0.001"_f   = 0.001f}}));
};

TTS_CASE("Check constexpr record::transpose behavior")
{
  using namespace kumi::literals;

  constexpr auto numbers = kumi::record {"1"_f = 1, "2"_f = 2, "3"_f = 3, "4"_f = 4};
  constexpr auto letters = kumi::record {"a"_f = 'a', "b"_f = 'b', "c"_f = 'c', "d"_f = 'd'};
  constexpr auto ratio   = kumi::record {"1."_f = 1.f, "0.1"_f = 0.1f, "0.01"_f = 0.01f, "0.001"_f = 0.001f};

  TTS_CONSTEXPR_EQUAL((kumi::transpose(kumi::record{ "n"_f = numbers, "l"_f = letters, "r"_f = ratio })),
            (kumi::tuple {kumi::record {"1"_f = 1, "a"_f = 'a', "1."_f      = 1.f}, 
                          kumi::record {"2"_f = 2, "b"_f = 'b', "0.1"_f     = 0.1f}, 
                          kumi::record {"3"_f = 3, "c"_f = 'c', "0.01"_f    = 0.01f}, 
                          kumi::record {"4"_f = 4, "d"_f = 'd', "0.001"_f   = 0.001f}}));
};
