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
  /*template<typename To, product_type From>
  [[nodiscard]] inline constexpr decltype(auto) rebind(From&& t)
  {
    using Base = std::remove_cvref_t<From>;
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      using type = builder_t<std::remove_cvref_t<To>, std::tuple_element_t<I, Base>...>;
      return type{ ([&]<std::size_t J>(std::integral_constant<std::size_t, J>)
          {
              using current_t   = std::remove_cvref_t<std::tuple_element_t<J, Base>>;
              using get_t       = std::remove_cvref_t<kumi::member_t<J, Base>>;
              if constexpr ( is_field_capture_v<current_t> && !is_field_capture_v<get_t>)
              {
                return KUMI_FWD( field_capture<current_t::name, typename current_t::type>{ get<J>(KUMI_FWD(t)) } );
              }
              else
                return KUMI_FWD( get<J>(KUMI_FWD(t)) );
          }(std::integral_constant<std::size_t, I>{}))...
      };
    }
    (std::make_index_sequence<kumi::size_v<From>>{});
  }*/
    
  template<std::size_t I, product_type PT>
  constexpr decltype(auto) keep_element_type(PT&& t)
  {
    using type          = std::remove_cvref_t<PT>; 
    using current_t     = std::remove_cvref_t<std::tuple_element_t<I, type>>;
    using get_t         = std::remove_cvref_t<kumi::member_t<I, type>>;
    if constexpr ( is_field_capture_v<current_t> && !is_field_capture_v<get_t>)
        return field_capture<current_t::name, typename current_t::type>{ get<I>(KUMI_FWD(t)) };
    else
        return get<I>(KUMI_FWD(t));
  }

  template<typename PT>
  requires ( product_type<std::remove_cvref_t<PT>> )
  struct tuple_view   
  {
    PT base;
    using type = std::remove_cvref_t<PT>;
    using is_product_type = void;

    constexpr explicit tuple_view(PT t) noexcept : base(t) {}

    static constexpr auto size()  noexcept { return kumi::size_v<type>;  };
    static constexpr auto empty() noexcept { return kumi::size_v<type> == 0; };
  };
  
  template<product_type PT> tuple_view(PT) -> tuple_view<PT>;


  template<std::size_t I, product_type T>
  //requires(I < sizeof...(Ts)) KUMI_TRIVIAL_NODISCARD 
  constexpr decltype(auto) 
  get(tuple_view<T> &t) noexcept
  {
    return keep_element_type<I>(static_cast<T &>(t.base));
  }

  /// @overload
  template<std::size_t I, product_type T>
  //requires(I < sizeof...(Ts)) KUMI_TRIVIAL_NODISCARD 
  constexpr decltype(auto)
  get(tuple_view<T> &&arg) noexcept
  {
    return keep_element_type<I>(static_cast<T &&>(arg.base)); 
  }

  /// @overload
  template<std::size_t I, product_type T>
  //requires(I < sizeof...(Ts)) KUMI_TRIVIAL_NODISCARD 
  constexpr decltype(auto)
  get(tuple_view<T> const &arg) noexcept
  {
    return keep_element_type<I>(static_cast<T const&>(arg.base)); 
  }

  /// @overload
  template<std::size_t I, product_type T>
  //requires(I < sizeof...(Ts)) KUMI_TRIVIAL_NODISCARD 
  constexpr decltype(auto)
  get(tuple_view<T> const &&arg) noexcept
  {
    return keep_element_type<I>(static_cast<T const &&>(arg.base));
  }

}

template<std::size_t I, kumi::product_type T>
struct std::tuple_element<I, kumi::tuple_view<T>> : std::tuple_element<I, std::remove_cvref_t<T>> {};

template<kumi::product_type T>
struct std::tuple_size<kumi::tuple_view<T>> : std::tuple_size<std::remove_cvref_t<T>> {};
