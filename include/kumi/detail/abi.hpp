//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// Macro to replace std::forward. Better compile-time + less error-prone
#define KUMI_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

#if defined(__CUDACC__)
#   define KUMI_CUDA __host__ __device__
#else
#   define KUMI_CUDA
#endif

#if defined(KUMI_DEBUG)
#   define KUMI_ABI
#elif defined(__GNUC__)
#   define KUMI_ABI [[using gnu : always_inline, flatten, artificial]] KUMI_CUDA inline
#elif defined(_MSC_VER)
#   define KUMI_ABI KUMI_CUDA __forceinline
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wmissing-braces"
#endif
