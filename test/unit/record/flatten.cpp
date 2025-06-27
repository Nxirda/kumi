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

TTS_CASE("Check result::flatten/flatten_all<record> behavior")
{
  using namespace kumi::literals;

  using char_f      = kumi::field_capture<"a", char>;
  using short_f     = kumi::field_capture<"b", short>;
  using int_f       = kumi::field_capture<"c", int>;
  using double_f    = kumi::field_capture<"d", double>;
  
  TTS_TYPE_IS( (kumi::result::flatten_t<kumi::record<>>), (kumi::record<>));

  TTS_TYPE_IS ( (kumi::result::flatten_t<kumi::record<char_f,short_f,int_f,double_f>>)
              , (kumi::record<char_f,short_f,int_f,double_f>)
              );

  TTS_TYPE_IS ( (kumi::result::flatten_t<kumi::record<char_f, kumi::field_capture<"e"
                                                     , kumi::record<short_f,int_f, kumi::field_capture<"f"
                                                        , kumi::record<double_f>>>>>>)
              , (kumi::record<char_f,short_f,int_f,kumi::field_capture<"f", kumi::record<double_f>>>)
              );

  TTS_TYPE_IS ( (kumi::result::flatten_all_t<kumi::record<kumi::field_capture<"e", kumi::record<char_f,short_f>>
                                                        ,kumi::field_capture<"f", kumi::record<int_f, kumi::field_capture<"g", kumi::record<double_f>>>>
                                                        >
                                            >
                )
              , (kumi::record<char_f,short_f,int_f,double_f>)
              );

  /*auto func     = [](auto& m)        { return &m; };
  auto cfunc    = [](auto const& m)  { return &m; };
  using func_t  = decltype(func);
  using cfunc_t = decltype(cfunc);

  TTS_TYPE_IS ( (kumi::result::flatten_all_t<kumi::record<kumi::field_capture<"e", kumi::record<char_f,short_f>>
                                                        , kumi::field_capture<"f", kumi::record<int_f, kumi::field_capture<"g", kumi::record<double_f>>>>
                                                        >
                                            , func_t
                                            >
                )
              , (kumi::record<kumi::field_capture<"a",char*>,kumi::field_capture<"b",short*>,kumi::field_capture<"c", int*>,kumi::field_capture<"d", double*>>)
              );

  TTS_TYPE_IS ( (kumi::result::flatten_all_t<kumi::record< kumi::field_capture<"e", kumi::record<char_f,short_f>>
                                                        , kumi::field_capture<"g",  kumi::record<int_f, kumi::field_capture<"f",kumi::record<double_f>>>>
                                                        >
                                            , cfunc_t
                                            >
                )
              , (kumi::record<kumi::field_capture<"a",char const*>,kumi::field_capture<"b", short const*>,kumi::field_capture<"c", int const*>,kumi::field_capture<"d", double const*>>)
              );*/
};


TTS_CASE("Check record::flatten behavior")
{
  using namespace kumi::literals;

  TTS_EQUAL( kumi::flatten(kumi::record {}), kumi::record {});
  TTS_EQUAL((kumi::flatten(kumi::record {"a"_f = 2., "b"_f = 1, "c"_f = short {55}})), (kumi::record {"a"_f = 2., "b"_f = 1, "c"_f = short {55}}));
  TTS_EQUAL((kumi::flatten(kumi::record {"a"_f = 3.25f, "b"_f = kumi::record {"c"_f = 2., "d"_f = 1, "e"_f = short {55}}, "f"_f = 'z'})),
            (kumi::record {"a"_f = 3.25f, "c"_f = 2., "d"_f = 1, "e"_f = short {55}, "f"_f = 'z'}));
  TTS_EQUAL((kumi::flatten(kumi::record {
                "a"_f = 3.25f, "b"_f = kumi::record {"c"_f = 2., "d"_f = kumi::record {"e"_f = 2., "f"_f = 1, "g"_f = short {55}}, "h"_f = short {55}}, "i"_f = 'z'})),
            (kumi::record {"a"_f = 3.25f, "c"_f = 2., "d"_f = kumi::record {"e"_f = 2., "f"_f = 1, "g"_f = short {55}}, "h"_f = short {55}, "i"_f  = 'z'}));
};


