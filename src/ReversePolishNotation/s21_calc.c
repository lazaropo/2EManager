#include "s21_calc.h"

node_t *s21_sum(node_t **head) {
  if (!(*head)->prev) return *head;
  double num1 = 0;
  s21_pop(head, &num1);
  (*head)->num += num1;
  return *head;
}

node_t *s21_sub(node_t **head) {
  if (!(*head)->prev) return *head;
  double num1 = 0;
  s21_pop(head, &num1);
  (*head)->num -= num1;
  return *head;
}

node_t *s21_mul(node_t **head) {
  if (!(*head)->prev) return *head;
  double num1 = 0;
  s21_pop(head, &num1);
  (*head)->num *= num1;
  return *head;
}

node_t *s21_div(node_t **head) {
  if (!(*head)->prev) return *head;
  double num1 = 0;
  s21_pop(head, &num1);
  (*head)->num /= num1;
  return *head;
}

node_t *s21_dice_mult(node_t **head) {
  if (!(*head)->prev) return *head;
  // node_t *tmp = *head;

  // while (tmp) {
  //   printf("+++++++ %c %f ", tmp->ch, tmp->num);
  //   tmp = tmp->prev;
  // }

  double num1 = 0;
  s21_pop(head, &num1);
  int len = (*head)->num;
  (*head)->num = 0;
  srand(time(NULL));
  for (int i = 0; i < len; ++i) {
    (*head)->num += (rand() % (int)num1 + 1);
  }
  return *head;
}

node_t *s21_func_calc(node_t **head, double(math_func(double))) {
  (*head)->num = math_func((*head)->num);
  return *head;
}

node_t *s21_func_calc_two_operands(node_t **head,
                                   double(math_func(double a, double b))) {
  if (!(*head)->prev) return *head;
  double num1 = 0;
  s21_pop(head, &num1);
  (*head)->num = math_func((*head)->num, num1);
  return *head;
}

void s21_calculate_by_rule(node_t **head, wchar_t ch) {
  int operator_code = s21_is_func(ch);
  operator_code = operator_code ? operator_code : s21_is_operator(ch);
  switch (operator_code) {
    case PLUS_OPERATOR: {
      *head = s21_sum(head);
      break;
    }
    case MINUS_OPERATOR: {
      *head = s21_sub(head);
      break;
    }
    case STAR_OPERATOR: {
      *head = s21_mul(head);
      break;
    }
    case SLASH_OPERATOR: {
      *head = s21_div(head);
      break;
    }
    case UNARI_PLUS_OPERATOR: {
      break;
    }
    case UNARI_MINUS_OPERATOR: {
      (*head)->num *= -1;
      break;
    }
    case POW_OPERATOR: {
      *head = s21_func_calc_two_operands(head, pow);
      break;
    }
    case MOD_FUNC_CH: {
      *head = s21_func_calc_two_operands(head, fmod);
      break;
    }
    case DICE_MULTIPLYING_d:
    case DICE_MULTIPLYING_D:
    case DICE_MULTIPLYING_b:
    case DICE_MULTIPLYING_B: {
      *head = s21_dice_mult(head);
      break;
    }
    case COS_FUNC_CH: {
      s21_func_calc(head, cos);
      break;
    }
    case SIN_FUNC_CH: {
      s21_func_calc(head, sin);
      break;
    }
    case TAN_FUNC_CH: {
      s21_func_calc(head, tan);
      break;
    }
    case ACOS_FUNC_CH: {
      s21_func_calc(head, acos);
      break;
    }
    case ASIN_FUNC_CH: {
      s21_func_calc(head, asin);
      break;
    }
    case ATAN_FUNC_CH: {
      s21_func_calc(head, atan);
      break;
    }
    case SQRT_FUNC_CH: {
      s21_func_calc(head, sqrt);
      break;
    }
    case LN_FUNC_CH: {
      s21_func_calc(head, log);
      break;
    }
    case LOG_FUNC_CH: {
      s21_func_calc(head, log10);
      break;
    }
    default: {
      break;
    }
  }
}

int s21_calculate(queue_t *head, double *result, double x_value) {
  if (!head) return ERROR;
  node_t *stack = NULL;
  queue_t *ptr = head;

  ptr = head;
  do {
    if (!ptr->ch)
      stack = s21_push(stack, ptr->ch, ptr->num);
    else if (ptr->ch == VARIABLE_CH)
      stack = s21_push(stack, '\0', x_value);
    else
      s21_calculate_by_rule(&stack, ptr->ch);
    ptr = ptr->next;
  } while (ptr);

  if (stack)
    *result = stack->num;
  else
    *result = 0.;
  s21_remove_list(&stack);
  return OK;
}
