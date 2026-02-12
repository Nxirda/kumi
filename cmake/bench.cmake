##======================================================================================================================
##  Copacabana - Common CMake Package Tools
##  Copyright : Copacabana Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
function(COPA_SETUP_BENCH_TARGETS)
  string(TOLOWER ${PROJECT_NAME} NAME)
  set(PROJECT_BENCH_TARGET "${NAME}-bench")
  if(NOT TARGET ${PROJECT_BENCH_TARGET})
    add_custom_target(${PROJECT_BENCH_TARGET})
    set(PROJECT_BENCH_TARGET "${PROJECT_BENCH_TARGET}" PARENT_SCOPE)
  endif()
endfunction()

##======================================================================================================================
## Select a test target build location
##======================================================================================================================
function(COPA_SETUP_BENCH test file location utility args)
  cmake_language(CALL ${utility} ${test} ${file} ${args})
endfunction()

##======================================================================================================================
## Process a list of source files to generate corresponding test target
##======================================================================================================================
function(COPA_MAKE_BENCH)
  set(options         QUIET)
  set(oneValueArgs    INTERFACE EXTENSION ROOT DESTINATION PCH IMPLICIT UTILITY)
  set(multiValueArgs  DEPENDENCIES FILES UTILITY_ARGS)
  cmake_parse_arguments(OPT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  if(NOT ${OPT_QUIET})
    list(LENGTH OPT_FILES NB_TARGETS)
    message(STATUS "[${PROJECT_NAME}] - ${NB_TARGETS} targets generated for ${OPT_ROOT}")
  endif()

  foreach(file ${OPT_FILES})
    copa_source_to_target( "${OPT_EXTENSION}" "${file}" bench)
    copa_setup_bench( ${bench} ${file} "${OPT_DESTINATION}" "${OPT_UTILITY}" "${OPT_UTILITY_ARGS}")
    add_dependencies(${PROJECT_BENCH_TARGET} ${bench})
    #target_include_directories(${bench} PRIVATE "${CMAKE_SOURCE_DIR}/include")
  endforeach()
endfunction()

##==================================================================================================
## Generate benchs from a GLOB
##==================================================================================================
function(COPA_GLOB_BENCH)
  set(options         QUIET IMPLICIT)
  set(oneValueArgs    RELATIVE PATTERN INTERFACE PCH EXTENSION DESTINATION UTILITY)
  set(multiValueArgs  DEPENDENCIES UTILITY_ARGS)
  cmake_parse_arguments(OPT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  if(NOT DEFINED OPT_INTERFACE)
    set(OPT_INTERFACE "")
  endif()

  if(NOT DEFINED OPT_PCH)
    set(OPT_PCH "")
  endif()

  if(NOT DEFINED OPT_DESTINATION)
    set(OPT_DESTINATION "bench")
  endif()

  if(NOT DEFINED OPT_EXTENSION)
    set(OPT_EXTENSION "exe")
  endif()

  if(NOT DEFINED OPT_RELATIVE)
    set(OPT_RELATIVE "${CMAKE_SOURCE_DIR}/bench")
  endif()

  if(NOT DEFINED OPT_PATTERN)
    set(OPT_PATTERN "*.cpp")
  endif()

  if(${OPT_IMPLICIT})
    set(MAKE_IMPLICIT 1)
  else()
    set(MAKE_IMPLICIT 0)
  endif()

  file(GLOB_RECURSE FOUND_FILES CONFIGURE_DEPENDS RELATIVE ${OPT_RELATIVE} ${OPT_PATTERN})

  copa_make_bench(
    INTERFACE     "${OPT_INTERFACE}"
    EXTENSION     "${OPT_EXTENSION}"
    DESTINATION   "${OPT_DESTINATION}"
    DEPENDENCIES  "${OPT_DEPENDENCIES}"
    FILES         "${FOUND_FILES}"
    UTILITY       "${OPT_UTILITY}"
    UTILITY_ARGS  "${OPT_UTILITY_ARGS}"
    ROOT          "${OPT_PATTERN}"
    IMPLICIT      "${OPT_IMPLICIT}"
    QUIET         "${OPT_QUIET}"
  )
  #if(${OPT_QUIET})
  #copa_make_bench( INTERFACE     "${OPT_INTERFACE}"
  #                EXTENSION     "${OPT_EXTENSION}"
  #                DESTINATION   "${OPT_DESTINATION}"
  #                DEPENDENCIES  "${OPT_DEPENDENCIES}"
  #                PCH           "${OPT_PCH}"
  #                FILES         "${FOUND_FILES}"
  #                UTILITY       "${OPT_UTILITY}"
  #                UTILITY_ARGS  "${OPT_UTILITY_ARGS}"
  #                ROOT          "${OPT_PATTERN}"
  #                IMPLICIT      "${MAKE_IMPLICIT}"
  #                QUIET
  #              )
  #else()
  #copa_make_bench( INTERFACE     "${OPT_INTERFACE}"
  #                EXTENSION     "${OPT_EXTENSION}"
  #                DESTINATION   "${OPT_DESTINATION}"
  #                DEPENDENCIES  "${OPT_DEPENDENCIES}"
  #                PCH           "${OPT_PCH}"
  #                FILES         "${FOUND_FILES}"
  #                UTILITY       "${OPT_UTILITY}"
  #                UTILITY_ARGS  "${OPT_UTILITY_ARGS}"
  #                ROOT          "${OPT_PATTERN}"
  #                IMPLICIT      "${MAKE_IMPLICIT}"
  #                QUIET
  #              )
  #endif()
endfunction()
