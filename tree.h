/* This is a library module supporting trees. My trees are ordered so that if a value
within a constiuent node is less than the value in the node it is being added to then it
goes to the left and vice versa to the right.

The items stored in a tree are of type 'item'.  The typedef for this can be
changed for any particular application so that 'item' stands for any desired
type. For the sake of simpilicty , keep the type to a numerical type.*/

#include <stdbool.h>

typedef int item;

// Both these structures are defined in tree.c.
struct tree;
typedef struct tree tree;

struct node;
typedef struct node node;

// Function that ceates a new one node tree.
node *newNode(item n);

// Function to insert nodes, with an ordering structure of left if less than
// and right if greater than. Returns a new, updated tree.
node *insertNode(node *p, item n);

// Function to create a new tree:
tree *newTree();

// Function to insert nodes into trees:
void insert(tree *t, item n);

// A recursive tree search function:
node *findNode(node *p, item n);

// A function to check if a value is within a tree:
bool checkFor(tree *t, item n);
