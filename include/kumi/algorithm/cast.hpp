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
  template<typename T>
  [[nodiscard]] KUMI_ABI constexpr auto value_of(T && t)
  {
           if constexpr ( is_field_capture_v<std::remove_cvref_t<T>> )  return KUMI_FWD(t).value; 
      else if constexpr ( sized_product_type<T, 0> )                    return _::builder<T>::make();
      else if constexpr ( record_type<T> ) 
      return [&]<std::size_t...I>(std::index_sequence<I...>)
      {
        return tuple<raw_element_t<I, T>...>{value_of(get<I>(KUMI_FWD(t)))...};
      }(std::make_index_sequence<size_v<T>>{});
      else return KUMI_FWD(t);
  }
   
  template<typename T>
  [[nodiscard]] KUMI_ABI constexpr auto name_of(T && t)
  {
      using unqualified_t = std::remove_cvref_t<T>;
           if constexpr ( is_field_capture_v<unqualified_t> )   return kumi::field_name<unqualified_t::name>{}; 
      else if constexpr ( sized_product_type<T, 0> )            return kumi::none;
      else if constexpr ( record_type<T> ) 
      return [&]<std::size_t...I>(std::index_sequence<I...>)
      {
        return tuple{ name_of(get<I>(KUMI_FWD(t)))... };
      }(std::make_index_sequence<size_v<T>>{});
      else return kumi::none; 
  }

  template<product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto decompose(T && t)
  {
    if constexpr ( sized_product_type<T, 0> ) return _::builder<T>::make();
    else return kumi::tuple{ name_of(KUMI_FWD(t)), value_of(KUMI_FWD(t)) };
  };

  //================================================================================================
  //! @ingroup utility
  //! @brief Converts a kumi::product_type to an instance of an other kumi::product_type
  //!
  //! @tparam Target kumi::product_type to generate 
  //! @param  b kumi::product_type to convert
  //! @return A product_type of type containing the values of b
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Target, product_type Base> struct product_type_cast;
  //!
  //!   template<product_type Target, Product_type Base>
  //!   using product_type_cast_t = typename product_type_cast<Target, Base>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::product_type_cast
  //!
  //! ## Example
  //! @include doc/product_type_cast.cpp
  //! @include doc/record/product_type_cast.cpp
  //================================================================================================
  template<product_type Target, product_type Base>
  requires(  _::supports_piecewise_cast<Base, Target>
          && ( size_v<Base> == size_v<Target> )
          && ( !std::same_as<Base, Target> )
          && ( !record_type<Target> )
          )
  [[nodiscard]] KUMI_ABI constexpr auto structural_cast(Base && b)
  {
         if constexpr ( sized_product_type<Base,0> ) return _::builder<Base>::make();
    else if constexpr ( record_type<Base> )
    {
      auto &&[names, values] = decompose(KUMI_FWD(b));
      return _::builder<Base>::combine(KUMI_FWD(names), structural_cast<Target>(KUMI_FWD(values)));
    }
    else return [&]<std::size_t...I>(std::index_sequence<I...>)
    {
      return _::builder<Base>::make( (v_or_t(index<I>, get<I>(KUMI_FWD(b))))... );
    }(std::make_index_sequence<size_v<Base>>{});
  }

  //================================================================================================
  //! @ingroup utility
  //! @brief Converts a kumi::product_type to an instance of an other kumi::product_type
  //!
  //! @tparam Target kumi::product_type to generate 
  //! @param  b kumi::product_type to convert
  //! @return A product_type of type Target containing the values of b
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Target, product_type Base> struct product_type_cast;
  //!
  //!   template<product_type Target, Product_type Base>
  //!   using product_type_cast_t = typename product_type_cast<Target, Base>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::product_type_cast
  //!
  //! ## Example
  //! @include doc/product_type_cast.cpp
  //! @include doc/record/product_type_cast.cpp
  //================================================================================================
  template<product_type Target, product_type Base>
  requires(  _::supports_recursive_piecewise_cast<Base, Target>
          && ( size_v<Base> == size_v<Target> )
          && ( !std::same_as<Base, Target> )
          && ( !record_type<Target> )
          )
  [[nodiscard]] KUMI_ABI constexpr auto recursive_structural_cast(Base && b)
  {
         if constexpr ( sized_product_type<Base,0> ) return _::builder<Base>::make();
    else if constexpr ( record_type<Base> )
    {
      auto &&[names, values] = decompose(KUMI_FWD(b));
      return _::builder<Base>::combine(KUMI_FWD(names), recursive_structural_cast<Target>(KUMI_FWD(values)));
    }
    else return [&]<std::size_t...I>(std::index_sequence<I...>)
    {
      auto v_or_t = []<typename V>(auto J, V && v)
      {
        using target_t = element_t<J, Target>;
        if constexpr ( product_type<V> ) return recursive_structural_cast<target_t>(KUMI_FWD(v));
        else                             return static_cast<target_t>(KUMI_FWD(v));
      };

      return _::builder<Base>::make( (v_or_t(index<I>, get<I>(KUMI_FWD(b))))... );
    }(std::make_index_sequence<size_v<Base>>{});
  }


  //================================================================================================
  //! @ingroup utility
  //! @brief Converts a kumi::product_type to an instance of an other kumi::product_type
  //!
  //! @tparam Target the type to which to convert 
  //! @param  b kumi::tuple to convert
  //! @return A tuple containing the values of b where each member is of type Target 
  //!
  //! @note : member_cast only operates on one level of the tuple, see `recursive_member_cast`
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Target, product_type Base> struct member_cast;
  //!
  //!   template<product_type Target, Product_type Base>
  //!   using member_cast_t = typename member_cast<Target, Base>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::member_cast
  //!
  //! ## Examples
  //! @include doc/member_cast.cpp
  //! @include doc/record/member_cast.cpp
  //================================================================================================
  template<typename Target, product_type Base>
  requires( _::supports_unary_cast<Base, Target> )
  [[nodiscard]] KUMI_ABI constexpr auto member_cast(Base && b)
  {
         if constexpr ( sized_product_type<Base, 0> ) return _::builder<Base>::make();
    else if constexpr ( record_type<Base> )
    {  
      auto &&[names, values] = decompose(KUMI_FWD(b));
      return _::builder<Base>::combine(KUMI_FWD(names), member_cast<Target>(KUMI_FWD(values)));
    }
    else return apply([](auto &&... elts)
    {
      return _::builder<Base>::make(v_or_t(KUMI_FWD(elts))...);
    }, KUMI_FWD(b));
  }

  //================================================================================================
  //! @ingroup utility
  //! @brief Converts a kumi::product_type to an instance of an other kumi::product_type
  //!
  //! @tparam Target the type to which to convert 
  //! @param  b kumi::tuple to convert
  //! @return A tuple containing the values of b where each member is of type Target
  //!
  //! @ note : recursive_member_cast keeps nested tuple and only convert values, see `member_cast`
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Target, product_type Base> struct member_cast;
  //!
  //!   template<product_type Target, Product_type Base>
  //!   using member_cast_t = typename member_cast<Target, Base>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::member_cast
  //!
  //! ## Examples
  //! @include doc/member_cast.cpp
  //! @include doc/record/member_cast.cpp
  //================================================================================================
  template<typename Target, product_type Base>
  requires( _::supports_recursive_unary_cast<Base, Target> )
  [[nodiscard]] KUMI_ABI constexpr auto recursive_member_cast(Base && b)
  {
         if constexpr ( sized_product_type<Base, 0> ) return _::builder<Base>::make();
    else if constexpr ( record_type<Base> )
    {
      auto &&[names, values] = decompose(KUMI_FWD(b)); 
      return _::builder<Base>::combine(KUMI_FWD(names), recursive_member_cast<Target>(KUMI_FWD(values)));
    }
    else return apply([](auto &&... elts)
    {
      auto v_or_t = []<typename V>(V && v)
      {
        if constexpr(product_type<V>) return recursive_member_cast<Target>(KUMI_FWD(v));
        else                          return static_cast<Target>(KUMI_FWD(v));
      };
      
      return _::builder<Base>::make(v_or_t(KUMI_FWD(elts))...);
    }, KUMI_FWD(b));
  }

  namespace result
  {
    template<product_type Target, product_type Base> struct structural_cast 
    {
      using type = decltype( kumi::structural_cast<Target, Base>( std::declval<Base>() ) );
    };

    template<product_type Target, product_type Base> struct recursive_structural_cast 
    {
      using type = decltype( kumi::recursive_structural_cast<Target, Base>( std::declval<Base>() ) );
    };
    
    template<typename Target, product_type Base> struct member_cast 
    {
      using type = decltype( kumi::member_cast<Target, Base>( std::declval<Base>() ) );
    };
   
    template<typename Target, product_type Base> struct recursive_member_cast 
    {
      using type = decltype( kumi::recursive_member_cast<Target, Base>( std::declval<Base>() ) );
    };

    template<product_type Target, product_type Base>
    using structural_cast_t = typename structural_cast<Target,Base>::type;

    template<product_type Target, product_type Base>
    using recursive_structural_cast_t = typename recursive_structural_cast<Target,Base>::type;

    template<typename Target, product_type Base>
    using member_cast_t = typename member_cast<Target,Base>::type;

    template<typename Target, product_type Base>
    using recursive_member_cast_t = typename recursive_member_cast<Target,Base>::type;
  }
}
