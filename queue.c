/**
 * @file queue.c
 * @author Joaquin Thiogo (joanthio09@gmail.com)
 * @brief Implementation of Queue-based Print Job Simulation in C
 * @date 2025-09-03
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  char *file_name;
  int pages;
} File;

typedef struct {
  File *file;
  int head;
  int tail;
  int capacity;
} Queue;

bool is_full(Queue q) { return q.tail == q.capacity - 1; }

bool is_empty(Queue q) { return q.head == -1; }

void read_queue(Queue q) {
  if (is_empty(q)) {
    fprintf(stderr, "err: queue is empty\n");
    exit(EXIT_FAILURE);
  }
  printf("info: reading queue\n");
  for (int i = q.head; i <= q.tail; i++) {
    if (i == q.head) {
      printf("Head ");
    }
    printf("<- %s ", q.file[i].file_name);

    if (i == q.tail) {
      printf("<- Tail");
    }
  }
  printf("\n");
}

Queue create_queue(int max_capacity) {
  Queue q;
  q.file = (File *)malloc(sizeof(File) * max_capacity);

  for (int i = 0; i < max_capacity; i++) {
    q.file[i].file_name = "-";
    q.file[i].pages = 0;
  }

  q.head = -1;
  q.tail = -1;
  q.capacity = max_capacity;

  printf("info: queue is created\n");
  return q;
}

void enqueue(Queue *q, File f) {
  if (is_full(*q)) {
    fprintf(stderr, "err: queue is full\n");
    exit(EXIT_FAILURE);
  }

  q->file[++q->tail] = f;
  if (q->head == -1) {
    q->head++;
  }

  printf("info: file %s (%d pages) is added to queue\n", f.file_name, f.pages);
}

File dequeue(Queue *q) {
  if (is_empty(*q)) {
    fprintf(stderr, "err: queue is empty\n");
    exit(EXIT_FAILURE);
  }

  File f = q->file[q->head];
  for (int i = q->head; i < q->tail; i++) {
    q->file[i] = q->file[i + 1];
  }
  q->tail--;

  if (q->tail == -1)
    q->head = -1;

  printf("info: file %s is removed from queue\n", f.file_name);
  return f;
}

File peek(Queue q) {
  if (is_empty(q)) {
    fprintf(stderr, "err: queue is empty\n");
    exit(EXIT_FAILURE);
  }

  File f = q.file[q.head];
  return f;
}

int size(Queue q) {
  if (is_empty(q)) {
    fprintf(stderr, "err: queue is empty\n");
    exit(EXIT_FAILURE);
  }

  return q.tail - q.head + 1;
}

Queue add_files(File *f, int n) {
  Queue q = create_queue(n);
  for (int i = 0; i < n; i++) {
    enqueue(&q, f[i]);
  }

  return q;
}

void print_file(Queue *q) {
  if (is_empty(*q)) {
    fprintf(stderr, "err: no file in print queue\n");
    exit(EXIT_FAILURE);
  }

  File f = dequeue(q);
  printf("info: printing %s (%d pages)\n", f.file_name, f.pages);
  sleep(1);
  printf("info: finished printing %s (%d pages)\n", f.file_name, f.pages);
}

void print_all_files(Queue *q) {
  if (is_empty(*q)) {
    fprintf(stderr, "err: no file in print queue\n");
    exit(EXIT_FAILURE);
  }

  while (!is_empty(*q)) {
    print_file(q);
  }

  printf("info: all print files are done\n");
}

int main() {
  srand(time(NULL));

  // TC1: add 3 jobs
  File *f = malloc(sizeof(File) * 3);
  for (int i = 0; i < 3; i++) {
    f[i].file_name = malloc(100);
    sprintf(f[i].file_name, "doc%d", i + 1);
    f[i].pages = rand() % 10 + 1;
  }
  Queue q = add_files(f, 3);

  printf("\n--- TC1: View Queue ---\n");
  read_queue(q);

  printf("\n--- TC2: Print One ---\n");
  print_file(&q);
  read_queue(q);

  printf("\n--- TC3: Print All ---\n");
  print_all_files(&q);
  read_queue(q);

  printf("\n--- TC4: Print on Empty ---\n");
  print_file(&q); // expected: err

  return 0;
}
