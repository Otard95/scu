#include <check.h>
#include <stdlib.h>

#define SCU_SV_IMPLEMENTATION
#include "../scu_string_view.h"

START_TEST(sanity_check)
{
  ck_assert(1 == 1);
}
END_TEST

START_TEST(string_view_from_cstr)
{
  Scu_String_View sv = scu_sv_from_cstr("hello");
  ck_assert_str_eq(sv.buf, "hello");
  ck_assert_int_eq(sv.len, 5);
}
END_TEST

START_TEST(string_view_from_buffer)
{
  Scu_String_View sv = scu_sv_from_buffer("hello", 5);
  ck_assert_str_eq(sv.buf, "hello");
  ck_assert_int_eq(sv.len, 5);
}
END_TEST

START_TEST(string_view_equals)
{
  Scu_String_View sv1 = scu_sv_from_cstr("hello");
  Scu_String_View sv2 = scu_sv_from_cstr("hello");
  Scu_String_View sv3 = scu_sv_from_cstr("world");
  Scu_String_View sv4 = scu_sv_from_cstr("foobarbaz");

  ck_assert(scu_sv_eq(sv1, sv2));
  ck_assert(!scu_sv_eq(sv1, sv3));
  ck_assert(!scu_sv_eq(sv1, sv4));
}
END_TEST

START_TEST(string_view_trim_right)
{
  Scu_String_View sv1 = scu_sv_from_cstr("hello");
  Scu_String_View sv1_trimmed = scu_sv_trim_right(sv1);

  ck_assert_str_eq(sv1_trimmed.buf, "hello");
  ck_assert_int_eq(sv1.len, 5);
  ck_assert_int_eq(sv1_trimmed.len, 5);

  Scu_String_View sv2 = scu_sv_from_cstr("hello  ");
  Scu_String_View sv2_trimmed = scu_sv_trim_right(sv2);

  ck_assert(memcmp(sv2_trimmed.buf, "hello", 5) == 0);
  ck_assert_int_eq(sv2.len, 7);
  ck_assert_int_eq(sv2_trimmed.len, 5);
}
END_TEST

START_TEST(string_view_trim_left)
{
  Scu_String_View sv1 = scu_sv_from_cstr("hello");
  Scu_String_View sv1_trimmed = scu_sv_trim_left(sv1);

  ck_assert_str_eq(sv1_trimmed.buf, "hello");
  ck_assert_int_eq(sv1.len, 5);
  ck_assert_int_eq(sv1_trimmed.len, 5);

  Scu_String_View sv2 = scu_sv_from_cstr("  hello");
  Scu_String_View sv2_trimmed = scu_sv_trim_left(sv2);

  ck_assert(memcmp(sv2_trimmed.buf, "hello", 5) == 0);
  ck_assert_int_eq(sv2.len, 7);
  ck_assert_int_eq(sv2_trimmed.len, 5);
}
END_TEST

START_TEST(string_view_trim)
{
  Scu_String_View sv1 = scu_sv_from_cstr("hello");
  Scu_String_View sv1_trimmed = scu_sv_trim(sv1);

  ck_assert_str_eq(sv1_trimmed.buf, "hello");
  ck_assert_int_eq(sv1.len, 5);
  ck_assert_int_eq(sv1_trimmed.len, 5);

  Scu_String_View sv2 = scu_sv_from_cstr("  hello  ");
  Scu_String_View sv2_trimmed = scu_sv_trim(sv2);

  ck_assert(memcmp(sv2_trimmed.buf, "hello", 5) == 0);
  ck_assert_int_eq(sv2.len, 9);
  ck_assert_int_eq(sv2_trimmed.len, 5);
}

Suite * string_view_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("String Builder");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, sanity_check);
    tcase_add_test(tc_core, string_view_from_cstr);
    tcase_add_test(tc_core, string_view_from_buffer);
    tcase_add_test(tc_core, string_view_equals);
    tcase_add_test(tc_core, string_view_trim_right);
    tcase_add_test(tc_core, string_view_trim_left);
    tcase_add_test(tc_core, string_view_trim);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = string_view_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
