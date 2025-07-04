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

using namespace kumi::literals;

TTS_CASE("Check result::transpose<record> behavior")
{

  using char_f          = kumi::field_capture<"a", char>;
  using short_f         = kumi::field_capture<"b", short>;
  using int_f           = kumi::field_capture<"c", int>;

  using long_double_f   = kumi::field_capture<"a", long double>;
  using double_f        = kumi::field_capture<"b", double>;
  using float_f         = kumi::field_capture<"c", float>;

  using record1_t = kumi::record<char_f,short_f,int_f>;
  using record2_t = kumi::record<long_double_f, double_f, float_f>;
  using record_t  = kumi::record<kumi::field_capture<"g", record1_t>, kumi::field_capture<"h", record2_t>>;

  TTS_TYPE_IS( (kumi::result::transpose_t<record_t>), (kumi::record<kumi::field_capture<"a", kumi::record<kumi::field_capture<"g", char>, kumi::field_capture<"h", long double>>>  ,
                                                                  kumi::field_capture<"b", kumi::record<kumi::field_capture<"g",short>, kumi::field_capture<"h", double>>>       ,
                                                                  kumi::field_capture<"c", kumi::record<kumi::field_capture<"g", int> , kumi::field_capture<"h", float>>>
                                                                  > 
                                                    )
            );
};

TTS_CASE("Check record::transpose behavior")
{
  auto numbers = kumi::record {"a"_f = 1, "b"_f = 2, "c"_f = 3, "d"_f = 4};
  auto letters = kumi::record {"a"_f = 'a', "b"_f = 'b', "c"_f = 'c', "d"_f = 'd'};
  auto ratio   = kumi::record {"a"_f = 1.f, "b"_f = 0.1f, "c"_f = 0.01f, "d"_f = 0.001f};

  TTS_EQUAL(kumi::transpose(kumi::record{}),kumi::record{});

  TTS_EQUAL((kumi::transpose(kumi::record{ "n"_f = numbers, "l"_f = letters, "r"_f = ratio })),
            (kumi::record { "a"_f = kumi::record {"n"_f = 1, "l"_f = 'a', "r"_f      = 1.f}, 
                            "b"_f = kumi::record {"n"_f = 2, "l"_f = 'b', "r"_f     = 0.1f}, 
                            "c"_f = kumi::record {"n"_f = 3, "l"_f = 'c', "r"_f    = 0.01f}, 
                            "d"_f = kumi::record {"n"_f = 4, "l"_f = 'd', "r"_f   = 0.001f}}));
};

TTS_CASE("Check constexpr record::transpose behavior")
{
  constexpr auto numbers = kumi::record {"a"_f = 1  , "b"_f = 2     , "c"_f = 3     , "d"_f = 4};
  constexpr auto letters = kumi::record {"a"_f = 'a', "b"_f = 'b'   , "c"_f = 'c'   , "d"_f = 'd'};
  constexpr auto ratio   = kumi::record {"a"_f = 1.f, "b"_f = 0.1f  , "c"_f = 0.01f , "d"_f = 0.001f};

  TTS_CONSTEXPR_EQUAL((kumi::transpose(kumi::record{ "n"_f = numbers, "l"_f = letters, "r"_f = ratio })),
            (kumi::record { "a"_f = kumi::record {"n"_f = 1, "l"_f = 'a', "r"_f      = 1.f}, 
                            "b"_f = kumi::record {"n"_f = 2, "l"_f = 'b', "r"_f     = 0.1f}, 
                            "c"_f = kumi::record {"n"_f = 3, "l"_f = 'c', "r"_f    = 0.01f}, 
                            "d"_f = kumi::record {"n"_f = 4, "l"_f = 'd', "r"_f   = 0.001f}}));
};
