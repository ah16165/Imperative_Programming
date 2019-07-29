#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "tree.h"

// Defines a node and a tree.
struct node {
  struct node *left;
  item key;
  struct node *right;
};

struct tree{
  struct node *root;
};

// Function that ceates a new one node tree.
node *newNode(item n)
{
  node *p = malloc(sizeof(node));
  *p = (node) {NULL, n, NULL};
  return p;
}

// Function to insert nodes, with an ordering structure of left if less than
// and right if greater than. Returns a new, updated tree.
node *insertNode(node *p, item n)
{
  if (p == NULL) p = newNode(n);
  else if (n < p->key) p->left = insertNode(p->left, n);
  else if (n > p->key) p->right = insertNode(p->right, n);
  return p;
}

// Function to create a new tree:
tree *newTree()
{
  tree *t = malloc(sizeof(tree));
  t->root = NULL;
  return t;
}

// Function to insert nodes into trees:
void insert(tree *t, item n)
{
  t->root = insertNode(t->root, n);
}

// A recursive tree search function:
node *findNode(node *p, item n)
{
  if (p == NULL){}
  else if (n < p->key) p = findNode(p->left, n);
  else if (n > p->key) p = findNode(p->right, n);
  return p;
}

// A function to check if a value is within a tree:
bool checkFor(tree *t, item n)
{
  return findNode(t->root,n) != NULL;
}


// TESTING

void tests()
{
  tree *test = newTree();
  insert(test, 1);
  insert(test, 5);
  insert(test, 2);
  insert(test, 3);

  assert(checkFor(test,1));
  assert(checkFor(test,5));
  assert(checkFor(test,2));
  assert(checkFor(test,3));
}

int treeMain()
{
  tests();
  printf("All tests pass!\n");
  return 0;
}
