#define NOB_IMPLEMENTATION
#include "./nob.h"

#define SCU_SB_IMPLEMENTATION
#include "scu_string_builder.h"

#define CFLAGS "-Wall", "-Wextra", "-pedantic"

bool build_and_run_test(const char *test_name) {
  Scu_String_Builder sb_out = {0};
  scu_sb_append_cstr(&sb_out, "tests/");
  scu_sb_append_cstr(&sb_out, test_name);

  Scu_String_Builder sb_input = {0};
  scu_sb_append_cstr(&sb_input, "tests/");
  scu_sb_append_cstr(&sb_input, test_name);
  scu_sb_append_cstr(&sb_input, ".c");

  char *out = scu_sb_to_cstr(&sb_out);
  char *input = scu_sb_to_cstr(&sb_input);

  if (out == NULL || input == NULL) {
    nob_log(NOB_ERROR, "could not create output or input file name");
    return false;
  }

  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "cc");
  nob_cmd_append(&cmd, CFLAGS);
  nob_cmd_append(&cmd, "-o", out);
  nob_cmd_append(&cmd, input);
  nob_cmd_append(&cmd, "-lcheck");
  if (!nob_cmd_run_sync(cmd)) {
    return false;
  }

  cmd.count = 0;
  nob_cmd_append(&cmd, out);
  if (!nob_cmd_run_sync(cmd)) {
    return false;
  }

  return true;
}

int main(int argc, char *argv[]) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  if (!build_and_run_test("check_scu_string_builder")) {
    return 1;
  }

  if (!build_and_run_test("check_scu_string_view")) {
    return 1;
  }

  return 0;
}
