#include <catch2/catch_test_macros.hpp>

extern "C" {
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "insertion_sort.h"
#include "queue.h"
}

TEST_CASE("initialize", "[queue]") {
  queue q;
  initialize(&q);
  REQUIRE(q.front == nullptr);
  REQUIRE(q.rear == nullptr);
  REQUIRE(q.size == 0);
}

TEST_CASE("empty", "[queue]") {
  queue q;
  q.front = NULL;
  q.rear = NULL;
  q.size = 0;
  REQUIRE(empty(&q));
  node n;
  n.data = 1;
  n.next = NULL;
  q.front = &n;
  q.rear = &n;
  q.size = 1;
  REQUIRE(!empty(&q));
}

TEST_CASE("full", "[queue]") {
  queue q;
  q.front = NULL;
  REQUIRE(!full(&q));
  node n;
  n.data = 1;
  n.next = NULL;
  q.front = &n;
  q.rear = &n;
  q.size = 1;
  REQUIRE(!full(&q));
}

TEST_CASE("enqueue", "[queue]") {
  queue q;
  q.front = NULL;
  q.rear = NULL;
  q.size = 0;
  const int x0 = 1;
  const int x1 = 2;
  enqueue(&q, x0);
  REQUIRE(q.front != nullptr);
  REQUIRE(q.rear != nullptr);
  REQUIRE(q.front->data == x0);
  REQUIRE(q.size == 1);

  enqueue(&q, x1);
  REQUIRE(q.front != nullptr);
  REQUIRE(q.rear != nullptr);
  REQUIRE(q.front->data == x0);
  REQUIRE(q.rear->data == x1);
  REQUIRE(q.size == 2);
}

TEST_CASE("dequeue", "[queue]") {
  queue q;
  q.front = NULL;
  q.rear = NULL;
  q.size = 0;
  const int x0 = 1;
  const int x1 = 2;

  node *n0 = (node *)malloc(sizeof(node));
  if (!n0) {
    fprintf(stderr, "%s:%d Allocation with malloc() failed.\n", __FILE__,
            __LINE__);
    exit(1);
  }
  n0->data = x0;
  n0->next = NULL;
  node *n1 = (node *)malloc(sizeof(node));
  if (!n1) {
    fprintf(stderr, "%s:%d Allocation with malloc() failed.\n", __FILE__,
            __LINE__);
    exit(1);
  }
  n1->data = x1;
  n1->next = NULL;
  // enqueue(&q, x0);
  q.front = n0;
  q.rear = n0;
  q.size = 1;

  // enqueue(&q, x1);
  q.rear = n1;
  q.front->next = n1;
  q.size = 2;

  const int y0 = dequeue(&q);
  REQUIRE(y0 == x0);
  REQUIRE(q.front != nullptr);
  REQUIRE(q.rear != nullptr);
  REQUIRE(q.front->data == x1);
  REQUIRE(q.rear->data == x1);
  REQUIRE(q.size == 1);

  const int y1 = dequeue(&q);
  REQUIRE(y1 == x1);
  REQUIRE(q.front == nullptr);
  REQUIRE(q.rear == nullptr);
  REQUIRE(q.size == 0);
}

TEST_CASE("queue", "[queue]") {
  queue q;
  initialize(&q);
  REQUIRE(empty(&q));
  const int x0 = 2;
  const int x1 = 3;
  enqueue(&q, x0);
  REQUIRE(!empty(&q));
  enqueue(&q, x1);
  REQUIRE(!empty(&q));
  const int y0 = dequeue(&q);
  REQUIRE(!empty(&q));
  const int y1 = dequeue(&q);
  REQUIRE(empty(&q));
  REQUIRE(!full(&q));

  REQUIRE(x0 == y0);
  REQUIRE(x1 == y1);

  int xs[] = {1, 2, 3, 4, 5};
  const int len = sizeof(xs) / sizeof(int);
  for (int i = 0; i < len; i++) {
    enqueue(&q, xs[i]);
  }

  int ys[len];
  for (int i = 0; i < len; i++) {
    ys[i] = dequeue(&q);
  }

  REQUIRE(empty(&q));
  REQUIRE(xs[0] == ys[0]);
  REQUIRE(xs[1] == ys[1]);
  REQUIRE(xs[2] == ys[2]);
  REQUIRE(xs[3] == ys[3]);
  REQUIRE(xs[4] == ys[4]);
}

node *ll_create_node(int x) {
  node *n = (node *)malloc(sizeof(node));
  if (!n) {
    fprintf(stderr, "%s:%d Allocation with malloc() failed.\n", __FILE__,
            __LINE__);
    exit(1);
  }

  n->data = x;
  n->next = NULL;

  return n;
}

node *ll_from_array(const int *xs, const int len) {
  if (len == 0) {
    return NULL;
  }

  node *list = ll_create_node(xs[0]);
  node *current = list;

  for (int i = 1; i < len; i++) {
    node *new_node = ll_create_node(xs[i]);
    current->next = new_node;
    current = current->next;
  }

  return list;
}

