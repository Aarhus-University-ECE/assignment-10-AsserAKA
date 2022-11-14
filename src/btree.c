#include "btree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_node *Insert(int x, struct tree_node *t) {
  // Insert item x into the tree t

  if (t == NULL) /* Base case: the current root is NULL */
  {
   /* Create a new tree with the item x */
    t = createTree(x);
    
    return t;
  }
  else if (x > t->item) /* Recursive step: x is larger than the current root's item */
  {
    /* Use recursion on the right child of the current root */
    t->right = Insert(x, t->right);
    return t;
  }
  else /* Recursive step: x is smaller or equal to the current root's item */
  {
    /* Use recursion on the current root's left child. If x is equal to the root's item, it will be moved another a left child down,
    and then be inserted in that's right child */
    t->left = Insert(x, t->left);
    return t;
  }
}

struct tree_node *Remove(int x, struct tree_node *t) {
  // Remove one item from the tree t
  
  /* Checks if the item x is in the tree. Otherwise the tree t just gets returned */
  if(Contains(x, t))
  {

    if (t->item == x) /* Base case: the item is the root */
    {
      if(t->left != NULL && t->right != NULL) /* This statement runs, if both of the roots children aren't NULL */
      {
        struct tree_node *temp = t->right;    /* Temp tree_node assigned as the root's right child */
  
        while (temp->left != NULL) /* Loop searching for the smallest left child (i.e. leaf), closest in matching x in value */
        {
          temp = temp->left;
        }
       
        t->item = temp->item; /* Assiging the found node's item to the root, thereby removing x */
        Remove(t->item, t->right);  /* Use Remove to replace temp */

        return t;
      }
      else if (t->left == NULL) /* This statement runs, if the left or both children are NULL, since it's first in line */
      {
        struct tree_node *temp = t->right; /* New temporary tree_node assigned as the root's right child */
        free(t);      /* Freeing the root */
        return temp;  /* Returning the removed node's child */
      }
      else if (t->right == NULL) /* This statement runs, if the right child is NULL */
      {
        struct tree_node *temp = t->left; /* New temporary tree_node assigned as the root's left child */
        free(t);      /* Freeing the root */
        return temp;  /* Returning the removed node's child */
      }
    } 
    else if (x < t->item) /* Recursive step: x is smaller than the current root's item */
    {
      t->left = Remove(x, t->left); /* Use recursion on the root's left child*/
      return t;
    }
    else if (x > t->item) /* Recursive step: x is larger than the current root's item */
    {
      t->right = Remove(x, t->right); /* Use recursion on the root's right child*/
      return t;
    }
  }
  else
  {
    return t;
  }
}
 
int Contains(int x, struct tree_node *t) {
  // Return true if the tree t contains item x. Return false otherwise.

  if (t == NULL) /* Base case: If the item of the current root is NULL, return false */
  {
    return 0;
  } 
  else if ( t->item == x) /* Base case: If the item is equal to x, return true */
  {
    return 1;
  } 
  else if (x > t->item) /* Recursive step: If x is larger than the current roots item, use recursion on the right child */
  {
    Contains(x, t->right); 
  }
  else /* Recursive step: If x is larger than the current roots item, use recursion on the right child */
  {
    Contains(x, t->left);
  }
}

struct tree_node *Initialize(struct tree_node *t) {

  t = NULL; /* Initializing the root of the tree to NULL */

  return t;
}

int Empty(struct tree_node *t) {
  // Test if empty

  if (t == NULL) /* If the root is NULL, i.e. the tree is empty, return true*/
  {
    return 1;
  }
  else /* Else return false */
  return 0;
}

int Full(struct tree_node *t) {
  /* The tree can never be full, since it is a dynamic list */
  return 0;
}

/* Function creating a tree */
struct tree_node *createTree(int value)
{
  struct tree_node *root = malloc(sizeof(struct tree_node)); /* Allocating memory to tree node */
  root->item = value; /* Assigning the input value to the root's item */
  root->left = NULL;  /* Initializing the left child to NULL */
  root->right = NULL; /* Initializing the right child to NULL */
  return root;
}