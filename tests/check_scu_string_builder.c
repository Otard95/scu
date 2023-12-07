#include <check.h>
#include <stdlib.h>

#define SCU_SB_IMPLEMENTATION
#include "../scu_string_builder.h"

START_TEST(sanity_check)
{
  ck_assert(1 == 1);
}
END_TEST

START_TEST(string_builder_append)
{
  Scu_String_Builder sb = {0};

  const char *str = "hello";
  scu_sb_append(&sb, str, 5);

  ck_assert_mem_eq(sb.buf, str, 5);
  ck_assert_int_eq(sb.len, 5);
  ck_assert_int_eq(sb.capacity, 5);

  scu_sb_free(&sb);
}
END_TEST

START_TEST(string_builder_append_cstr)
{
  Scu_String_Builder sb = {0};

  scu_sb_append_cstr(&sb, "hello");

  ck_assert_str_eq(sb.buf, "hello");
  ck_assert_int_eq(sb.len, 5);
  ck_assert_int_eq(sb.capacity, 5);

  scu_sb_free(&sb);
}
END_TEST

START_TEST(string_builder_append_char)
{
  Scu_String_Builder sb = {0};

  scu_sb_append_cstr(&sb, "hello");
  scu_sb_append_char(&sb, '!');

  ck_assert_str_eq(sb.buf, "hello!");
  ck_assert_int_eq(sb.len, 6);
  ck_assert_int_eq(sb.capacity, 8);
  ck_assert(sb.buf[5] == '!');

  scu_sb_free(&sb);
}
END_TEST

START_TEST(string_builder_to_cstr)
{
  Scu_String_Builder sb = {0};

  scu_sb_append_cstr(&sb, "hello");
  scu_sb_append_char(&sb, '!');

  ck_assert(sb.buf[sb.len - 1] != '\0');

  char *str = scu_sb_to_cstr(&sb);

  ck_assert(sb.buf[sb.len - 1] == '\0');
  ck_assert_str_eq(str, "hello!");

  scu_sb_free(&sb);
}
END_TEST

Suite * string_builder_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("String Builder");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, sanity_check);
    tcase_add_test(tc_core, string_builder_append);
    tcase_add_test(tc_core, string_builder_append_cstr);
    tcase_add_test(tc_core, string_builder_append_char);
    tcase_add_test(tc_core, string_builder_to_cstr);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = string_builder_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
