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
  //! @brief Reorder elements of a kumi::product_type
  //!
  //! This function does not participate in overload resolution if any IDx is outside [0, size_v<T>[.
  //!
  //! @note Nothing prevent the number of reordered index to be lesser or greater than t size or
  //!       the fact they can appear multiple times.
  //!
  //! @tparam Idx     Reordered index of elements
  //! @param  t kumi::product_type to reorder
  //! @return A tuple equivalent to kumi::make_tuple(t[index<Idx>]...);
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple,std::size_t... Idx> struct reorder;
  //!
  //!   template<product_type Tuple,std::size_t... Idx>
  //!   using reorder_t = typename reorder<Tuple,Idx...>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::reorder
  //!
  //! ## Examples:
  //! @include doc/reorder.cpp
  //! @include doc/record/reorder.cpp
  //================================================================================================
  template<std::size_t... Idx, product_type Tuple>
  requires((Idx < size_v<Tuple>) && ...)
  [[nodiscard]] KUMI_ABI constexpr auto reorder(Tuple &&t)
  {
    return _::builder<Tuple>::make( get<Idx>(KUMI_FWD(t))... );
  }

  //================================================================================================
  //! @ingroup generators
  //! @brief Reorder elements of a kumi::record
  //!
  //! This function does not participate in overload resolution if the names are not in T
  //!
  //! @note Nothing prevent the number of reordered names to be lesser or greater than t size or
  //!       the fact they can appear multiple times if it is applied on a named tuple. 
  //!
  //! @tparam Name     Reordered names of elements
  //! @param  t kumi::product_type to reorder
  //! @return A product type equivalent to product_type(t[index<Idx>]...);
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple,std::size_t... Idx> struct reorder_fields;
  //!
  //!   template<product_type Tuple,std::size_t... Idx>
  //!   using reorder_fields_t = typename reorder_fields<Tuple,Idx...>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::reorder_fields
  //!
  //! ## Example
  //! @include doc/record/reorder_fields.cpp
  //================================================================================================
  template<field_name... Name, product_type Tuple>
  requires ( requires { get<Name>(std::declval<Tuple>()); } && ... )
  KUMI_ABI constexpr auto reorder_fields(Tuple && t)
  {
    return _::builder<Tuple>::make( field_name<Name.name>{} = get<Name>(KUMI_FWD(t))... );
  }

  namespace result
  {
    template<product_type Tuple, std::size_t... Idx>
    struct reorder
    {
      using type = decltype( kumi::reorder<Idx...>( std::declval<Tuple>() ) );
    };

     template<product_type Tuple, field_name... Name>
    struct reorder_fields
    {
      using type = decltype( kumi::reorder_fields<Name...>( std::declval<Tuple>() ) );
    };

    template<product_type Tuple, std::size_t... Idx>
    using reorder_t = typename reorder<Tuple,Idx...>::type;

    template<product_type Tuple, field_name... Name>
    using reorder_fields_t = typename reorder_fields<Tuple,Name...>::type;   
  }
}
