#include <locale.h>

#include "s21_calc.h"

int s21_is_func(const wchar_t ch) {
  int e_code;
  switch (ch) {
    case MOD_FUNC_CH:
    case COS_FUNC_CH:
    case SIN_FUNC_CH:
    case TAN_FUNC_CH:
    case ACOS_FUNC_CH:
    case ASIN_FUNC_CH:
    case ATAN_FUNC_CH:
    case SQRT_FUNC_CH:
    case LN_FUNC_CH:
    case LOG_FUNC_CH: {
      e_code = ch;
      break;
    }
    default: {
      e_code = NON_FUNC;
      break;
    }
  }
  return e_code;
}

int s21_is_operator(const wchar_t ch) {
  int e_code;
  switch (ch) {
    case PLUS_OPERATOR:
    case MINUS_OPERATOR:
    case UNARI_MINUS_OPERATOR:
    case STAR_OPERATOR:
    case SLASH_OPERATOR:
    case POW_OPERATOR:
    case DICE_MULTIPLYING_d:
    case DICE_MULTIPLYING_D:
    case DICE_MULTIPLYING_b:
    case DICE_MULTIPLYING_B: {
      e_code = ch;
      break;
    }
    default: {
      e_code = NON_OPERATOR_CH;
      break;
    }
  }
  return e_code;
}

int s21_what_is_token(const wchar_t ch) {
  int e_code = 0;
  if (isdigit(ch) || ch == VARIABLE_CH)
    e_code = NUMBER_CASE;
  else if (s21_is_func(ch) || ch == BRA_CH)
    e_code = FUNCTION_OR_BRA_CASE;
  else if (ch == COMMA_CH)
    e_code = SEPARATOR_CASE;
  else if (s21_is_operator(ch))
    e_code = OPERATOR_CASE;
  else if (ch == KET_CH)
    e_code = KET_CASE;
  return e_code;
}

int s21_get_priority(const wchar_t ch) {
  int e_code;
  switch (ch) {
    case PLUS_OPERATOR: {
      e_code = SUM_PR;
      break;
    }
    case MINUS_OPERATOR: {
      e_code = SUB_PR;
      break;
    }
    case STAR_OPERATOR: {
      e_code = MUL_PR;
      break;
    }
    case SLASH_OPERATOR: {
      e_code = DIV_PR;
      break;
    }
    case POW_OPERATOR: {
      e_code = POW_PR;
      break;
    }
    case DICE_MULTIPLYING_d:
    case DICE_MULTIPLYING_D:
    case DICE_MULTIPLYING_b:
    case DICE_MULTIPLYING_B: {
      e_code = DICE_MULTIPLYING_PR;
      break;
    }
    case UNARI_MINUS_OPERATOR: {
      e_code = UMINUS_PR;
      break;
    }
    case MOD_FUNC_CH: {
      e_code = MOD_PR;
      break;
    }
    case COS_FUNC_CH: {
      e_code = COS_PR;
      break;
    }
    case SIN_FUNC_CH: {
      e_code = SIN_PR;
      break;
    }
    case TAN_FUNC_CH: {
      e_code = TAN_PR;
      break;
    }
    case ACOS_FUNC_CH: {
      e_code = ACOS_PR;
      break;
    }
    case ASIN_FUNC_CH: {
      e_code = ASIN_PR;
      break;
    }
    case ATAN_FUNC_CH: {
      e_code = ATNG_PR;
      break;
    }
    case SQRT_FUNC_CH: {
      e_code = SQRT_PR;
      break;
    }
    case LN_FUNC_CH: {
      e_code = LN_PR;
      break;
    }
    case LOG_FUNC_CH: {
      e_code = LOG_PR;
      break;
    }
    default: {
      e_code = NON_OPERATOR_CH;
      break;
    }
  }
  return e_code;
}

