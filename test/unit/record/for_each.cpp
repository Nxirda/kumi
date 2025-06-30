//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#define TTS_MAIN
#include <kumi/record.hpp>
#include <tts/tts.hpp>

struct A { void operator()(auto&&) & {} };
struct B { void operator()(auto&&) && {} };

TTS_CASE("Check for_each SFINAE compliance")
{
  using namespace kumi::literals;
  
  A a;
  B b;
  auto t = kumi::make_record("a"_f = 1,"b"_f = 2);

  TTS_EXPECT_COMPILES(a, t, { kumi::for_each(a, t); } );
  TTS_EXPECT_NOT_COMPILES(b, t, { kumi::for_each(b, t); } );
};

TTS_CASE("Check for_each behavior")
{
  using namespace kumi::literals;
  
  auto t = kumi::record {"a"_f = 1, "b"_f = 2., "c"_f = 3.4f, "d"_f = '5'};
  kumi::for_each([](auto &m) { m++; }, t);

  TTS_EQUAL(get<"a"_f>(t), 2);
  TTS_EQUAL(get<"b"_f>(t), 3.);
  TTS_EQUAL(get<"c"_f>(t), 4.4f);
  TTS_EQUAL(get<"d"_f>(t), '6');

  kumi::for_each([](auto &m, auto n) { m *= n; }, t, t);

  TTS_EQUAL(get<"a"_f>(t), 4);
  TTS_EQUAL(get<"b"_f>(t), 9.);
  TTS_EQUAL(get<"c"_f>(t), 19.36f);
  TTS_EQUAL(get<"d"_f>(t), 'd');

  bool was_run = false;
  kumi::for_each([&]() { was_run = true; }, kumi::record{});
  TTS_EXPECT_NOT(was_run);
};

TTS_CASE("Check for_each constexpr behavior")
{
  using namespace kumi::literals;

  constexpr auto t = []() {
    auto it = kumi::record {"a"_f = 1, "b"_f = 2., "c"_f = 3.4f, "d"_f = '5'};
    kumi::for_each([](auto &m) { m++; }, it);
    return it;
  }();

  TTS_CONSTEXPR_EQUAL(get<"a"_f>(t), 2);
  TTS_CONSTEXPR_EQUAL(get<"b"_f>(t), 3.);
  TTS_CONSTEXPR_EQUAL(get<"c"_f>(t), 4.4f);
  TTS_CONSTEXPR_EQUAL(get<"d"_f>(t), '6');

  constexpr auto t2 = []() {
    auto it = kumi::record {"a"_f = 1, "b"_f = 2., "c"_f = 3.4f, "d"_f = char(8)};
    kumi::for_each([](auto &m, auto n) { m *= n; }, it, it);
    return it;
  }();

  TTS_CONSTEXPR_EQUAL(get<"a"_f>(t2), 1);
  TTS_CONSTEXPR_EQUAL(get<"b"_f>(t2), 4.);
  TTS_CONSTEXPR_EQUAL(get<"c"_f>(t2), 11.56f);
  TTS_CONSTEXPR_EQUAL(get<"d"_f>(t2), '@');
};

TTS_CASE("Check for_each_index behavior")
{
  using namespace kumi::literals;

  auto t = kumi::record {"a"_f = 1, "b"_f = 2., "c"_f = 3.4f, "d"_f = '5'};
  kumi::for_each_index(
      [](auto i, auto &m) {
        if constexpr( i % 2 == 0 )
          m++;
        else
          m--;
      },
      t);

  TTS_EQUAL(get<"a"_f>(t), 2);
  TTS_EQUAL(get<"b"_f>(t), 1.);
  TTS_EQUAL(get<"c"_f>(t), 4.4f);
  TTS_EQUAL(get<"d"_f>(t), '4');

  kumi::for_each_index(
      [](auto i, auto &m, auto n) {
        if constexpr( i % 2 == 0 )
          m *= n;
        else
          m += n;
      },
      t, t);

  TTS_EQUAL(get<"a"_f>(t), 4);
  TTS_EQUAL(get<"b"_f>(t), 2.);
  TTS_EQUAL(get<"c"_f>(t), 19.36f);
  TTS_EQUAL(get<"d"_f>(t), 'h');
};

TTS_CASE("Check for_each_index constexpr behavior")
{
  using namespace kumi::literals;

  constexpr auto t = []() {
    auto it = kumi::record {"a"_f = 1, "b"_f = 2., "c"_f = 3.4f, "d"_f = '5'};
    kumi::for_each_index(
        [](auto i, auto &m) {
          if constexpr( i % 2 == 0 )
            m++;
          else
            m--;
        },
        it);
    return it;
  }();

  TTS_CONSTEXPR_EQUAL(get<"a"_f>(t), 2);
  TTS_CONSTEXPR_EQUAL(get<"b"_f>(t), 1.);
  TTS_CONSTEXPR_EQUAL(get<"c"_f>(t), 4.4f);
  TTS_CONSTEXPR_EQUAL(get<"d"_f>(t), '4');

  constexpr auto t2 = []() {
    auto it = kumi::record {"a"_f = 1, "b"_f = 2., "c"_f = 3.4f, "d"_f = '5'};
    kumi::for_each_index(
        [](auto i, auto &m, auto n) {
          if constexpr( i % 2 == 0 )
            m *= n;
          else
            m +=n;
        },
        it, it);
    return it;
  }();

  TTS_CONSTEXPR_EQUAL(get<"a"_f>(t2), 1);
  TTS_CONSTEXPR_EQUAL(get<"b"_f>(t2), 4.);
  TTS_CONSTEXPR_EQUAL(get<"c"_f>(t2), 11.56f);
  TTS_CONSTEXPR_EQUAL(get<"d"_f>(t2), 'j');

  bool was_run = false;
  kumi::for_each_index([&]() { was_run = true; }, kumi::record{});
  TTS_EXPECT_NOT(was_run);
};
