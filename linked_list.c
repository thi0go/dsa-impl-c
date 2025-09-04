/**
 * @file linked_list.c
 * @author Joaquin Thiogo (joanthio09@gmail.com)
 * @brief Implementation of Linked List-based Playlist Management in C
 * @date 2025-09-04
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  const char *title;
  struct Node *next;
} Node;

Node *head = NULL;

bool is_empty() { return head == NULL; }

void add_song(const char *title) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->title = title;
  new_node->next = NULL;

  if (head == NULL) {
    head = new_node;
  } else {
    Node *temp = head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = new_node;
  }

  printf("info: %s is added to playlist\n", new_node->title);
}

void read_playlist() {
  if (is_empty()) {
    fprintf(stderr, "err: playlist is empty\n");
    exit(EXIT_FAILURE);
  }

  Node *temp = head;

  printf("info: reading playlist\n");
  for (int i = 0; temp != NULL; temp = temp->next, i++) {
    printf("%d. %s\n", i + 1, temp->title);
  }
}

void delete_song(const char *title) {
  if (is_empty()) {
    fprintf(stderr, "err: playlist is empty\n");
    exit(EXIT_FAILURE);
  }

  bool is_success = 0;

  Node *temp = head;

  if (strcmp(head->title, title) == 0) {
    Node *del = head;
    head = head->next;
    free(del);
    is_success = 1;
    printf("info: %s is deleted in playlist\n", title);
    return;
  }

  while (temp != NULL) {
    if (temp->next != NULL && strcmp(temp->next->title, title) == 0) {
      Node *del = temp->next;
      temp->next = temp->next->next;
      free(del);
      is_success = 1;
      printf("info: %s is deleted in playlist\n", title);
      break;
    }
    temp = temp->next;
  }

  if (!is_success) {
    fprintf(stderr, "err: %s is not found\n", title);
    exit(EXIT_FAILURE);
  }
}

void delete_playlist() {
  Node *temp = head;
  while (temp != NULL) {
    Node *next = temp->next;
    free(temp);
    temp = next;
  }
  head = NULL;
  printf("info: playlist is deleted\n");
}

int main() {

  add_song("A");
  add_song("B");
  add_song("C");

  read_playlist();

  delete_song("C");

  read_playlist();

  delete_playlist();
  read_playlist();
  return 0;
}