int s21_parser_postfix_notation(queue_t* root, const wchar_t* from) {
  if (!from || !root) return ERROR;

  setlocale(LC_ALL, "en_US.UTF-8");

  int e_code = OK;
  bool is_unary = true;
  queue_t* head = root;
  node_t* stack = NULL;
  double tmp_num = 0;
  while (*from && *from != EQUALITY_CH && e_code == OK) {
    switch (s21_what_is_token(*from)) {
      case NUMBER_CASE: {
        if (*from == VARIABLE_CH)
          head = s21_enqueue(head, VARIABLE_CH, NAN);
        else {
          wchar_t* tmp;
          tmp_num = strtod(from, &tmp);
          from = tmp;
          from--;
          head = s21_enqueue(head, '\0', tmp_num);
        }
        is_unary = false;
        break;
      }
      case FUNCTION_OR_BRA_CASE: {
        stack = s21_push(stack, *from, NAN);
        is_unary = true;
        break;
      }
      case SEPARATOR_CASE: {
        wchar_t tmp = 0;
        do {
          tmp = s21_pop(&stack, &tmp_num);
          if (tmp) head = s21_enqueue(head, tmp, tmp_num);
        } while (tmp != KET_CH && tmp);
        if (tmp != KET_CH) e_code = ERROR;
        is_unary = false;
        break;
      }
      case OPERATOR_CASE: {
        int pr_this = s21_get_priority(*from);
        wchar_t ch = *from;
        if (ch == MINUS_OPERATOR && is_unary) {
          ch = UNARI_MINUS_OPERATOR;
          is_unary = false;
        } else if (ch == PLUS_OPERATOR && is_unary) {
          ch = UNARI_PLUS_OPERATOR;
          is_unary = false;
        } else
          is_unary = true;
        while (stack && pr_this <= s21_get_priority(stack->ch))
          head = s21_enqueue(head, s21_pop(&stack, &tmp_num), tmp_num);
        stack = s21_push(stack, ch, NAN);
        break;
      }
      case KET_CASE: {
        while (stack && stack->ch != BRA_CH)
          head = s21_enqueue(head, s21_pop(&stack, &tmp_num), tmp_num);
        if (!stack)
          e_code = ERROR;
        else {
          s21_pop(&stack, &tmp_num);
          if (stack && s21_is_func(stack->ch))
            head = s21_enqueue(head, s21_pop(&stack, &tmp_num), tmp_num);
        }
        is_unary = false;
        break;
      }
      default:
        break;
    }
    from++;
  }
  if (!(*from)) {
    if (stack && (stack->ch == BRA_CH || stack->ch == KET_CH))
      e_code = ERROR;
    else {
      wchar_t ch = 0;
      while (s21_what_is_token(ch = s21_pop(&stack, NULL)) == OPERATOR_CASE ||
             s21_is_func(ch))
        head = s21_enqueue(head, ch, NAN);
    }
  }
  s21_remove_list(&stack);
  return e_code;
}

int s21_is_func_str(const wchar_t** from) {
  wchar_t ret_ch = 0;
  for (int i = 0; i < 10 && !ret_ch; ++i)
    if (!strncmp(*from, map_with_strings[i], strlen(map_with_strings[i]))) {
      ret_ch = map_with_chars[i];
      *from += strlen(map_with_strings[i]);
    }
  return ret_ch;
}

void s21_parser_from_infix_to_postfix(wchar_t* to, const wchar_t* from) {
  while (*from) {
    if (*from == VARIABLE_CH || *from == LOWER_EXP_CH || *from == UPPER_EXP_CH)
      *to++ = *from++;
    else if (isalpha(*from)) {
      int ch = s21_is_func_str(&from);
      switch (ch) {
        case MOD_FUNC_CH:
        case COS_FUNC_CH:
        case SIN_FUNC_CH:
        case TAN_FUNC_CH:
        case ACOS_FUNC_CH:
        case ASIN_FUNC_CH:
        case ATAN_FUNC_CH:
        case SQRT_FUNC_CH:
        case LN_FUNC_CH:
        case LOG_FUNC_CH: {
          *to++ = ch;
          break;
        }
        default: {
          from++;
          break;
        }
      }
    } else
      *to++ = *from++;
  }
}

int s21_is_expression_correct(const wchar_t* from) {
  wchar_t proccessed_expression[BUFF_SIZE];
  memset(proccessed_expression, '\0', BUFF_SIZE);
  s21_parser_from_infix_to_postfix(proccessed_expression, from);
  queue_t* queue = s21_enqueue(NULL, '0', 0.);
  int e_code = s21_parser_postfix_notation(queue, from);
  s21_remove_list_q(&queue);
  return e_code;
}
