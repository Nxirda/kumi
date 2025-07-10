
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
  //! ## Example
  //! @include doc/reorder.cpp
  //================================================================================================
  template <product_type Tuple, product_type Layout>
  requires( !record_type<Tuple> )
  [[nodiscard]] constexpr auto reindex(Tuple && tuple, Layout && layout)
  {
    // I think it s necessary to do a make tuple in case we have only 1 tuple
    if constexpr (sized_product_type<Tuple, 0>) return KUMI_FWD(tuple);
    else
    {
      return kumi::apply([&](auto &&... m)
      {
        [[maybe_unused]] auto v_or_t = [&]<typename V>(V&& v) 
        {
          if constexpr(product_type<V>) return kumi::make_tuple(reindex(KUMI_FWD(tuple), KUMI_FWD(v)));
          else                          return kumi::tuple<element_t<v, Tuple>>{ kumi::get<v>(KUMI_FWD(tuple)) };
        };                
        return kumi::cat(v_or_t(KUMI_FWD(m))...);
      }
    , layout);

    }
  }

  namespace result
  {
    template<product_type Tuple, product_type Layout> struct reindex
    {
      using type = decltype( kumi::reindex( std::declval<Tuple>()
                                          , std::declval<Layout>()
                                          )
                           );
    };

    template<product_type Tuple, product_type Layout> 
    using reindex_t = typename reindex<Tuple,Layout>::type;
  }
    

  template <record_type Record, product_type Layout>
  [[nodiscard]] constexpr auto reindex_field(Record && tuple, Layout && layout)
  {
    if constexpr (sized_product_type<Record, 0>)        return KUMI_FWD(tuple);
    else if constexpr (sized_product_type<Layout, 0>)   return kumi::record{};
    else
    {
      return kumi::apply([&](auto &&... m)
      {
        [[maybe_unused]]auto v_or_t = [&]<typename V>(V&& v)         
        {
          if constexpr( product_type<unwrap_field_capture_t<std::remove_cvref_t<V>>>) 
            return kumi::make_record( unwrap_name_v<std::remove_cvref_t<decltype(v)>>
                                    , reindex(KUMI_FWD(tuple), KUMI_FWD(v)));
          else      
          {
            constexpr auto name = field_name<std::remove_cvref_t<V>::name>{};
            return kumi::make_record
                  ( kumi::field_capture<std::remove_cvref_t<V>::name, named_element_t<name, Record>>
                  {kumi::get<name>(KUMI_FWD(tuple))});
          }
        };                
        return kumi::cat(v_or_t(KUMI_FWD(m))...);
      }
    , layout);
    }
  }


  namespace result
  {
    template<product_type Record, product_type Layout> 
    struct reindex_field
    {
      using type = decltype( kumi::reindex_field( std::declval<Record>()
                                                , std::declval<Layout> ()
                                                )
                           );
    };

    template<product_type Record, product_type Layout> 
    using reindex_field_t = typename reindex_field<Record,Layout>::type;
  }

}