int ll_size(node *head) {
  assert(head != NULL);

  int size = 0;
  while (head != NULL) {
    head = head->next;
    size++;
  }

  return size;
}

/**
 * Converts a linked list to an array.
 *
 * @param head pointer to the head node of the linked list
 *
 * @return pointer to the dynamically allocated array containing copies the data
 * from the linked list
 */
int *ll_to_array(node *head) {
  assert(head != NULL);
  const int len = ll_size(head);
  int *arr = (int *)malloc(sizeof(int) * len);
  if (!arr) {
    fprintf(stderr, "%s:%d Allocation with malloc() failed.\n", __FILE__,
            __LINE__);
    exit(1);
  }

  int idx = 0;
  node *p = head;
  while (p != NULL) {
    arr[idx] = p->data;
    idx++;
    p = p->next;
  }

  return arr;
}

/**
 * Compares two arrays of integers to check if they are equal.
 *
 * @param arr1 pointer to the first array
 * @param arr2 pointer to the second array
 * @param len length of the arrays
 *
 * @return true if the arrays are equal, false otherwise
 */
bool arrays_equal(const int *arr1, const int *arr2, const int len) {
  assert(arr1 != NULL);
  assert(arr2 != NULL);
  assert(len > 0);

  for (int i = 0; i < len; i++) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }
  return true;
}

void int_array_print(const int *arr, const int len) {
  fprintf(stderr, "[ ");
  for (int i = 0; i < len; i++) {
    fprintf(stderr, "%d", arr[i]);
    if (i < len - 1) {
      fprintf(stderr, ", ");
    }
  }
  fprintf(stderr, "]\n");
}

static const char *RESET = "\033[0m";
static const char *RED = "\033[31m";
static const char *GREEN = "\033[32m";

#define INSERTION_SORT_TEST_CASE(input, expected)                              \
  const int len = sizeof(input) / sizeof(int);                                 \
  node *list = ll_from_array(input, len);                                      \
  node *sorted = isort(list);                                                  \
  int *arr = ll_to_array(sorted);                                              \
  bool equal = arrays_equal(arr, expected, len);                               \
  if (!equal) {                                                                \
    fprintf(stderr, "%sExpected:%s\n", GREEN, RESET);                          \
    int_array_print(expected, len);                                            \
    fprintf(stderr, "%sGot:%s\n", RED, RESET);                                 \
    int_array_print(arr, len);                                                 \
  }                                                                            \
  REQUIRE(arrays_equal(arr, expected, len));

TEST_CASE("positive-numbers", "[insertion_sort]") {
  const int input[] = {5, 22, 11, 33, 3, 2, 1};
//   const int len = sizeof(input) / sizeof(int);
  const int input_sorted[] = {1, 2, 3, 5, 11, 22, 33};

  INSERTION_SORT_TEST_CASE(input, input_sorted);

//   node *list = ll_from_array(input, len);
//   node *sorted = isort(list);
//   int *arr = ll_to_array(sorted);
//   bool equal = arrays_equal(arr, input_sorted, len);
//   if (!equal) {
//     fprintf(stderr, "%sExpected:%s\n", GREEN, RESET);
//     int_array_print(input_sorted, len);
//     fprintf(stderr, "%sGot:%s\n", RED, RESET);
//     int_array_print(arr, len);
//   }
//   REQUIRE(arrays_equal(arr, input_sorted, len));
}

TEST_CASE("negative-numbers", "[insertion_sort]") {
  const int input[] = {-5, -22, -11, -33, -3, -2, -1};
  // const int len = sizeof(input) / sizeof(int);
  const int input_sorted[] = {-33, -22, -11, -5, -3, -2, -1};

  INSERTION_SORT_TEST_CASE(input, input_sorted);

  // node* list = ll_from_array(input, len);
  // node* sorted = isort(list);
  // int* arr = ll_to_array(sorted);
  // REQUIRE(arrays_equal(arr, input_sorted, len));
}

TEST_CASE("2-numbers", "[insertion_sort]") {
  const int input[] = {1, 10};
//   const int len = sizeof(input) / sizeof(int);
  const int input_sorted[] = {1, 10};

  INSERTION_SORT_TEST_CASE(input, input_sorted);

//   node *list = ll_from_array(input, len);
//   node *sorted = isort(list);
//   int *arr = ll_to_array(sorted);
//   REQUIRE(arrays_equal(arr, input_sorted, len));
}

TEST_CASE("numbers", "[insertion_sort]") {
  const int input[] = {3,  5,  11, 2,  16, 18, 6,  4,  -14, 9,
                       -7, 20, 10, 19, 8,  1,  17, 13, 15,  -12};
//   const int len = sizeof(input) / sizeof(int);
  const int input_sorted[] = {-14, -12, -7, 1,  2,  3,  4,  5,  6,  8,
                              9,   10,  11, 13, 15, 16, 17, 18, 19, 20};

  INSERTION_SORT_TEST_CASE(input, input_sorted);

//   node *list = ll_from_array(input, len);
//   node *sorted = isort(list);
//   int *arr = ll_to_array(sorted);
//   REQUIRE(arrays_equal(arr, input_sorted, len));
}
