//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#define TTS_MAIN
#include <array>
#include <kumi/tuple.hpp>
#include <tts/tts.hpp>
#include <vector>

TTS_CASE("Check result::flatten/flatten_all<Tuple> behavior")
{
  TTS_TYPE_IS ( (kumi::result::flatten_t<kumi::tuple<char,short,int,double>>)
              , (kumi::tuple<char,short,int,double>)
              );

  TTS_TYPE_IS ( (kumi::result::flatten_t<kumi::tuple<char,kumi::tuple<short,int,kumi::tuple<double>>>>)
              , (kumi::tuple<char,short,int,kumi::tuple<double>>)
              );

  TTS_TYPE_IS ( (kumi::result::flatten_all_t<kumi::tuple<kumi::tuple<char,short>
                                                        ,kumi::tuple<int,kumi::tuple<double>>
                                                        >
                                            >
                )
              , (kumi::tuple<char,short,int,double>)
              );

  auto func     = [](auto& m)        { return &m; };
  auto cfunc    = [](auto const& m)  { return &m; };
  using func_t  = decltype(func);
  using cfunc_t = decltype(cfunc);

  TTS_TYPE_IS ( (kumi::result::flatten_all_t<kumi::tuple<kumi::tuple<char,short>
                                                        ,kumi::tuple<int,kumi::tuple<double>>
                                                        >
                                            , func_t
                                            >
                )
              , (kumi::tuple<char*,short*,int*,double*>)
              );

  TTS_TYPE_IS ( (kumi::result::flatten_all_t<kumi::tuple<kumi::tuple<char,short>
                                                        ,kumi::tuple<int,kumi::tuple<double>>
                                                        >
                                            , cfunc_t
                                            >
                )
              , (kumi::tuple<char const*,short const*,int const*,double const*>)
              );
};

TTS_CASE("Check result::flatten/flatten_all<Tuple> behavior on named tuple")
{
  using namespace kumi::literals;

  using f1 = decltype("x"_m = 'x'       );
  using f2 = decltype("y"_m = short{55} );
  using f3 = decltype("z"_m = 1         );
  using f4 = decltype("t"_m = 2.        );

  TTS_TYPE_IS ( (kumi::result::flatten_t<kumi::tuple<f1,f2,f3,f4>>)
              , (kumi::tuple<char,short,int,double>)
              );

  TTS_TYPE_IS ( (kumi::result::flatten_t<kumi::tuple<f1,kumi::tuple<f2,f3,kumi::tuple<f4>>>>)
              , (kumi::tuple<char,f2,f3,kumi::tuple<f4>>)
              );

  TTS_TYPE_IS ( (kumi::result::flatten_all_t<kumi::tuple<kumi::tuple<f1,f2>
                                                        ,kumi::tuple<f3,kumi::tuple<f4>>
                                                        >
                                            >
                )
              , (kumi::tuple<char,short,int,double>)
              );

  auto func     = [](auto& m)        { return &m; };
  auto cfunc    = [](auto const& m)  { return &m; };
  using func_t  = decltype(func);
  using cfunc_t = decltype(cfunc);

  TTS_TYPE_IS ( (kumi::result::flatten_all_t<kumi::tuple<kumi::tuple<f1,f2>
                                                        ,kumi::tuple<f3,kumi::tuple<f4>>
                                                        >
                                            , func_t
                                            >
                )
              , (kumi::tuple<char*,short*,int*,double*>)
              );

  TTS_TYPE_IS ( (kumi::result::flatten_all_t<kumi::tuple<kumi::tuple<f1,f2>
                                                        ,kumi::tuple<f3,kumi::tuple<f4>>
                                                        >
                                            , cfunc_t
                                            >
                )
              , (kumi::tuple<char const*,short const*,int const*,double const*>)
              );
};

TTS_CASE("Check tuple::flatten behavior")
{
  TTS_EQUAL( kumi::flatten(kumi::tuple {}), kumi::tuple {});
  TTS_EQUAL((kumi::flatten(kumi::tuple {2., 1, short {55}})), (kumi::tuple {2., 1, short {55}}));
  TTS_EQUAL((kumi::flatten(kumi::tuple {3.25f, kumi::tuple {2., 1, short {55}}, 'z'})),
            (kumi::tuple {3.25f, 2., 1, short {55}, 'z'}));
  TTS_EQUAL((kumi::flatten(kumi::tuple {
                3.25f, kumi::tuple {2., kumi::tuple {2., 1, short {55}}, short {55}}, 'z'})),
            (kumi::tuple {3.25f, 2., kumi::tuple {2., 1, short {55}}, short {55}, 'z'}));
};

