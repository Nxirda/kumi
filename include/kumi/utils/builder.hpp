//======================================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace kumi
{ 
  //================================================================================================
  //! @ingroup traits 
  //! @brief   Extracts the common product_type of a parameter pack, if all the types are `record`
  //!          then it returns an empty record, otherwise returns an empty `kumi::tuple`
  //!
  //! @tparam Ts The `product_types` to access
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<typename... Ts> using common_product_type_t 
  //!       = typename common_product_type<Ts...>::type;
  //! }
  //! @endcode
  //================================================================================================
  /*template<product_type... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto common_product_type(Ts...)
  {
      if constexpr (( record_type<Ts> && ... )) return kumi::record{};
      else                                      return kumi::tuple{};   
  }*/

  namespace _
  {
    //================================================================================================
    //! @ingroup tuple
    //! @class builder 
    //! @brief Helper structure to build the correct output `product_type`. If the provided Typle
    //!        is a not a record_type the builder will output a tuple otherwise a record. 
    //!
    //! builder provides a generic way of defining a kumi::product_type which depending on the 
    //! given semantic (product_type or record_type) will output respectively a kumi::tuple or a 
    //! kumi::record
    //!
    //! @tparam T the template template type to be built. 
    //================================================================================================

    template<typename T>
    struct builder
    {
      using type = std::remove_cvref_t<T>;
      
      /// rebind aggregate utility
      template<typename... Us> using to = type;    

      /// relies on brace init and CTAD on a concrete type
      template<typename... Args>
      requires requires(Args&&... args) { type{ std::forward<Args>(args)... }; }
      static constexpr auto build(Args&&... args)
      {
        return type{ std::forward<Args>(args)... };
      }

      /// relies on a enforcing the type of an aggregate
      template<typename... Args>
      requires requires(Args&&... args) { type{ std::forward<Args>(args)... }; }
      static constexpr auto make(Args&&... args)
      {
        return type{ std::forward<Args>(args)... };
      }
    };

    template <typename T>
    using builder_t = typename builder<T>::type;

    template<typename T, typename... Args>
    using builder_make_t = typename builder<T>::template to<Args...>;
  }
}
