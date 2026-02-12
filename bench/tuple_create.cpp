#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

#include <kumi/kumi.hpp>

#define FOO_MAX 16

#define DECL(z, i, nope)                                                                                               \
  struct id##i                                                                                                         \
  {                                                                                                                    \
  };

BOOST_PP_REPEAT(BENCHMARK_SIZE, DECL, FOO_MAX);
#undef DECL

#define T_INST(z, i, _)                                                                                                \
  id##i {}

void build()
{
  [[maybe_unused]] auto a = kumi::tuple{BOOST_PP_ENUM(BENCHMARK_SIZE, T_INST, ~)};
}

#undef T_INST
