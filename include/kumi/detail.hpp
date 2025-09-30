//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//==================================================================================================
//! @namespace kumi
//! @brief Main KUMI namespace
//==================================================================================================
namespace kumi
{
  //================================================================================================
  //! @defgroup detail   Helper Types and Functions
  //! @brief    Tools for interacting with kumi::tuple
  //!
  //! @defgroup concepts     Tuple Related Concepts
  //! @brief    Definition for product types related Concepts
  //!
  //! @defgroup traits     Tuple Related Traits
  //! @brief    Definition for kumi::tuple traits and extension points
  //================================================================================================
}

#include <cstdint>
#include <ostream>
#include <utility>
#include <kumi/detail/stdfix.hpp>
#include <kumi/detail/fwd.hpp>

#include <kumi/detail/abi.hpp>
#include <kumi/detail/binder.hpp>
#include <kumi/detail/optimized.hpp>
#include <kumi/detail/str.hpp>
#include <kumi/detail/unique.hpp>