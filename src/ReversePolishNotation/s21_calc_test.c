#include <check.h>

#include "s21_test.h"

START_TEST(test_1) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"2*4*5*(6)";

  double result = 0;
  double expect = 240;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_1: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_2) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"8*sin(6)";

  double result = 0;
  double expect = -2.23532398559;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_2: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_3) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"log(16)";

  double result = 0;
  double expect = 1.20411998266;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_3: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_4) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"6^5-14*2";

  double result = 0;
  double expect = 7748;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_4: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_5) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"6mod4";

  double result = 0;
  double expect = 2;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_5: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_6) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"-0";

  double result = 0;
  double expect = 0.;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_6: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_8) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"-25+6-8";

  double result = 0;
  double expect = -27;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_8: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_9) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"+10+10+5";

  double result = 0;
  double expect = 25;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_9: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_10) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"15+75*1/3-42+3^3";

  double result = 0;
  double expect = 25;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_10: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_11) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"sin(0.6)";

  double result = 0;
  double expect = 0.56464247339;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_11: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_12) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"acos(3*0.08)";

  double result = 0;
  double expect = 1.32843048;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_12: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_13) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"atan(-0.4)";

  double result = 0;
  double expect = -0.3805064;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_13: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_14) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"tan(-6)";

  double result = 0;
  double expect = 0.2910062;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_14: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_15) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"sqrt(256.5)";

  double result = 0;
  double expect = 16.0156174;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_15: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_16) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"ln(10)";

  double result = 0;
  double expect = 2.3025851;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_16: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_17) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"log(125)";

  double result = 0;
  double expect = 2.096910;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_17: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_18) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"()";

  double result = 0;
  double expect = 0;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_18: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_19) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"3-(-3)";

  double result = 0;
  double expect = 6;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_19: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_20) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"3-(+3)";

  double result = 0;
  double expect = 0;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_20: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_21) {
  printf("---------------------------------------------\n");
  wchar_t *prompt = L"1+2+3+4*5*6^7";

  double result = 0;
  double expect = 5598726.;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_21: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_22) {
  printf("---------------------------------------------\n");
  wchar_t *prompt = L"123.456+2*3^4";

  double result = 0;
  double expect = 285.456;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_22: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_23) {
  printf("---------------------------------------------\n");
  wchar_t *prompt = L"(8+2*5)/(1+3*2-4)";

  double result = 0;
  double expect = 6.;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_23: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_24) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt =
      L"(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";

  double result = 0;
  double expect = 10;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_24: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_25) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt = L"cos(1*2)-1";

  double result = 0;
  double expect = -1.41614683655;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_25: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_26) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt =
      L"cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";

  double result = 0;
  double expect = -1.83907152908;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_26: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_27) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt =
      L"cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";

  double result = 0;
  double expect = -1.839071529076;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_27: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_28) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt = L"2.33mod1";

  double result = 0;
  double expect = 0.33;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_28: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_29) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt = L"3+4*2/(1-5)^2";

  double result = 0;
  double expect = 3.5;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_29: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_30) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt = L"3+x";

  double result = 0;
  double expect = 13;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 10);

  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_30: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_31) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt = L"3+sqrt(x*1e2)";

  double result = 0;
  double expect = 23;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 4);

  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_31: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_32) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt = L"1.11e5";

  double result = 0;
  double expect = 111000;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 4);

  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_32: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_33) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt = L"1.11e5";

  double result = 0;
  double expect = 111000;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 4);

  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_33: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_34) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt = L"cos(x";

  int e_code = 0;
  e_code += s21_is_expression_correct(prompt);

  bool is_ok = e_code == ERROR ? true : false;
  printf("s21_test_34: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, ERROR);
}
END_TEST

START_TEST(test_35) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt = L"cos(x,";

  double result = 0;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 4);

  bool is_ok = e_code == ERROR ? true : false;
  printf("s21_test_35: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, ERROR);
}
END_TEST

START_TEST(test_36) {
  printf("\n---------------------------------------------\n");
  wchar_t *prompt = L"cos(0+0+0)-(tg(0)-1)";

  double result = 0;
  double expect = 2;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 4);

  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_36: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(e_code, OK);
  ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

START_TEST(test_37) {
  printf("---------------------------------------------\n");

  wchar_t *prompt = L"6d6";

  double result = 0;
  double expect = 240;
  int e_code = 0;
  e_code += s21_main_calc_function(prompt, &result, 0);
  bool is_ok = e_code == OK && fabs(result - expect) < EPS ? true : false;
  printf("s21_test_37: ");
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\nINPUT: %ls\nOUTPUT%15.10f\nEXPECTED:%15.10f\n", prompt, result,
         expect);
  printf("\n---------------------------------------------\n");

  // ck_assert_int_eq(e_code, OK);
  // ck_assert_double_eq_tol(result, expect, EPS);
}
END_TEST

int main() {
  Suite *s1 = suite_create("s21_smart_calc: ");
  TCase *tc1_1 = tcase_create("s21_smart_calc: ");
  SRunner *sr = srunner_create(s1);
  int result;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, test_1);
  tcase_add_test(tc1_1, test_2);
  tcase_add_test(tc1_1, test_3);
  tcase_add_test(tc1_1, test_4);
  tcase_add_test(tc1_1, test_5);
  tcase_add_test(tc1_1, test_6);
  tcase_add_test(tc1_1, test_8);
  tcase_add_test(tc1_1, test_9);
  tcase_add_test(tc1_1, test_10);
  tcase_add_test(tc1_1, test_11);
  tcase_add_test(tc1_1, test_12);
  tcase_add_test(tc1_1, test_13);
  tcase_add_test(tc1_1, test_14);
  tcase_add_test(tc1_1, test_15);
  tcase_add_test(tc1_1, test_16);
  tcase_add_test(tc1_1, test_17);
  tcase_add_test(tc1_1, test_18);
  tcase_add_test(tc1_1, test_19);
  tcase_add_test(tc1_1, test_20);
  tcase_add_test(tc1_1, test_21);
  tcase_add_test(tc1_1, test_22);
  tcase_add_test(tc1_1, test_23);
  tcase_add_test(tc1_1, test_24);
  tcase_add_test(tc1_1, test_25);
  tcase_add_test(tc1_1, test_26);
  tcase_add_test(tc1_1, test_27);
  tcase_add_test(tc1_1, test_28);
  tcase_add_test(tc1_1, test_29);
  tcase_add_test(tc1_1, test_30);
  tcase_add_test(tc1_1, test_31);
  tcase_add_test(tc1_1, test_32);
  tcase_add_test(tc1_1, test_33);
  tcase_add_test(tc1_1, test_34);
  tcase_add_test(tc1_1, test_35);
  tcase_add_test(tc1_1, test_36);
  tcase_add_test(tc1_1, test_37);

  srunner_run_all(sr, CK_ENV);

  result = srunner_ntests_failed(sr);

  srunner_free(sr);

  return result == 0 ? 0 : 1;
}
