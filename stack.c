/**
 * @file bracket_balance.c
 * @author Joaquin Thiogo (joanthio09@gmail.com)
 * @brief Implementation of stack-based bracket balance checker in C
 * @date 2025-09-03
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct Stack
 * @brief A simple stack implementation for characters
 */
typedef struct {
  char *c;      /**< Dynamic array to hold stack elements */
  int top;      /**< Index of the top element (-1 if empty) */
  int capacity; /**< Maximum number of elements the stack can hold */
} Stack;

/**
 * @brief Creates a new stack with a given capacity
 *
 * @param max_capacity The maximum number of elements the stack can hold
 * @return A Stack instance
 */
Stack create_stack(int max_capacity) {
  Stack s;
  s.c = (char *)malloc(sizeof(char) * max_capacity);
  s.top = -1; // -1 is empty
  s.capacity = max_capacity;
  return s;
}

/**
 * @brief Checks if the stack is empty
 *
 * @param s The stack to check
 * @return true if empty, false otherwise
 */
bool is_empty(Stack s) { return s.top == -1; }

/**
 * @brief Checks if the stack is full
 *
 * @param s The stack to check
 * @return true if full, false otherwise
 */
bool is_full(Stack s) { return s.top == s.capacity - 1; }

/**
 * @brief Pushes an element onto the stack
 *
 * @param s Pointer to the stack
 * @param c Character to push
 */
void push(Stack *s, char c) {
  if (is_full(*s)) {
    fprintf(stderr, "err: stack is full, max capacity is %d\n", s->capacity);
    exit(EXIT_FAILURE);
  }
  s->c[++s->top] = c;
  printf("info: pushed %c onto the stack\n", c);
}

/**
 * @brief Returns the top element of the stack without removing it
 *
 * @param s The stack
 * @return The top character of the stack
 */
char peek(Stack s) {
  if (is_empty(s)) {
    fprintf(stderr, "err: stack is empty\n");
    exit(EXIT_FAILURE);
  }

  return s.c[s.top];
}

/**
 * @brief Pops the top element from the stack
 *
 * @param s Pointer to the stack
 * @return The character popped
 */
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

/**
 * @brief Checks if a string of brackets is balanced
 *
 * This function uses a stack to ensure that every opening bracket
 * has a corresponding closing bracket in the correct order.
 *
 * @param str The input string containing brackets
 * @return true if the string is balanced, false otherwise
 */
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
    }
  }
  return 1;
}

/**
 * @brief Runs simple unit tests for the bracket balance checker
 *
 * @return int Exit status
 */
int main() {
  const char *tests[] = {"()",    "[]",    "{}",    "({[]})", "({(())})",
                         "",      "(",     ")",     "(()",    "([)]",
                         "(({})", "({})]", "()[]{}"};

  for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
    if (is_bracket_balance(tests[i]))
      printf("%s is balance\n", tests[i]);
    else
      printf("%s isn't balance\n", tests[i]);
  }

  return 0;
}
