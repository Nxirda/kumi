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

TTS_CASE("Check result::reorder<record,I...> behavior")
{
  using char_f      = kumi::field_capture<"a", char>;
  using short_f     = kumi::field_capture<"b", short>;
  using int_f       = kumi::field_capture<"c", int>;
  using double_f    = kumi::field_capture<"d", double>;

  using record_t = kumi::record<char_f,short_f,int_f,double_f>;

  TTS_TYPE_IS( (kumi::result::reorder_t<record_t,0,1,2,3>), record_t                              );
  TTS_TYPE_IS( (kumi::result::reorder_t<record_t,1,2,3,0>), (kumi::record<short_f,int_f,double_f,char_f>) );
  TTS_TYPE_IS( (kumi::result::reorder_t<record_t,3,3>    ), (kumi::tuple<double_f,double_f>)         );
  TTS_TYPE_IS( (kumi::result::reorder_t<record_t>        ), kumi::record<>                        );
};

TTS_CASE("Check reorder<I...>(record) behavior")
{
  using namespace kumi::literals;

  {
    auto t = kumi::record {"a"_f = 1, "b"_f = 2., "c"_f = 3.4f, "d"_f = '5'};

    {
      auto s = kumi::reorder<0,1,2,3>(t);
      TTS_EQUAL(s, t);
    }

    {
      auto s = kumi::reorder<3,2,1,0>(t);
      TTS_EQUAL(s, (kumi::record{"d"_f = '5',"c"_f = 3.4f,"b"_f = 2.,"a"_f = 1}));
    }

    {
      auto s = kumi::reorder<0,1,2>(t);
      TTS_EQUAL(s, (kumi::record{"a"_f = 1,"b"_f = 2.,"c"_f = 3.4f}) );
    }

    {
      auto s = kumi::reorder<0,1>(t);
      TTS_EQUAL(s, (kumi::record{"a"_f = 1,"b"_f = 2.}) );
    }

    {
      auto s = kumi::reorder<0>(t);
      TTS_EQUAL(s, (kumi::record{"a"_f = 1}) );
    }

    {
      auto s = kumi::reorder<1>(t);
      TTS_EQUAL(s, (kumi::record{"b"_f = 2.}) );
    }

    {
      auto s = kumi::reorder<2>(t);
      TTS_EQUAL(s, (kumi::record{"c"_f = 3.4f}) );
    }

    {
      auto s = kumi::reorder<3>(t);
      TTS_EQUAL(s, (kumi::record{"d"_f = '5'}) );
    }

    {
      auto s = kumi::reorder<0,1,2,3,2,1,0>(t);
      TTS_EQUAL(s, (kumi::tuple{"a"_f = 1,"b"_f = 2.,"c"_f = 3.4f,"d"_f = '5',"c"_f = 3.4f,"b"_f = 2.,"a"_f = 1}) );
    }
  }
};

TTS_CASE("Check reorder<I...>(record) constexpr behavior")
{
  using namespace kumi::literals;

  {
    constexpr auto t = kumi::record {"a"_f = 1, "b"_f = 2., "c"_f = 3.4f, "d"_f = '5'};

    {
      constexpr auto s = kumi::reorder<0,1,2,3>(t);
      TTS_CONSTEXPR_EQUAL(s, t);
    }

    {
      constexpr auto s = kumi::reorder<3,2,1,0>(t);
      TTS_CONSTEXPR_EQUAL(s, (kumi::record{"d"_f = '5',"c"_f = 3.4f,"b"_f = 2.,"a"_f = 1}));
    }

    {
      constexpr auto s = kumi::reorder<0,1,2>(t);
      TTS_CONSTEXPR_EQUAL(s, (kumi::record{"a"_f = 1,"b"_f = 2.,"c"_f = 3.4f}) );
    }

    {
      constexpr auto s = kumi::reorder<0,1>(t);
      TTS_CONSTEXPR_EQUAL(s, (kumi::record{"a"_f = 1,"b"_f = 2.}) );
    }

    {
      constexpr auto s = kumi::reorder<0>(t);
      TTS_CONSTEXPR_EQUAL(s, (kumi::record{"a"_f = 1}) );
    }

    {
      constexpr auto s = kumi::reorder<1>(t);
      TTS_CONSTEXPR_EQUAL(s, (kumi::record{"b"_f = 2.}) );
    }

    {
      constexpr auto s = kumi::reorder<2>(t);
      TTS_CONSTEXPR_EQUAL(s, (kumi::record{"c"_f = 3.4f}) );
    }

    {
      constexpr auto s = kumi::reorder<3>(t);
      TTS_CONSTEXPR_EQUAL(s, (kumi::record{"d"_f = '5'}) );
    }

    {
      constexpr auto s = kumi::reorder<0,1,2,3,2,1,0>(t);
      TTS_CONSTEXPR_EQUAL(s, (kumi::tuple{"a"_f = 1,"b"_f = 2.,"c"_f = 3.4f,"d"_f = '5',"c"_f = 3.4f,"b"_f = 2.,"a"_f = 1}) );
    }
  }
};
