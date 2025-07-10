//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace kumi
{

  //================================================================================================
  //! @ingroup transforms
  //! @brief Invoke the Callable object f with a product_type of arguments. f is applied on the
  //!        values if the given product_type is a kumi::record 
  //!
  //! @param f	Callable object to be invoked
  //! @param t  kumi::product_type whose elements to be used as arguments to f
  //! @return The value returned by f.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<typename Function, product_type Tuple> struct apply;
  //!
  //!   template<typename Function, product_type Tuple>
  //!   using apply_t = typename apply<Function,Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::apply
  //!
  //! ## Example
  //! @include doc/apply.cpp
  //! @include doc/record/apply.cpp
  //================================================================================================
  template<std::size_t...Idx, typename Function, product_type Tuple>
  constexpr auto project(Function f, Tuple &&t) 
  {
    if constexpr(sized_product_type<Tuple,0>) return std::remove_cvref_t<Tuple>{};
    else
    {
      return kumi::make_tuple(f(unwrap_if_record<Tuple>(get<Idx>(KUMI_FWD(t))))...);
    }
  }

  namespace result
  {
    template<typename Function, product_type Tuple, std::size_t... Idx>
    struct project    
    {
        using type = decltype(kumi::project<Idx...>(std::declval<Function>()
                                                  , std::declval<Tuple>   ()
                                                  ));
    };

    template<typename Function, product_type Tuple, std::size_t... Idx>
    using project_t = typename project<Function,Tuple, Idx...>::type;
  }
}
