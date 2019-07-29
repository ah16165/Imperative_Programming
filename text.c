#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct text
{
    int size;
    char *array;
};

// Create a new text structure, containing a copy of the given string.
// Note that this function is impossible to test fully.
text *new(char *s)
{
  struct text *n = {0,NULL};
  n = malloc(strlen(s) + 2);
  n->size = (strlen(s) + 1);
  n->array = malloc(strlen(s)+1);
  strcpy(n->array,s);
  return n;
}

// Free up both the space for the struct and the space for the character array.
// Be careful not to access anything after it has been freed.
// Note that this function is imnpossible to test.
void discard(text *t)
{
  free(t->array);
  free(t);
}

int length(text *t)
{
  int x = strlen(t->array);
  return x;
}

char get(text *t, int i)
{
  char x[strlen(t->array)+1];
  strcpy(x,t->array);
  return x[i];
}

void set(text *t, int i, char c)
{
  char x[strlen(t->array)+1];
  strcpy(x,t->array);
  x[i] = c;
  strcpy(t->array,x);
}

text *copy(text *t)
{
  char x[strlen(t->array)+1];
  strcpy(x,t->array);

  struct text *z = {0,NULL};
  z = malloc(strlen(t->array) + 2);
  z->size = strlen(t->array) + 1;
  z->array = malloc(strlen(t->array)+1);
  strcpy(z->array,t->array);
  return z;
}

int compare(text *t1, text *t2)
{
  char x[strlen(t1->array)+1];
  strcpy(x,t1->array);
  char y[strlen(t2->array)+1];
  strcpy(y,t2->array);

  if (strcmp(x,y) == 0) return 0;
  if (strcmp(x,y) < 1) return -1;
  else return 1;
}

void append(text *t1, text *t2)
{
  int c = (strlen(t1->array)) + (strlen(t2->array) + 1);
  char x[c];
  strcpy(x,t1->array);
  char y[strlen(t2->array) + 1];
  strcpy(y,t2->array);
  strcat(x,y);

  t1 = realloc(t1,(c+2));
  t1->array = realloc(t1->array,(c+1));
  t1->size = (c+2);
  strcpy(t1->array,x);
}

text *slice(text *t, int i, int j)
{
  char x[strlen(t->array) +1];
  strcpy(x,t->array);
  int b = (j-i) + 2;
  char y[b+1];
  int o;
  int u;

  for (o = i,u = 0;o <= (j-1); o++, u++)
  {
    y[u] = x[o];
  }

  struct text *r = {0,NULL};
  r = malloc(strlen(y) + 2);
  r->size = strlen(y)+1;
  r->array = malloc(strlen(y)+1);
  strcpy(r->array,y);
  return r;
}

int find(text *t, text *p)
{
  char x[strlen(t->array)+1];
  strcpy(x,t->array);
  char y[strlen(p->array)+1];
  strcpy(y,p->array);

  int i, n = strlen(x), m = strlen(y);
  bool found = false;
  for (i = 0; i <= n - m && ! found; i++)
  {
    found = true;
    for (int j = 0; j < m && found; j++)
    {
      if (x[i+j] != y[j]) found = false;
    }
  }
  if (! found) i = 0;
  return i - 1;
}

//-----------------------------------------------------------------------------
// Tests and a textMain function (renamed to main when compiled for testing).

// Check whether a text is like a given string, as far as can be checked
// without knowing how much memory has been allocated.
bool like(text *t, char *s) {
    if (t == NULL) return false;
    if (t->size <= strlen(s)) return false;
    if (strcmp(t->array, s) != 0) return false;
    return true;
}

// Check that everything is as expected after calling new.
void testNew() {
    text *t = new("");
    assert(like(t, ""));
    text *t2 = new("cat");
    assert(like(t2, "cat"));
    discard(t);
    discard(t2);
}

void testLength() {
    text *t = new("cat");
    assert(length(t) == 3);
    discard(t);
}

void testGet() {
    text *t = new("cat");
    assert(get(t,0) == 'c');
    assert(get(t,1) == 'a');
    assert(get(t,2) == 't');
    discard(t);
}

void testSet() {
    text *t = new("cat");
    set(t, 0, 'b');
    set(t, 2, 'r');
    assert(like(t, "bar"));
    discard(t);
}

void testCopy() {
    text *t = new("cat");
    text *t2 = copy(t);
    assert(like(t2, "cat"));
    discard(t);
    discard(t2);
}

void testCompare() {
    text *t = new("cat");
    text *t2 = new("cat");
    assert(compare(t, t2) == 0);
    text *t3 = new("cas");
    assert(compare(t, t3) > 0);
    text *t4 = new("cau");
    assert(compare(t, t4) < 0);
    discard(t);
    discard(t2);
    discard(t3);
    discard(t4);
}

void testAppend() {
    text *t = new("car");
    text *t2 = new("pet");
    append(t, t2);
    assert(like(t, "carpet"));
    discard(t);
    discard(t2);
}

void testSlice() {
    text *t = new("carpet");
    text *t2 = slice(t, 0, 3);
    assert(like(t2, "car"));
    text *t3 = slice(t, 3, 6);
    assert(like(t3, "pet"));
    discard(t);
    discard(t2);
    discard(t3);
}

void testFind() {
    text *t = new("carpet");
    text *t2 = new("car");
    assert(find(t, t2) == 0);
    text *t3 = new("pet");
    assert(find(t, t3) == 3);
    text *t4 = new("cat");
    assert(find(t, t4) == -1);
    discard(t);
    discard(t2);
    discard(t3);
    discard(t4);
}

// Test the library.  (With a real library, a renaming scheme would be needed.)
int textMain() {
    testNew();
    testLength();
    testGet();
    testSet();
    testCopy();
    testCompare();
    testAppend();
    testSlice();
    testFind();
    printf("Tests all pass.");
    return 0;
}
