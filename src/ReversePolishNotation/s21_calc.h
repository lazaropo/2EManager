#ifndef _SMART_CALC_ERRORS_
#define _SMART_CALC_ERRORS_
typedef enum { OK, ERROR } def_e_code;
#endif

#ifndef _S21_SMARTCALC_H_FA68C275_D180_43EB_9AAC_F1C629F79E74_
#define _S21_SMARTCALC_H_FA68C275_D180_43EB_9AAC_F1C629F79E74_
// #include <ctype.h>
#include <math.h>
#include <stdbool.h>
// #include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#define BUFF_SIZE 512

typedef struct node_t {
  wchar_t ch;
  double num;
  struct node_t* prev;
} node_t;

typedef struct queue_t {
  wchar_t ch;
  double num;
  struct queue_t* next;
} queue_t;

typedef enum {
  NON_OPERATOR_CH,
  EQUALITY_CH = L'=',
  PLUS_OPERATOR = L'+',
  MINUS_OPERATOR = L'-',
  STAR_OPERATOR = L'*',
  SLASH_OPERATOR = L'/',
  UNARI_PLUS_OPERATOR = L'@',
  UNARI_MINUS_OPERATOR = L'!',
  BRA_CH = L'(',
  KET_CH = L')',
  POW_OPERATOR = L'^',
  COMMA_CH = L',',
  VARIABLE_CH = L'x',
  DOT_CH = L'.',
  LOWER_EXP_CH = L'e',
  UPPER_EXP_CH = L'E',
  DICE_MULTIPLYING_d = L'd',
  DICE_MULTIPLYING_D = L'D',
  DICE_MULTIPLYING_b = L'в',
  DICE_MULTIPLYING_B = L'В',
} set_of_chars;

typedef enum {
  NUMBER_CASE = 1,
  FUNCTION_OR_BRA_CASE,
  SEPARATOR_CASE,
  OPERATOR_CASE,
  KET_CASE
} set_of_cases_for_parser;

typedef enum {
  NON_FUNC,
  MOD_FUNC_CH = L'm',
  COS_FUNC_CH = L'c',
  SIN_FUNC_CH = L's',
  TAN_FUNC_CH = L't',
  ACOS_FUNC_CH = L'a',
  ASIN_FUNC_CH = L'i',
  ATAN_FUNC_CH = L'n',
  SQRT_FUNC_CH = L'r',
  LN_FUNC_CH = L'l',
  LOG_FUNC_CH = L'o',
} set_of_funcs_for_calc;

static const wchar_t map_with_strings[][5] = {
    L"mod", L"cos", L"sin", L"tan", L"acos", L"asin", L"atan", L"sqrt", L"ln", L"log"};
static const wchar_t map_with_chars[] = {
    MOD_FUNC_CH,  COS_FUNC_CH,  SIN_FUNC_CH,  TAN_FUNC_CH, ACOS_FUNC_CH,
    ASIN_FUNC_CH, ATAN_FUNC_CH, SQRT_FUNC_CH, LN_FUNC_CH,  LOG_FUNC_CH};

typedef enum {
  SUM_PR = 1,
  SUB_PR = 1,
  DICE_MULTIPLYING_PR = 3,
  MUL_PR = 3,
  DIV_PR = 3,
  POW_PR = 5,
  MOD_PR = 3,
  UPLUS_PR = 2,   // unary plus
  UMINUS_PR = 2,  // unary minus
  COS_PR = 4,
  SIN_PR = 4,
  TAN_PR = 4,
  ACOS_PR = 4,
  ASIN_PR = 4,
  ATNG_PR = 4,
  SQRT_PR = 4,
  LN_PR = 4,
  LOG_PR = 4,
} operation_priority;

node_t* s21_push(node_t* prev, wchar_t ch, double num);
queue_t* s21_enqueue(queue_t* prev, wchar_t ch, double num);

wchar_t s21_pop(node_t** head, double* ret_num);

void s21_remove_list(node_t** head);
void s21_remove_list_q(queue_t** head);

int s21_is_func(const wchar_t ch);
int s21_is_operator(const wchar_t ch);
int s21_what_is_token(const wchar_t ch);
int s21_get_priority(const wchar_t ch);
int s21_is_func_str(const wchar_t** from);

void s21_parser_from_infix_to_postfix(wchar_t* to, const wchar_t* from);
int s21_parser_postfix_notation(queue_t* root, const wchar_t* from);
int s21_is_expression_correct(const wchar_t* from);
void s21_calculate_by_rule(node_t** head, wchar_t ch);
int s21_calculate(queue_t* head, double* result, double x_value);
int s21_main_calc_function(const wchar_t* expression, double* result,
                           double x_value);
#endif
