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
  //! @defgroup product_types Product_types Classes 
  //! @brief    Class definition and functions on kumi::product_types
  //!
  //! @addtogroup product_types 
  //! @{
  //!   @defgroup tuple     Tuple Types and Functions
  //!   @brief    Definition for kumi::tuple class and functions
  //!   
  //!   @defgroup record    Record Types and Functions
  //!   @brief    Definition for kumi::record class and functions
  //! @}
  //================================================================================================
}

#include <kumi/product_types/tuple.hpp>
#include <kumi/product_types/record.hpp>

namespace kumi::result 
{
    template<product_type... Ts>
    struct common_product_type 
    {
      using type = std::conditional_t<(record_type<Ts> && ...), record<>, tuple<>>;
        //using type = decltype(kumi::common_product_type(std::declval<Ts>()...));
    };

    template<typename... Ts>
    using common_product_type_t = typename common_product_type<Ts...>::type;
}
