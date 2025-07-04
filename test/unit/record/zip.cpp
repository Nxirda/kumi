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

TTS_CASE("Check result::zip<record...> behavior")
{
  using char_f      = kumi::field_capture<"a", char>;
  using short_f     = kumi::field_capture<"b", short>;
  using int_f       = kumi::field_capture<"c", int>;

  using ld_f        = kumi::field_capture<"b", long double>;
  using double_f    = kumi::field_capture<"c", double>;
  using float_f     = kumi::field_capture<"a", float>;

  using voidp_f     = kumi::field_capture<"c", void*>;
  using voidpp_f    = kumi::field_capture<"a", void**>;
  using voidppp_f   = kumi::field_capture<"b", void***>;

  using record1_t = kumi::record<char_f,short_f,int_f>;
  using record2_t = kumi::record<ld_f, double_f, float_f>;
  using record3_t = kumi::record<voidp_f,voidpp_f,voidppp_f>;

  TTS_TYPE_IS ( (kumi::result::zip_t<record1_t, record2_t,record3_t>)
              , (kumi::record<kumi::field_capture<"a", kumi::tuple<char, float, void**>>,
                              kumi::field_capture<"b", kumi::tuple<short, long double, void***>>,
                              kumi::field_capture<"c", kumi::tuple<int, double, void*>>>)
              );
};

TTS_CASE("Check record::zip behavior")
{
  auto numbers = kumi::record {"a"_f = 1, "c"_f = 2, "b"_f = 3, "d"_f = 4};
  auto letters = kumi::record {"c"_f = 'a', "d"_f = 'b', "b"_f = 'c', "a"_f = 'd'};
  auto ratio   = kumi::record {"b"_f = 1.f, "a"_f = 0.5f, "d"_f = 0.25, "c"_f = 0.01};

  TTS_EQUAL((kumi::zip(kumi::record{},kumi::record{})),kumi::record{});

  TTS_EQUAL((kumi::zip(numbers, letters)),
            (kumi::record {"a"_f = kumi::tuple{1, 'd'}, "c"_f = kumi::tuple{2, 'a'}, "b"_f = kumi::tuple{3, 'c'}, "d"_f = kumi::tuple{4, 'b'}}));

  TTS_EQUAL(
      (kumi::zip(numbers, letters, ratio)),
      (kumi::record {
          "a"_f = kumi::tuple{1, 'd', 0.5f}, "c"_f = kumi::tuple{2, 'a', 0.01}, "b"_f = kumi::tuple{3, 'c', 1.f}, "d"_f = kumi::tuple{4, 'b', 0.25}}));
};

TTS_CASE("Check record::zip constexpr behavior")
{
  constexpr auto numbers = kumi::record {"a"_f = 1, "b"_f = 2, "c"_f = 3, "d"_f = 4};
  constexpr auto letters = kumi::record {"c"_f = 'a', "d"_f = 'b', "a"_f = 'c', "b"_f = 'd'};
  constexpr auto ratio   = kumi::record {"d"_f = 1.f, "b"_f = 0.5f, "a"_f = 0.25, "c"_f = 0.01};

  TTS_CONSTEXPR_EQUAL((kumi::zip(numbers, letters)),
                      (kumi::record{"a"_f = kumi::tuple {1, 'c'}, "b"_f = kumi::tuple {2, 'd'}, "c"_f = kumi::tuple {3, 'a'}, "d"_f = kumi::tuple {4, 'b'}}));

  TTS_CONSTEXPR_EQUAL(
      (kumi::zip(numbers, letters, ratio)),
      (kumi::record{
          "a"_f = kumi::tuple {1, 'c', 0.25}, "b"_f = kumi::tuple {2, 'd', 0.5f}, "c"_f = kumi::tuple {3, 'a', 0.01}, "d"_f = kumi::tuple {4, 'b', 1.f}}));
};