TTS_CASE("Check tuple::flatten behavior on named tuples")
{
  using namespace kumi::literals;
  TTS_EQUAL((kumi::flatten(kumi::tuple {"x"_m = 2., "y"_m = 1, "z"_m = short {55}})), (kumi::tuple {"x"_m = 2., "y"_m = 1, "z"_m = short {55}}));
  TTS_EQUAL((kumi::flatten(kumi::tuple {"x"_m = 3.25f, "y"_m = kumi::tuple {"z"_m = 2., "t"_m = 1, "m"_m = short {55}}, "id"_m = 'z'})),
            (kumi::tuple {"x"_m = 3.25f, "z"_m = 2., "t"_m = 1, "m"_m = short {55}, "id"_m = 'z'}));
  TTS_EQUAL((kumi::flatten(kumi::tuple {
                "x"_m = 3.25f, kumi::tuple {"y"_m = 2., kumi::tuple {2., "z"_m = 1, short {55}}, short {55}}, "t"_m = 'z'})),
            (kumi::tuple {"x"_m = 3.25f, "y"_m = 2., kumi::tuple {2., "z"_m = 1, short {55}}, short {55}, "t"_m = 'z'}));
};

TTS_CASE("Check tuple::flatten constexpr behavior")
{
  constexpr auto t0 = kumi::tuple {2., 1, short {55}};
  constexpr auto t1 = kumi::tuple {3.25f, kumi::tuple {2., 1, short {55}}, 'z'};
  constexpr auto t2 =
      kumi::tuple {3.25f, kumi::tuple {2., kumi::tuple {2., 1, short {55}}, short {55}}, 'z'};

  TTS_CONSTEXPR_EQUAL(kumi::flatten(kumi::tuple{}), kumi::tuple{});
  TTS_CONSTEXPR_EQUAL(kumi::flatten(t0), (kumi::tuple {2., 1, short {55}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten(t1), (kumi::tuple {3.25f, 2., 1, short {55}, 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten(t2),
                      (kumi::tuple {3.25f, 2., kumi::tuple {2., 1, short {55}}, short {55}, 'z'}));
};

TTS_CASE("Check tuple::flatten constexpr behavior on named tuples")
{
  using namespace kumi::literals;
  constexpr auto t0 = kumi::tuple {"x"_m = 2., 1, "y"_m = short {55}};
  constexpr auto t1 = kumi::tuple {"x"_m = 3.25f, "z"_m = kumi::tuple {2., "t"_m = 1, short {55}}, "id"_m = 'z'};
  constexpr auto t2 =
      kumi::tuple {"x"_m = 3.25f, kumi::tuple {"y"_m = 2., kumi::tuple {2., "z"_m = 1, "t"_m = short {55}}, short {55}}, 'z'};

  TTS_CONSTEXPR_EQUAL(kumi::flatten(t0), (kumi::tuple {"x"_m = 2., 1, "y"_m  = short {55}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten(t1), (kumi::tuple {"x"_m = 3.25f, 2., "t"_m = 1, short {55}, "id"_m = 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten(t2),
                      (kumi::tuple {"x"_m = 3.25f, "y"_m = 2., kumi::tuple {2., "z"_m = 1, "t"_m = short {55}}, short {55}, 'z'}));
};

TTS_CASE("Check tuple::flatten_all behavior")
{
  TTS_EQUAL( kumi::flatten_all(kumi::tuple{}),kumi::tuple{});
  TTS_EQUAL((kumi::flatten_all(kumi::tuple{kumi::tuple{},kumi::tuple{},kumi::tuple{}})),kumi::tuple{});
  TTS_EQUAL((kumi::flatten_all(kumi::tuple {2., 1, short {55}})),
            (kumi::tuple {2., 1, short {55}}));
  TTS_EQUAL((kumi::flatten_all(kumi::tuple {3.25f, kumi::tuple {2., 1, short {55}}, 'z'})),
            (kumi::tuple {3.25f, 2., 1, short {55}, 'z'}));
  TTS_EQUAL((kumi::flatten_all(kumi::tuple {
                3.25f, kumi::tuple {2., kumi::tuple {2., 1, short {55}}, short {55}}, 'z'})),
            (kumi::tuple {3.25f, 2., 2., 1, short {55}, short {55}, 'z'}));
  TTS_EQUAL((kumi::flatten_all(kumi::tuple {
                3.25f, kumi::tuple {2., kumi::tuple{}, short {55}}, 'z'})),
            (kumi::tuple {3.25f, 2., short {55}, 'z'}));
};

TTS_CASE("Check tuple::flatten_all behavior on named tuples")
{
  using namespace kumi::literals;
  TTS_EQUAL((kumi::flatten_all(kumi::tuple {"x"_m = 2., "y"_m = 1, "z"_m = short {55}})),
            (kumi::tuple {"x"_m = 2., "y"_m = 1, "z"_m = short {55}}));
  TTS_EQUAL((kumi::flatten_all(kumi::tuple {"x"_m = 3.25f, "y"_m = kumi::tuple {2., 1, short {55}}, "id"_m = 'z'})),
            (kumi::tuple {3.25f, 2., 1, short {55}, 'z'}));
};

TTS_CASE("Check tuple::flatten_all + function behavior")
{
  auto inc = [](auto m) { return m+1; };

  TTS_EQUAL( kumi::flatten_all(kumi::tuple{}, inc),kumi::tuple{});

  TTS_EQUAL((kumi::flatten_all(kumi::tuple{kumi::tuple{},kumi::tuple{},kumi::tuple{}},inc))
            ,kumi::tuple{}
            );

  TTS_EQUAL((kumi::flatten_all(kumi::tuple {2., 1, short {55}}, inc)),
            (kumi::tuple {3., 2, short {56}}));

  TTS_EQUAL((kumi::flatten_all(kumi::tuple {3.25f, kumi::tuple {2., 1, short {55}}, 'a'}, inc)),
            (kumi::tuple {4.25f, 3., 2, short {56}, 'b'}));

  TTS_EQUAL((kumi::flatten_all(kumi::tuple {
                3.25f, kumi::tuple {2., kumi::tuple {2., 1, short {55}}, short {55}}, 'a'}, inc)),
            (kumi::tuple {4.25f, 3., 3., 2, short {56}, short {56}, 'b'}));

  TTS_EQUAL((kumi::flatten_all(kumi::tuple {
                3.25f, kumi::tuple {2., kumi::tuple{}, short {55}}, 'a'}, inc)),
            (kumi::tuple {4.25f, 3., short {56}, 'b'}));
};

TTS_CASE("Check tuple::flatten_all + function behavior on named tuples")
{
  using namespace kumi::literals;
  auto inc = [](auto m) { return m+1; };

  TTS_EQUAL((kumi::flatten_all(kumi::tuple {"x"_m = 2., "y"_m = 1, "z"_m = short {55}}, inc)),
            (kumi::tuple {3., 2, short {56}}));

  TTS_EQUAL((kumi::flatten_all(kumi::tuple {"x"_m = 3.25f, "y"_m = kumi::tuple {"z"_m = 2., "t"_m = 1, "l"_m = short {55}}, "f"_m = 'a'}, inc)),
            (kumi::tuple {4.25f, 3., 2, short {56}, 'b'}));

  TTS_EQUAL((kumi::flatten_all(kumi::tuple {
                "x"_m = 3.25f, "y"_m = kumi::tuple {"z"_m = 2., "t"_m = kumi::tuple {"x"_m = 2., "y"_m = 1, "z"_m = short {55}},"l"_m = short {55}}, "f"_m = 'a'}, inc)),
            (kumi::tuple {4.25f, 3., 3., 2, short {56}, short {56}, 'b'}));

  TTS_EQUAL((kumi::flatten_all(kumi::tuple {
                "x"_m = 3.25f, "y"_m = kumi::tuple {"z"_m = 2., "t"_m = kumi::tuple{}, "l"_m = short {55}}, "f"_m = 'a'}, inc)),
            (kumi::tuple {4.25f, 3., short {56}, 'b'}));
};

TTS_CASE("Check tuple::flatten_all constexpr behavior")
{
  constexpr auto t0 = kumi::tuple {2., 1, short {55}};
  constexpr auto t1 = kumi::tuple {3.25f, kumi::tuple {2., 1, short {55}}, 'z'};
  constexpr auto t2 = kumi::tuple {3.25f, t0, t1, 'z'};
  constexpr auto te = kumi::tuple {3.25f, kumi::tuple {}, 'z'};

  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(kumi::tuple{}),kumi::tuple{});
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t0), (kumi::tuple {2., 1, short {55}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t1), (kumi::tuple {3.25f, 2., 1, short {55}, 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(te), (kumi::tuple {3.25f, 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t2),
                      (kumi::tuple {3.25f, 2., 1, short {55}, 3.25f, 2., 1, short {55}, 'z', 'z'}));
};

TTS_CASE("Check tuple::flatten_all constexpr behavior on named tuples")
{
  using namespace kumi::literals;
  constexpr auto t0 = kumi::tuple {"x"_m = 2.   , "y"_m = 1, "z"_m = short {55}};
  constexpr auto t1 = kumi::tuple {"x"_m = 3.25f, "y"_m = kumi::tuple {"z"_m = 2., "t"_m = 1, "l"_m = short {55}}, "f"_m = 'z'};
  constexpr auto t2 = kumi::tuple {"x"_m = 3.25f, "y"_m = t0, "z"_m = t1, "t"_m = 'z'};
  constexpr auto te = kumi::tuple {"x"_m = 3.25f, "y"_m = kumi::tuple {}, "t"_m = 'z'};

  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t0), (kumi::tuple {2., 1, short {55}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t1), (kumi::tuple {3.25f, 2., 1, short {55}, 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(te), (kumi::tuple {3.25f, 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t2),
                      (kumi::tuple {3.25f, 2., 1, short {55}, 3.25f, 2., 1, short {55}, 'z', 'z'}));
};

TTS_CASE("Check tuple::flatten_all + function constexpr behavior")
{
  constexpr auto t0 = kumi::tuple {2., 1, short {55}};
  constexpr auto t1 = kumi::tuple {3.25f, kumi::tuple {2., 1, short {55}}, 'a'};
  constexpr auto t2 = kumi::tuple {3.25f, t0, t1, 'a'};
  constexpr auto te = kumi::tuple {3.25f, kumi::tuple {}, 'a'};

  auto inc = [](auto m) { return m+1; };

  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(kumi::tuple{}, inc),kumi::tuple{});
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t0, inc), (kumi::tuple {3., 2, short {56}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t1, inc), (kumi::tuple {4.25f, 3., 2, short {56}, 'b'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(te, inc), (kumi::tuple {4.25f, 'b'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t2, inc),
                      (kumi::tuple {4.25f, 3., 2, short {56}, 4.25f, 3., 2, short {56}, 'b', 'b'}));
};

TTS_CASE("Check tuple::flatten_all + function constexpr behavior on named tuples")
{
  using namespace kumi::literals;
  constexpr auto t0 = kumi::tuple {"x"_m = 2., "y"_m = 1, "z"_m = short {55}};
  constexpr auto t1 = kumi::tuple {"x"_m = 3.25f, "y"_m = kumi::tuple {"z"_m = 2., "t"_m = 1, "l"_m = short {55}}, "f"_m = 'a'};
  constexpr auto t2 = kumi::tuple {"x"_m = 3.25f, "y"_m = t0, "z"_m = t1, "t"_m = 'a'};
  constexpr auto te = kumi::tuple {"x"_m = 3.25f, "y"_m = kumi::tuple {}, "z"_m = 'a'};

  auto inc = [](auto m) { return m+1; };

  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(kumi::tuple{}, inc),kumi::tuple{});
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t0, inc), (kumi::tuple {3., 2, short {56}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t1, inc), (kumi::tuple {4.25f, 3., 2, short {56}, 'b'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(te, inc), (kumi::tuple {4.25f, 'b'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t2, inc),
                      (kumi::tuple {4.25f, 3., 2, short {56}, 4.25f, 3., 2, short {56}, 'b', 'b'}));
};
