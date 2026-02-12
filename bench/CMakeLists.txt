##======================================================================================================================
##  KUMI - Compact C++20 Tuple Toolbox
##  Copyright : KUMI Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
copa_setup_bench_targets()
set(root "${CMAKE_SOURCE_DIR}/bench")

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -std=c++20
    -ftime-trace
    -ftime-trace-granularity=1)

##======================================================================================================================
## Benchmark tests
##======================================================================================================================
copa_glob_bench(QUIET PATTERN "*.cpp" INTERFACE kumi_bench RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
                UTILITY "ctbench_add_benchmark" UTILITY_ARGS "1;16;1;10")


ctbench_add_graph(test_graph compare.json tuple.requires)
