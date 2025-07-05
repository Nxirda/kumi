//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kumi/detail/builder.hpp>

namespace kumi
{
  //================================================================================================
  //! @ingroup generators
  //! @brief Transpose a tuple of tuples by shifting elements in their transposed position
  //!
  //! @param t Tuple to transpose
  //! @return A tuple containing the transposed elements of t.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple> struct transpose;
  //!
  //!   template<product_type Tuple>
  //!   using transpose_t = typename transpose<Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::transpose
  //!
  //! ## Example
  //! @include doc/transpose.cpp
  //================================================================================================
  template<product_type Tuple> [[nodiscard]] constexpr auto transpose(Tuple const &t)
  {
    using base_t = std::remove_cvref_t<Tuple>;
    if constexpr(sized_product_type<Tuple,0>) return t;
    else if constexpr ( record_type<std::remove_cvref_t<Tuple>> )
    {
      using first_t = std::remove_cvref_t<raw_element_t<0, Tuple>>;
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        constexpr auto uz = [&]<typename N>(N const &, auto const &u) 
        {
          using field_t = field_name<member_name_v<N::value, first_t>>;

          return _::apply_field([&](auto const &...m) 
                { 
                    return builder<base_t>
                        ::make( field_name<unwrap_name_v<std::remove_cvref_t<decltype(m)>>>{} = get<field_t{}>(unwrap_field_value(m))...); 
                }, u);
                                                                                         };
        return kumi::record{ ( field_name<member_name_v<I, first_t>>{} = uz(index_t<I>{}, t) )...};
      }
      (std::make_index_sequence<size<raw_element_t<0,Tuple>>::value>());
    }
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        constexpr auto uz = []<typename N>(N const &, auto const &u) {
          return apply([](auto const &...m) { return builder<base_t>::make(get<N::value>(m)...); }, u);
        };

        return builder<base_t>::make(uz(index_t<I>{}, t)...);
      }
      (std::make_index_sequence<size<element_t<0,Tuple>>::value>());
    }
  }

  namespace result
  {
    template<product_type Tuple> struct transpose
    {
      using type = decltype( kumi::transpose( std::declval<Tuple>() ) );
    };

    template<product_type Tuple>
    using transpose_t = typename transpose<Tuple>::type;
  }
}
