
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

TTS_CASE("Check == operator on kumi::tuple")
{
  using namespace kumi::literals;

  // Ref
  kumi::tuple t1 = {1};
  kumi::tuple t2 = {1.f, 2};
  kumi::tuple t3 = {1., 2.f, 3};
  kumi::tuple t4 = {'1', 2., 3.f, 4};

  // Named
  kumi::tuple tn1 = {"x"_m = 1};
  kumi::tuple tn2 = {"x"_m = 1.f, "y"_m = 2};
  kumi::tuple tn3 = {"x"_m = 1., "y"_m = 2.f, "z"_m = 3 };
  kumi::tuple tn4 = {"x"_m = '1', "y"_m = 2., "z"_m = 3.f, "t"_m = 4};

  // Named and permuted
  kumi::tuple tnp2 = {"y"_m = 2, "x"_m = 1.f };
  kumi::tuple tnp3 = {"x"_m = 1., "z"_m = 3,  "y"_m = 2.f};
  kumi::tuple tnp4 = {"t"_m = 4, "z"_m = 3.f, "y"_m = 2., "x"_m = '1'};

  // Partially named
  kumi::tuple tp2 = {1.f, "y"_m = 2};
  kumi::tuple tp3 = {"x"_m = 1., 2.f,  "y"_m = 3};
  kumi::tuple tp4 = {'1', 2., "z"_m = 3.f, "y"_m = 4};
   
  TTS_EQUAL(t1, tn1);
  
  TTS_EQUAL(t2, tp2);
  TTS_EQUAL(t2, tn2);
  TTS_EQUAL(t2, tp2);
  TTS_NOT_EQUAL(tn2, tnp2);
  TTS_EQUAL(tn2, tp2);

  TTS_EQUAL(t3, tp3);
  TTS_EQUAL(t3, tn3);
  TTS_EQUAL(t3, tp3);
  TTS_NOT_EQUAL(tn3, tnp3);
  TTS_EQUAL(tn3, tp3);

  TTS_EQUAL(t4, tp4);
  TTS_EQUAL(t4, tn4);
  TTS_EQUAL(t4, tp4);
  TTS_NOT_EQUAL(tn4, tnp4);
  TTS_EQUAL(tn4, tp4);
};

TTS_CASE("Check constexpr access to kumi::tuple via indexing")
{
  using namespace kumi::literals;

  // Ref
  constexpr kumi::tuple t1 = {1};
  constexpr kumi::tuple t2 = {1.f, 2};
  constexpr kumi::tuple t3 = {1., 2.f, 3};
  constexpr kumi::tuple t4 = {'1', 2., 3.f, 4};

  // Named
  constexpr kumi::tuple tn1 = {"x"_m = 1};
  constexpr kumi::tuple tn2 = {"x"_m = 1.f, "y"_m = 2};
  constexpr kumi::tuple tn3 = {"x"_m = 1., "y"_m = 2.f, "z"_m = 3 };
  constexpr kumi::tuple tn4 = {"x"_m = '1', "y"_m = 2., "z"_m = 3.f, "t"_m = 4};

  // Named and permuted
  constexpr kumi::tuple tnp2 = {"y"_m = 2, "x"_m = 1.f };
  constexpr kumi::tuple tnp3 = {"x"_m = 1., "z"_m = 3,  "y"_m = 2.f};
  constexpr kumi::tuple tnp4 = {"t"_m = 4, "z"_m = 3.f, "y"_m = 2., "x"_m = '1'};

  // Partially named
  constexpr kumi::tuple tp2 = {1.f, "y"_m = 2};
  constexpr kumi::tuple tp3 = {"x"_m = 1., 2.f,  "y"_m = 3};
  constexpr kumi::tuple tp4 = {'1', 2., "z"_m = 3.f, "y"_m = 4};
    
  TTS_EQUAL(t1, tn1);
  
  TTS_EQUAL(t2, tp2);
  TTS_EQUAL(t2, tn2);
  TTS_EQUAL(t2, tp2);
  TTS_NOT_EQUAL(tn2, tnp2);
  TTS_EQUAL(tn2, tp2);

  TTS_EQUAL(t3, tp3);
  TTS_EQUAL(t3, tn3);
  TTS_EQUAL(t3, tp3);
  TTS_NOT_EQUAL(tn3, tnp3);
  TTS_EQUAL(tn3, tp3);

  TTS_EQUAL(t4, tp4);
  TTS_EQUAL(t4, tn4);
  TTS_EQUAL(t4, tp4);
  TTS_NOT_EQUAL(tn4, tnp4);
  TTS_EQUAL(tn4, tp4);
};
