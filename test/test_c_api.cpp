#include <scope/test.h>

#include "lightgrep_c_api.h"
#include "basic.h"

SCOPE_TEST(testDedupeOnDiffEncodings) {
  std::shared_ptr<ParserHandle> parser(lg_create_parser(0), lg_destroy_parser);
  LG_KeyOptions opts;
  opts.FixedString = 1;
  opts.CaseInsensitive = 0;

  lg_add_keyword(parser.get(), "apple", 5, 0, &opts, "ASCII");
  lg_add_keyword(parser.get(), "apple", 5, 0, &opts, "UTF-8");

  LG_ProgramOptions progOpts;
  progOpts.Determinize = 1;
  std::shared_ptr<ProgramHandle> prog(lg_create_program(parser.get(), &progOpts),
                                   lg_destroy_program);

  std::shared_ptr<ContextHandle> ctx(lg_create_context(prog.get(), 0),
                                    lg_destroy_context);
}
