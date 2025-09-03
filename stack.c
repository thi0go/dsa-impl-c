/**
 * @file stack.c
 * @author Joaquin Thiogo (joanthio09@gmail.com)
 * @brief Implementation of stack-based bracket balance checker in C
 * @date 2025-09-03
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *c;
  int top;
  int capacity;
} Stack;

Stack create_stack(int max_capacity) {
  Stack s;
  s.c = (char *)malloc(sizeof(char) * max_capacity);
  s.top = -1; // -1 is empty
  s.capacity = max_capacity;
  printf("info: stack is created\n");
  return s;
}

bool is_empty(Stack s) { return s.top == -1; }

bool is_full(Stack s) { return s.top == s.capacity - 1; }

void push(Stack *s, char c) {
  if (is_full(*s)) {
    fprintf(stderr, "err: stack is full, max capacity is %d\n", s->capacity);
    exit(EXIT_FAILURE);
  }
  s->c[++s->top] = c;
  printf("info: pushed %c onto the stack\n", c);
}

char peek(Stack s) {
  if (is_empty(s)) {
    fprintf(stderr, "err: stack is empty\n");
    exit(EXIT_FAILURE);
  }

  return s.c[s.top];
}

char pop(Stack *s) {
  if (is_empty(*s)) {
    fprintf(stderr, "err: stack is empty\n");
    exit(EXIT_FAILURE);
  }

  char temp = s->c[s->top];
  s->top--;
  printf("info: popped %c from the stack\n", temp);
  return temp;
}

bool is_bracket_balance(const char *str) {
  if (strlen(str) % 2 != 0) {
    return 0;
  }
  Stack s = create_stack(strlen(str));
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '[' || str[i] == '(' || str[i] == '{') {
      push(&s, str[i]);
    } else if (str[i] == ']' || str[i] == ')' || str[i] == '}') {
      if (str[i] == '}' && peek(s) == '{') {
        pop(&s);
      } else if (str[i] == ')' && peek(s) == '(') {
        pop(&s);
      } else if (str[i] == ']' && peek(s) == '[') {
        pop(&s);
      } else {
        return 0;
      }
    } else {
      fprintf(stderr, "err: str input must be bracket '() || {} || []'\n");
      exit(EXIT_FAILURE);
    }
  }
  return 1;
}

int main() {
  const char *tests[] = {"()",    "[]",    "{}",     "({[]})",  "({(())})",
                         "",      "(",     ")",      "(()",     "([)]",
                         "(({})", "({})]", "()[]{}", "Halo ges"};

  for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
    if (is_bracket_balance(tests[i]))
      printf("%s is balance\n", tests[i]);
    else
      printf("%s isn't balance\n", tests[i]);
  }

  return 0;
}
