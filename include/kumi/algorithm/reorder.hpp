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
  //! @return A kumi::product_type equivalent to product_type(t[index<Idx>]...);
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type T,std::size_t... Idx> struct reorder;
  //!
  //!   template<product_type T,std::size_t... Idx>
  //!   using reorder_t = typename reorder<T,Idx...>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::reorder
  //!
  //! ## Example
  //! @include doc/reorder.cpp
  //================================================================================================
  template<std::size_t... Idx, product_type T>
  requires((Idx < size_v<T>) && ...)
  [[nodiscard]] KUMI_ABI constexpr auto reorder(T &&t)
  {
    return _::builder<T>::make( get<Idx>(KUMI_FWD(t))... );
  }

  namespace result
  {
    template<product_type T, std::size_t... Idx>
    struct reorder
    {
      using type = decltype( kumi::reorder<Idx...>( std::declval<T>() ) );
    };

    template<product_type T, std::size_t... Idx>
    using reorder_t = typename reorder<T,Idx...>::type;
  }
}
