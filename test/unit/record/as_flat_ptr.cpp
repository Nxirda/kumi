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

using namespace kumi::literals;

TTS_CASE("Check record::as_flat_ptr function behavior")
{
  auto t = kumi::record{"a"_f = 3.25f, "b"_f = kumi::record {"c"_f = 2., "d"_f = 
                        kumi::record{"e"_f = 2., "f"_f = 1, "g"_f = short {55}}, "h"_f = short {55}}, "i"_f  ='a'};
  auto f = kumi::as_flat_ptr(t);

  TTS_EQUAL(kumi::get<"a"_f>      (f), &                                    kumi::get<"a"_f>(t)   );
  TTS_EQUAL(kumi::get<"b.c"_f>    (f), &                  kumi::get<"c"_f>( kumi::get<"b"_f>(t) ) );
  TTS_EQUAL(kumi::get<"b.d.e"_f>  (f), &kumi::get<"e"_f>( kumi::get<"d"_f>( kumi::get<"b"_f>(t))) );
  TTS_EQUAL(kumi::get<"b.d.f"_f>  (f), &kumi::get<"f"_f>( kumi::get<"d"_f>( kumi::get<"b"_f>(t))) );
  TTS_EQUAL(kumi::get<"b.d.g"_f>  (f), &kumi::get<"g"_f>( kumi::get<"d"_f>( kumi::get<"b"_f>(t))) );
  TTS_EQUAL(kumi::get<"b.h"_f>    (f), &                  kumi::get<"h"_f>( kumi::get<"b"_f>(t) ) );
  TTS_EQUAL(kumi::get<"i"_f >     (f), &                                    kumi::get<"i"_f>(t)   );

};
