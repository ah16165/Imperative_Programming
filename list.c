#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct list
{
    struct node *position;
    struct node *first;
    struct node *last;
};

struct node
{
  item subject;
  struct node *next;
  struct node *back;
};
typedef struct node node;

// Create a new empty list.
list *newList()
{
  struct list *new;
  struct node *s;
  struct node *e;

  new = malloc(sizeof(list));
  s = malloc(sizeof(node));
  e = malloc(sizeof(node));

  (new->first) = s;
  (new->position) = s;
  (new->last) = e;

  (e->back) = s;
  (s->next) = e;

  return new;
}


// Set the current position before the first item or after the last item, e.g.
// to begin a forward or backward traversal.
void start(list *l)
{
  (l->position) = (l->first);
}

void end(list *l)
{
  (l->position) = (l->last->back);
}


// Check whether the current position is at the start or end, e.g. to test
// whether a traversal has finished.
bool atStart(list *l)
{
  if ((l->position) == (l->first)) return true;
  else return false;
}

bool atEnd(list *l)
{
  if ((l->position) == (l->last->back)) return true;
  else return false;
}

//Error funtion that stops the program.
void fail(char *message)
{
  fprintf(stderr, "%s\n", message);
  exit(1);
}

// Move the current position one place forwards or backwards.
void forward(list *l)
{
  if(atEnd(l)) fail("Cannot call forward when at the end of a list.");
  else l->position = l->position->next;
}

void backward(list *l)
{
  if(atStart(l)) fail("Cannot call backward when at the start of a list.");
  else l->position = l->position->back;
}

// Insert an item before or after the current position (i.e. at the current
// position, but with the current position ending up after or before the new
// item).
void insertBefore(list *l, item x)
{
  node *newB = malloc(sizeof(node));
  newB->subject = x;
  newB->back = l->position;
  newB->next = l->position->next;

  newB->next->back = newB;
  newB->back->next = newB;

  forward(l);
}

void insertAfter(list *l, item x)
{
  insertBefore(l,x);
  backward(l);
}

// Get the item before or after the current position. It is an error to call
// getBefore when at the start, or getAfter when at the end.
item getBefore(list *l)
{
  item x;

  if (!atStart(l)){ x = l->position->subject; return x;}
  else fail("You cannot call getBefore at the start of the list.");
  exit(1);
}

item getAfter(list *l)
{
  item x;

  if(!atEnd(l)){x = l->position->next->subject; return x;}
  else fail("You cannot call getAfter at the end of the list.");
  exit(1);
}

// Set the item before or after the current position. It is an error to call
// setBefore when at the start, or setAfter when at the end.
void setBefore(list *l, item x)
{
  if (!atStart(l)) (l->position->subject) = x;
  else fail("You cannot call setBefore at the start of the list.");
}

void setAfter(list *l, item x)
{
  if (!atEnd(l)) (l->position->next->subject) = x;
  else fail("You cannot call setAfter at the end of the list.");
}

// Delete the item before or after the current position. It is an error to call
// deleteBefore when at the start, or deleteAfter when at the end.
void deleteBefore(list *l)
{
  if (atStart(l)) fail("Cannot call deleteBefore at start of list");
  else
  {
    node *floating = l->position;
    l->position->next->back = l->position->back;
    l->position->back->next = l->position->next;
    l->position = l->position->back;
    free(floating);
  }
}

void deleteAfter(list *l)
{
  if (atEnd(l)) fail("Cannot call deleteAfter at end of list");
  else
  {
    node *floating = l->position->next;
    l->position->next->next->back = l->position;
    l->position->next = l->position->next->next;
    free(floating);

  }
}







void tests()
{
  //Sets up a new list with 3 nodes and the standard 2 sentinels - (S-1-2-3-S).
  list *test = newList();
  insertAfter(test,3);
  insertAfter(test,2);
  insertAfter(test,1);

  //Tests atStart and atEnd, as well as testing that Start and End match up with
  //them. Start and End are implicitly tested in all of the functions, as if
  //all of the function with them in operate correclty then it can be assumed
  //they operate correctly.
  start(test);
  assert(atStart(test));

  end(test);
  assert(atEnd(test));

  //Tests getAfter and getBefore work in combination with start and end.
  start(test);
  assert(getAfter(test) == 1 );

  end(test);
  assert(getBefore(test) == 3);

  //Tests that forward and backward work, and cotinues to check start, end ,
  //getBefore and getAfter.
  start(test);
  forward(test);
  assert(getBefore(test) == 1);
  assert(getAfter(test) == 2);

  end(test);
  backward(test);
  assert(getBefore(test) == 2);
  assert(getAfter(test) == 3);

  //Tests that insertBefore and insertAfter work, and continues to test all previous
  //functions.
  end(test);
  insertBefore(test,4);
  assert(getBefore(test) == 4);
  insertAfter(test,5);
  assert(getAfter(test) == 5);

  start(test);
  setAfter(test,9);
  assert(getAfter(test) == 9);
  forward(test);
  setBefore(test,1);
  assert(getBefore(test) == 1);
  start(test);
  assert(getAfter(test) == 1);

  //Tests that deleteBefore and deleteAfter work, and continues to test all previous
  //functions.
  deleteAfter(test);
  assert(atStart(test));
  assert(getAfter(test) == 2);
  forward(test);
  assert(getBefore(test) == 2);
  assert(getAfter(test) == 3);

  end(test);
  deleteBefore(test);
  assert(atEnd(test));
  assert(getBefore(test) == 4);
  backward(test);
  assert(getBefore(test) == 3);
  assert(getAfter(test) == 4);

   //Deletes rest of nodes and frees space of the list.
  deleteBefore(test);
  deleteBefore(test);
  deleteAfter(test);

  free((test->first));
  free((test->last));

  free(test);
}


int listMain()
{
  tests();
  printf("All tests pass!\n");
  return 0;
}
