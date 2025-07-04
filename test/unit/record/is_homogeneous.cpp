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
#include <array>
#include <concepts>

TTS_CASE("Check is_homogeneous for kumi::record")
{
  using aint_f = kumi::field_capture<"a", int>;
  using bint_f = kumi::field_capture<"b", int>;
  using cint_f = kumi::field_capture<"c", int>;
  using dint_f = kumi::field_capture<"d", int>;
  using float_f = kumi::field_capture<"f", float>;

  TTS_CONSTEXPR_EXPECT_NOT( kumi::record<>::is_homogeneous                     );
  TTS_CONSTEXPR_EXPECT    ( kumi::record<aint_f>::is_homogeneous                  );
  TTS_CONSTEXPR_EXPECT    ((kumi::record<aint_f,bint_f>::is_homogeneous             ));
  TTS_CONSTEXPR_EXPECT_NOT((kumi::record<aint_f,float_f>::is_homogeneous           ));
  TTS_CONSTEXPR_EXPECT    ((kumi::record<aint_f,bint_f,cint_f>::is_homogeneous         ));
  TTS_CONSTEXPR_EXPECT_NOT((kumi::record<aint_f,float_f,cint_f>::is_homogeneous       ));
  TTS_CONSTEXPR_EXPECT    ((kumi::record<aint_f,bint_f,cint_f,dint_f>::is_homogeneous     ));
  TTS_CONSTEXPR_EXPECT_NOT((kumi::record<aint_f,float_f,cint_f,dint_f>::is_homogeneous   ));

  TTS_CONSTEXPR_EXPECT_NOT( kumi::homogeneous_product_type<kumi::record<>>                    );
  TTS_CONSTEXPR_EXPECT    ( kumi::homogeneous_product_type<kumi::record<aint_f>>                 );
  TTS_CONSTEXPR_EXPECT    ( kumi::homogeneous_product_type<kumi::record<aint_f>>                 );
  TTS_CONSTEXPR_EXPECT    ((kumi::homogeneous_product_type<kumi::record<aint_f,bint_f>>            ));
  TTS_CONSTEXPR_EXPECT_NOT((kumi::homogeneous_product_type<kumi::record<aint_f,float_f>>          ));
  TTS_CONSTEXPR_EXPECT    ((kumi::homogeneous_product_type<kumi::record<aint_f,bint_f,cint_f>>        ));
  TTS_CONSTEXPR_EXPECT_NOT((kumi::homogeneous_product_type<kumi::record<aint_f,float_f,cint_f>>      ));
  TTS_CONSTEXPR_EXPECT    ((kumi::homogeneous_product_type<kumi::record<aint_f,bint_f,cint_f,dint_f>>    ));
  TTS_CONSTEXPR_EXPECT_NOT((kumi::homogeneous_product_type<kumi::record<aint_f,float_f,cint_f,dint_f>>  ));
};

/*
template<typename T, bool isHomogeneous>
struct trivial_product_type : kumi::record<T,T,T,T,T>
{};

template<typename T>
struct trivial_product_type<T,false> : kumi::record<T,T,T,T,void*>
{};

template<typename T, bool B>
struct std::record_size<trivial_product_type<T,B>> : std::integral_constant<std::size_t,5>
{};

template<std::size_t N, typename T, bool B>
struct std::record_element<N,trivial_product_type<T,B>> { using type = T; };

template<typename T>
struct std::record_element<4,trivial_product_type<T,false>> { using type = void*; };

TTS_CASE("Check is_homogeneous for kumi::record derived types")
{
  TTS_CONSTEXPR_EXPECT((trivial_product_type<int,true>::is_homogeneous                ));
  TTS_CONSTEXPR_EXPECT((kumi::homogeneous_product_type<trivial_product_type<int,true>>));

  TTS_CONSTEXPR_EXPECT_NOT((trivial_product_type<int,false>::is_homogeneous                ));
  TTS_CONSTEXPR_EXPECT_NOT((kumi::homogeneous_product_type<trivial_product_type<int,false>>));
};

struct some_box
{
  using is_product_type = void;

  int i;
  float f;
  char c;

  template<std::size_t I>
  friend constexpr auto const& get(some_box const& s) noexcept requires(I < 3)
  {
    if constexpr(I==0) return s.i;
    if constexpr(I==1) return s.f;
    if constexpr(I==2) return s.c;
  }

  template<std::size_t I>
  friend  constexpr auto & get(some_box& s) noexcept requires(I < 3)
  {
    if constexpr(I==0) return s.i;
    if constexpr(I==1) return s.f;
    if constexpr(I==2) return s.c;
  }
};

template<> struct std::record_size<some_box> : std::integral_constant<std::size_t,3> {};
template<> struct std::record_element<0,some_box> { using type = int;   };
template<> struct std::record_element<1,some_box> { using type = float; };
template<> struct std::record_element<2,some_box> { using type = char;  };

TTS_CASE("Check is_homogeneous for kumi::product_type adapted types")
{
  TTS_CONSTEXPR_EXPECT((kumi::homogeneous_product_type<std::array<int,7>>));
  TTS_CONSTEXPR_EXPECT_NOT((kumi::homogeneous_product_type<some_box>));
};*/
