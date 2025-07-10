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
  template<product_type Tuple, typename Pred>
  [[nodiscard]] constexpr auto filter(Tuple && t, Pred &&p) noexcept
  {
    if constexpr (sized_product_type<Tuple, 0>) return t;
    else
    {
      return kumi::apply( [&](auto &&...m)
                          {
                            auto v_or_t = [&]<typename V>(V&& v)
                            {
                              if constexpr ( product_type<V> ) return kumi::make_tuple(filter(KUMI_FWD(v), KUMI_FWD(p)));
                              else return KUMI_FWD(p)(KUMI_FWD(v))  
                                    ? kumi::tuple<std::remove_cvref_t<decltype(v)>>{KUMI_FWD(v)} 
                                    : kumi::tuple{};
                            };
                            return kumi::cat(v_or_t(KUMI_FWD(m))...);
                          }, t 
                        );
    }
  }

  namespace result
  {
    template<product_type Tuple, typename Pred>
    struct project    
    {
        using type = decltype(kumi::filter( std::declval<Tuple>()
                                          , std::declval<Pred>()
                                          ));
    };

    template<product_type Tuple, typename Pred>
    using project_t = typename project<Tuple, Pred>::type;
  }
}
