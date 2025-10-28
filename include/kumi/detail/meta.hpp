//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kumi/utils/as.hpp>

namespace kumi
{
  //================================================================================================
  //! @ingroup product_types 
  //! @brief Extracts the value from a kumi::field_capture or returns the parameter 
  //!
  //! @note If the unqualified type of T is not a field_capture returns kumi::none.
  //! @tparam   T The name to extract name from. 
  //! @return   The name of the field_capture or kumi::none.
  //! @related kumi::field_capture
  //================================================================================================
  template<typename T>
  [[nodiscard]] KUMI_ABI constexpr auto name_of( as<T> ) noexcept
  {
    using U = std::remove_cvref_t<T>;
    if constexpr ( requires{U::is_field_capture;} ) return U::name;
    else                                            return kumi::none;
  }
  
  //================================================================================================
  //! @ingroup product_types 
  //! @brief Extracts the value from a kumi::field_capture or returns the parameter 
  //!
  //! @note If the unqualified type of T is not a field_capture, simply forwards the parameter
  //! @tparam   T The type to unwrap 
  //! @param    t A forwarding reference to the input object.
  //! @return   A forwarded value of the unwrapped object.
  //! @related kumi::field_capture
  //================================================================================================
  template<typename T>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) field_value_of( T && t ) noexcept
  {
    using U = std::remove_cvref_t<T>;
    if constexpr ( requires {U::is_field_capture;} )  return _::get_field(KUMI_FWD(t));
    else                                              return KUMI_FWD(t);
  }

  namespace _ 
  {
    template <typename T, typename... Ts>
    [[nodiscard]] KUMI_ABI consteval std::size_t index_of_type() noexcept {
        std::size_t idx = 0;
        [[maybe_unused]] bool b = ((std::same_as<T, Ts> ? true : (++idx, false)) || ...);  
        return idx;
    }

    template <kumi::str Name, typename... Ts>
    [[nodiscard]] KUMI_ABI consteval std::size_t index_of_name() noexcept {
        std::size_t idx = 0;
        [[maybe_unused]] bool found = (([&] {
        if constexpr (std::same_as<decltype(name_of(as<Ts>{})), kumi::str>) {
            if (name_of(as<Ts>{}) == Name) return true;
        } 
        return (++idx, false);
        }() || ...));
        return idx;
    }
  }

}
