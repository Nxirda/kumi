//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#define TTS_MAIN
#include <kumi/tuple.hpp>
#include <tts/tts.hpp>

using namespace kumi;

TTS_CASE("Check result::reindex<Tuple, Idx_tuple, Idx_tuples...> behavior")
{
  using base_tuple  = kumi::tuple<int, float, char*, short&, double&&, const long&>;
  /*using base_record = kumi::record< kumi::field_capture<"a", int        >,
                                    kumi::field_capture<"b", float      >,
                                    kumi::field_capture<"c", char*      >,
                                    kumi::field_capture<"d", short&     >,
                                    kumi::field_capture<"e", double&   >,
                                    kumi::field_capture<"f", const long&>>;*/
   
  using ref_t           = kumi::tuple<index_t<0>, index_t<1>, index_t<2>
                                    , index_t<3>, index_t<4>, index_t<5>>;
  using duplicates_t    = kumi::tuple<index_t<0>, index_t<1>, index_t<2>, index_t<1>, index_t<0>>;
  using complex_t       = kumi::tuple<index_t<4>, index_t<3>, index_t<0>
                                     , kumi::tuple<index_t<5>,index_t<1>, index_t<2>>>;
 
  TTS_TYPE_IS((kumi::result::reindex_t<base_tuple, kumi::tuple<>>), (kumi::tuple<>));
  //TTS_TYPE_IS((kumi::result::reindex_t<base_record, kumi::tuple<>>), (kumi::record<>));

  TTS_TYPE_IS((kumi::result::reindex_t<kumi::tuple<>, ref_t>), (kumi::tuple<>));
  //TTS_TYPE_IS((kumi::result::reindex_t<kumi::record<>, ref_t>), (kumi::record<>));
  TTS_TYPE_IS( (kumi::result::reindex_t<base_tuple, ref_t>), (base_tuple));
  //TTS_TYPE_IS( (kumi::result::reindex_t<base_record, ref_t>), (base_record));

  TTS_TYPE_IS( (kumi::result::reindex_t<base_tuple, duplicates_t>), (kumi::tuple<int, float, char*, float, int>));
  
  TTS_TYPE_IS( (kumi::result::reindex_t<base_tuple, complex_t>), 
                (kumi::tuple<double, short, int, kumi::tuple<long, float, char*>> ));
};

/*
TTS_CASE("Check result::reindex<Record, Name_tuple, Name_tuples...> behavior")
{
  using base_record = kumi::record< kumi::field_capture<"a", int        >,
                                    kumi::field_capture<"b", float      >,
                                    kumi::field_capture<"c", char*      >,
                                    kumi::field_capture<"d", short&     >,
                                    kumi::field_capture<"e", double&   >,
                                    kumi::field_capture<"f", const long&>>;
   
  using ref_t           = kumi::tuple<kumi::field_name<"a">, kumi::field_name<"b">, kumi::field_name<"c">
                                    , kumi::field_name<"d">, kumi::field_name<"e">, kumi::field_name<"d">>;
  
  using duplicates_t    = kumi::tuple<kumi::field_name<"a">, kumi::field_name<"b">, kumi::field_name<"c">,
                                      kumi::tuple<kumi::field_name<"a">, kumi::field_name<"b">, kumi::field_name<"c">>>;

  TTS_TYPE_IS((kumi::result::reindex_field_t<base_record, kumi::tuple<>>), (kumi::record<>));
  TTS_TYPE_IS((kumi::result::reindex_field_t<kumi::record<>, ref_t>), (kumi::record<>));

  TTS_TYPE_IS( (kumi::result::reindex_field_t<base_record, ref_t>), (base_record));

  TTS_TYPE_IS( (kumi::result::reindex_field_t<base_record, duplicates_t>)
             , (kumi::record<kumi::field_capture<"a", int>,
                             kumi::field_capture<"b", float>,
                             kumi::field_capture<"c", char*>,
                             kumi::record<  kumi::field_capture<"a", int>,
                                            kumi::field_capture<"b", float>,
                                            kumi::field_capture<"c", char*>
                                         >
                            >));
};*/
