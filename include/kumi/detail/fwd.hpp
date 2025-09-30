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
  // Forward declaration
  struct unit;
  template<typename... Ts>  struct tuple;
  template<typename... Ts>  struct record;

  //template<auto I, typename T>
  //constexpr decltype(auto) get( T && ) noexcept;

  //template<typename T, typename U>
  //constexpr decltype(auto) get( U && ) noexcept;
}