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
  namespace _
  {
    template<product_type T> struct uniquer
    {
      KUMI_ABI consteval auto operator()() const noexcept
      {
        struct { std::size_t count{1}, t[size_v<T>]; } that = {};
        that.t[0] = 0;
        auto locate = [&]<std::size_t... I>(std::index_sequence<I...>)
        {
          ((  ! std::is_same_v<raw_element_t<I,T>, raw_element_t<I+1,T>> 
              ? (that.t[that.count++] = I+1) : I), ...);
        };

        locate(std::make_index_sequence<size_v<T>-1>{});
        return that;
 
      }
    };

    template<product_type T> inline constexpr uniquer<T> uniqued{};
  }

  namespace _ 
  {
    template<typename Ints, typename... Ts> struct make_unique;

    template <>
    struct make_unique<std::index_sequence<>> { using type = std::true_type; };

    // To be replaced smartly
    template<std::size_t... Is, template<class...> class Box, typename... Ts> 
    struct make_unique<std::index_sequence<Is...>, Box<Ts...>>
    {      
      struct impl : _::unique<Ints, Ts>... {};

      template <typename Us>
      static consteval auto is_set(Us) -> decltype(_::true_fn(static_cast<Us>(all_uniques_inner())));
      static consteval std::false_type is_set(...);

      
      //using type = decltype(is_set(std::type_identity<Ts>{}...));
      
      //T acc;

      //template<typename W>
      //KUMI_ABI friend constexpr decltype(auto) operator | (make_unique &&x, make_unique<W> &&y)
      //{
      //  constexpr auto value = []<std::size_t...I>(std::index_sequence<I...>)
      //  {
      //    return (all_uniques_v<W, raw_element_t<I, T>...>);
      //  }(std::make_index_sequence<size_v<T>>{});
      //  
      //  if constexpr ( value ) return [&]<std::size_t...I>(std::index_sequence<I...>)
      //  {
      //     using res_t = _::builder_make_t<T, element_t<I,T>..., W>;
      //     return _::make_unique{ res_t{ get<I>(KUMI_FWD(x.acc))..., KUMI_FWD(y.acc) } };
      //  }(std::make_index_sequence<size_v<T>>{});
      //  else                   return KUMI_FWD(x);
      //}
    };

    template<typename W> make_unique(W && w) -> make_unique<W>;
  }
  
  //================================================================================================
  //! @ingroup generators
  //! @brief  Returns a product type with consecutive duplicate types removed (pairwise uniqueness).
  //! @param  t Product type to process
  //! @return A product type containing elements from t with consecutive duplicates removed.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi
  //! {
  //!   template<product_type T> struct unique;
  //!
  //!   template<product_type T>
  //!   using unique_t = typename unique<T>::type;
  //! }
  //! @endcode
  //!
  //! Computes the type returned by a call to kumi::unique.
  //!
  //! ## Example:
  //! @include doc/unique.cpp
  //================================================================================================
  template<product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto unique(T && t)
  {
    if constexpr ( sized_product_type<T,0> ) return KUMI_FWD(t);
    else
    {  
      constexpr auto pos = _::uniqued<T>();
      return [&]<std::size_t...I>(std::index_sequence<I...>)
      {
        using ret_t = _::builder_make_t<T, raw_element_t<pos.t[I], T>...>;
        return ret_t{ get<pos.t[I]>(KUMI_FWD(t))... };
      }(std::make_index_sequence<pos.count>{});
    }
  };

  //================================================================================================
  //! @ingroup generators
  //! @brief  Return the product type containing the values of the first occurence of each type 
  //!         in the input product type.
  //! @param  t Product type to process
  //! @return A product type built by keeping the first occurrence of every distinct element type 
  //!         in the input product type.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi
  //! {
  //!   template<product_type T> struct all_unique;
  //!
  //!   template<product_type T>
  //!   using all_unique_t = typename all_unique<T>::type;
  //! }
  //! @endcode
  //!
  //! Computes the type returned by a call to kumi::all_unique.
  //!
  //! ## Example:
  //! @include doc/all_unique.cpp
  //================================================================================================
  template <product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto all_unique(T && t)
  {
    if constexpr ( sized_product_type<T,0> ) return t;
    else
    {
      return [&]<std::size_t...I>(std::index_sequence<I...>)
      {
        return ( _::make_unique{_::builder_make_t<T,raw_element_t<0,T>>{ get<0>(KUMI_FWD(t)) }}
               | ...
               | _::make_unique<raw_element_t<I+1,T>>{ get<I+1>(KUMI_FWD(t)) }).acc;
      }(std::make_index_sequence<size_v<T>-1>{});
    }
  }

  namespace result
  {
    template<product_type T>
    struct unique
    {
      using type = decltype(kumi::unique(std::declval<T>()));
    };

    template<product_type T>
    struct all_unique
    {
      using type = decltype(kumi::all_unique(std::declval<T>())); 
    };

    template<product_type T>
    using unique_t = typename unique<T>::type;

    template<product_type T>
    using all_unique_t = typename all_unique<T>::type;
  }
}