TTS_CASE("Check record::flatten constexpr behavior")
{
  using namespace kumi::literals;

  constexpr auto t0 = kumi::record {"a"_f = 2., "b"_f = 1, "c"_f = short {55}};
  constexpr auto t1 = kumi::record {"a"_f = 3.25f, "b"_f = kumi::record {"c"_f = 2., "d"_f = 1, "e"_f = short {55}}, "f"_f = 'z'};
  constexpr auto t2 =
      kumi::record {"a"_f = 3.25f, "b"_f = kumi::record {"c"_f = 2., "d"_f = kumi::record {"e"_f = 2., "f"_f = 1, "g"_f = short {55}}, "h"_f = short {55}}, "i"_f = 'z'};

  TTS_CONSTEXPR_EQUAL(kumi::flatten(kumi::record{}), kumi::record{});
  TTS_CONSTEXPR_EQUAL(kumi::flatten(t0), (kumi::record {"a"_f = 2., "b"_f = 1, "c"_f = short {55}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten(t1), (kumi::record {"a"_f = 3.25f, "c"_f = 2., "d"_f = 1, "e"_f = short {55}, "f"_f = 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten(t2),
                      (kumi::record {"a"_f = 3.25f, "c"_f = 2., "d"_f = kumi::record {"e"_f = 2., "f"_f = 1, "g"_f = short {55}}, "h"_f = short {55}, "i"_f = 'z'}));
};


TTS_CASE("Check record::flatten_all behavior")
{
  using namespace kumi::literals;

  TTS_EQUAL( kumi::flatten_all(kumi::record{}),kumi::record{});
  TTS_EQUAL((kumi::flatten_all(kumi::record{"a"_f = kumi::record{},"b"_f = kumi::record{},"c"_f = kumi::record{}})),kumi::record{});
  TTS_EQUAL((kumi::flatten_all(kumi::record {"a"_f = 2., "b"_f = 1, "c"_f = short {55}})),
            (kumi::record {"a"_f = 2., "b"_f = 1, "c"_f = short {55}}));
  TTS_EQUAL((kumi::flatten_all(kumi::record {"a"_f = 3.25f, "b"_f = kumi::record {"c"_f = 2., "d"_f = 1, "e"_f = short {55}}, "f"_f = 'z'})),
            (kumi::record {"a"_f = 3.25f, "c"_f = 2., "d"_f = 1, "e"_f = short {55}, "f"_f = 'z'}));
  TTS_EQUAL((kumi::flatten_all(kumi::record {
                "a"_f = 3.25f, "b"_f = kumi::record {"c"_f = 2., "d"_f = kumi::record {"e"_f = 2., "f"_f = 1, "g"_f = short {55}}, "h"_f = short {55}}, "i"_f = 'z'})),
            (kumi::record {"a"_f = 3.25f, "c"_f = 2., "e"_f = 2., "f"_f = 1, "g"_f = short {55}, "h"_f = short {55}, "i"_f = 'z'}));
  TTS_EQUAL((kumi::flatten_all(kumi::record {
                "a"_f = 3.25f, "b"_f = kumi::record {"c"_f = 2., "d"_f = kumi::record{}, "e"_f = short {55}}, "f"_f = 'z'})),
            (kumi::record {"a"_f = 3.25f, "c"_f = 2., "e"_f = short {55}, "f"_f = 'z'}));
};
/*
TTS_CASE("Check record::flatten_all + function behavior")
{
  auto inc = [](auto m) { return m+1; };

  TTS_EQUAL( kumi::flatten_all(kumi::record{}, inc),kumi::record{});

  TTS_EQUAL((kumi::flatten_all(kumi::record{kumi::record{},kumi::record{},kumi::record{}},inc))
            ,kumi::record{}
            );

  TTS_EQUAL((kumi::flatten_all(kumi::record {2., 1, short {55}}, inc)),
            (kumi::record {3., 2, short {56}}));

  TTS_EQUAL((kumi::flatten_all(kumi::record {3.25f, kumi::record {2., 1, short {55}}, 'a'}, inc)),
            (kumi::record {4.25f, 3., 2, short {56}, 'b'}));

  TTS_EQUAL((kumi::flatten_all(kumi::record {
                3.25f, kumi::record {2., kumi::record {2., 1, short {55}}, short {55}}, 'a'}, inc)),
            (kumi::record {4.25f, 3., 3., 2, short {56}, short {56}, 'b'}));

  TTS_EQUAL((kumi::flatten_all(kumi::record {
                3.25f, kumi::record {2., kumi::record{}, short {55}}, 'a'}, inc)),
            (kumi::record {4.25f, 3., short {56}, 'b'}));
};*/

TTS_CASE("Check record::flatten_all constexpr behavior")
{
  using namespace kumi::literals;

  constexpr auto t0 = kumi::record {"a"_f = 2., "b"_f = 1, "c"_f = short {55}};
  constexpr auto t1 = kumi::record {"d"_f = 3.25f, "e"_f = kumi::record {"f"_f = 2., "g"_f = 1, "h"_f = short {55}},"i"_f = 'z'};
  constexpr auto t2 = kumi::record {"j"_f = 3.25f, "k"_f = t0, "l"_f = t1, "m"_f = 'z'};
  constexpr auto te = kumi::record {"a"_f = 3.25f, "b"_f = kumi::record {}, "c"_f = 'z'};

  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(kumi::record{}),kumi::record{});
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t0), (kumi::record {"a"_f = 2., "b"_f = 1, "c"_f = short {55}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t1), (kumi::record {"d"_f = 3.25f, "f"_f = 2., "g"_f = 1, "h"_f = short {55}, "i"_f = 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(te), (kumi::record {"a"_f = 3.25f, "c"_f = 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t2),
                      (kumi::record {"j"_f = 3.25f, "a"_f = 2., "b"_f = 1, "c"_f = short {55}, "d"_f = 3.25f, "f"_f = 2., "g"_f = 1, "h"_f = short {55}, "i"_f = 'z', "m"_f = 'z'}));
};

/*
TTS_CASE("Check record::flatten_all + function constexpr behavior")
{
  constexpr auto t0 = kumi::record {2., 1, short {55}};
  constexpr auto t1 = kumi::record {3.25f, kumi::record {2., 1, short {55}}, 'a'};
  constexpr auto t2 = kumi::record {3.25f, t0, t1, 'a'};
  constexpr auto te = kumi::record {3.25f, kumi::record {}, 'a'};

  auto inc = [](auto m) { return m+1; };

  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(kumi::record{}, inc),kumi::record{});
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t0, inc), (kumi::record {3., 2, short {56}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t1, inc), (kumi::record {4.25f, 3., 2, short {56}, 'b'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(te, inc), (kumi::record {4.25f, 'b'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t2, inc),
                      (kumi::record {4.25f, 3., 2, short {56}, 4.25f, 3., 2, short {56}, 'b', 'b'}));
};
*/
