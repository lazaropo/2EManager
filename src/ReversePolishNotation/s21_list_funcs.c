#include "s21_calc.h"

node_t *s21_push(node_t *prev, wchar_t ch, double num) {
  node_t *node = (node_t *)calloc(1, sizeof(node_t));
  node->ch = ch;
  node->num = num;
  node->prev = prev;
  return node;
}

queue_t *s21_enqueue(queue_t *prev, wchar_t ch, double num) {
  queue_t *node = (queue_t *)calloc(1, sizeof(queue_t));
  node->ch = ch;
  node->num = num;
  if (prev) prev->next = node;
  node->next = NULL;
  return node;
}

wchar_t s21_pop(node_t **head, double *ret_num) {
  wchar_t ret_ch = 0;
  if (ret_num) *ret_num = NAN;
  if (*head) {
    ret_ch = (*head)->ch;
    if (ret_num) *ret_num = (*head)->num;
    node_t *node = (*head);
    (*head) = (*head)->prev;
    free(node);
  }
  return ret_ch;
}

void s21_remove_list(node_t **head) {
  node_t *ptr;
  while (*head) {
    ptr = *head;
    *head = (*head)->prev;
    free(ptr);
  }
  *head = NULL;
}

void s21_remove_list_q(queue_t **head) {
  queue_t *ptr;
  while (*head) {
    ptr = (*head)->next;
    free(*head);
    *head = ptr;
  }
  *head = NULL;
}