#include "s21_calc.h"

int s21_main_calc_function(const wchar_t *expression, double *result,
                           double x_value) {
  wchar_t proccessed_expression[BUFF_SIZE];
  memset(proccessed_expression, '\0', BUFF_SIZE * sizeof(wchar_t));

  s21_parser_from_infix_to_postfix(proccessed_expression, expression);
  // printf("%ls\n", expression);
  // printf("%ls\n", proccessed_expression);

  queue_t *queue = s21_enqueue(NULL, '0', NAN);
  int e_code = s21_parser_postfix_notation(queue, proccessed_expression);

  // queue_t* tmp = queue;

  // while (tmp) {
  //   printf("+++++++ %c %f ", tmp->ch, tmp->num);
  //   tmp = tmp->next;
  // }

  if (!result)
    result = (double *)calloc(1, sizeof(double));
  else
    *result = 0;
  if (!e_code) e_code = s21_calculate(queue, result, x_value);

  s21_remove_list_q(&queue);
  return e_code;
}
