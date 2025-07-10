//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kumi/utils/concepts.hpp>
#include <kumi/utils/traits.hpp>
#include <array>
#include <type_traits>
#include <utility>

#if !defined(KUMI_DOXYGEN_INVOKED)
//==================================================================================================
// Structured binding adaptation
//==================================================================================================
template<std::size_t I, typename Head, typename... Tail>
struct  std::tuple_element<I, kumi::tuple<Head, Tail...>>
      : std::tuple_element<I - 1, kumi::tuple<Tail...>>
{
};

template<std::size_t I, typename... Ts> struct std::tuple_element<I, kumi::tuple<Ts...> const>
{
  using type = typename tuple_element<I, kumi::tuple<Ts...>>::type const;
};

template<typename Head, typename... Tail> struct std::tuple_element<0, kumi::tuple<Head, Tail...>>
{
  using type = Head;
};

template<typename... Ts>
struct std::tuple_size<kumi::tuple<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>
{
};

//==================================================================================================
// Structured binding adaptation for records
//==================================================================================================
template<std::size_t I, typename Head, typename... Tail>
struct  std::tuple_element<I, kumi::record<Head, Tail...>>
      : std::tuple_element<I - 1, kumi::tuple<Tail...>>
{
};

template<std::size_t I, typename... Ts> struct std::tuple_element<I, kumi::record<Ts...> const>
{
  using type = typename tuple_element<I, kumi::record<Ts...>>::type const;
};

template<typename Head, typename... Tail> struct std::tuple_element<0, kumi::record<Head, Tail...>>
{
  using type = Head;
};

///
template<auto Field, typename Record> struct named_element;

// 
template<auto Field, auto Name, typename T, typename... Tail>
struct named_element<Field, kumi::tuple< kumi::field_capture<Name,T>, Tail... >>
{
  using type = T;
};

template<auto Field, typename Head, typename... Tail>
struct named_element<Field, kumi::tuple<Head, Tail...>>
  : named_element<Field, kumi::tuple<Tail...>>
{ };

template<auto Field, typename... Fs>
struct named_element<Field, kumi::tuple<Fs...> const>
{
  using type = typename named_element<Field, kumi::tuple<Fs...>>::type const;
};

template<auto Field, typename Record>
using named_element_t = typename named_element<Field, Record>::type;


template<typename... Ts>
struct std::tuple_size<kumi::record<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>
{
};

#if !defined( __ANDROID__ )
//==================================================================================================
// Common Reference support
//==================================================================================================
template< typename... Ts, typename... Us
        , template<class> class TQual, template<class> class UQual >
requires(sizeof...(Ts) == sizeof...(Us))
struct std::basic_common_reference<kumi::tuple<Ts...>, kumi::tuple<Us...>, TQual, UQual>
{
  using type = kumi::tuple<std::common_reference_t<TQual<Ts>, UQual<Us>>...>;
};
#endif

//==================================================================================================
// Standard array support
//==================================================================================================
#if !defined(KUMI_NO_STD_ADAPTORS)
template< typename T, std::size_t N >
struct kumi::is_product_type<std::array<T , N>> : std::true_type {};
#endif

#endif
