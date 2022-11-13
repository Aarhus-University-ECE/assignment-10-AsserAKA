#include <assert.h> /* assert */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

#include "linked_list.h"

/* functions to create lists */
node *make_node(int v, node *q) {
  node *p = malloc(sizeof(node));
  p->value = v;
  p->next = q;
  return p;
}

/* free all nodes in the list p */
void free_list(node *p) {
  node *q;
  while (p != NULL) {
    q = p->next;
    free(p);
    p = q;
  }
}

/* print list to console */
void print_list(node *p) {
  
  printf("%d",p->value); /* Print the current value of the linked list */

  /* Recursion: Uses the print_list function as long as the next element isn't NULL */
  if (p->next != NULL)
  {
    return print_list(p->next);
  } 
}

int sum_squares(node *p) {

  if (p != NULL)
  {
    /* Recursive step: calculating square of current element and adding it with the sum_square of the next element. Stops when the current element is NULL */
    return p->value * p->value + sum_squares(p->next); 
  }
  else
  {
    return 0; /* Base case: If the current element is NULL, return 0 */
  }
}

typedef int (*fn_int_to_int)(int);

node *map(node *p, fn_int_to_int f) { 
  // Add your code for excercise 3
  

  if (p != NULL)
  {
    /* Recursive step: Mapping the node's value to the sqaure of p->value. Its next points to the map of the next node */
    return make_node(f(p->value), map(p->next, f));
  } 
  else
  {
    /* Base case: When the current node is NULL, we return NULL to end the list. */
    return NULL;
  }
   
}

int square(int x) { return x * x; }

// example of another function that can be passed to map
// returns the sign of the number
// -1 if negative, 0 if zero, 1 if positive
int sign(int x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }
