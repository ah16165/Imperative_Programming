#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>

struct state
{
  int x0;
  int y0;
  int x1;
  int y1;
  bool pen;
};

struct state *newState()
{
  struct state *st;
  st = malloc(sizeof(struct state));
  st->x0 = 0;
  st->y0 = 0;
  st->x1 = 0;
  st->y1 = 0;
  st->pen = false;
  return st;
}


signed char findopcode(signed char x)
{
  signed char opcode;
  opcode = x>>6;
  opcode = opcode & (0x3);
  return opcode;
}

signed char findoperand(signed char x, int opcode)
{
  signed char operand;
  operand = (x) & (0x3f);
  if ((opcode == 0 || opcode == 1) && ((operand & (0x20)) == 32)) operand = operand | (-1 << 6);
  return operand;
}

void opcode1(int operand, struct state *st, display *d)
{
  st->y0 = st->y1;
  st->y1 = st->y1 + operand;
  if (st->pen == true) line(d, st->x0, st->y0, st->x1, st->y1);
  st->x0 = st->x1;
}

void opcode2(int operand, struct state *st, display *d)
{
  pause(d, (operand * 10));
}

void opcode3(int operand, struct state *st)
{
  if (st->pen == false) st->pen = true;
  else st->pen = false;
}

void opcode0(int operand, struct state *st)
{
  st->x0 = st->x1;
  st->x1 = st->x1 + operand;
}

void dissect(signed char x, struct state *st, display *d)
{
  int opcode = findopcode(x);
  int operand = findoperand(x, opcode);

  if (opcode == 0) opcode0(operand, st);
  else if (opcode == 1) opcode1(operand, st, d);
  else if (opcode == 2) opcode2(operand, st, d);
  else if (opcode == 3) opcode3(operand, st);
}

void extract(char *inputFile)
{

  FILE *in = fopen(inputFile,"rb");
  if (in == NULL)
  {
    fprintf(stderr, "Can't open %s\n", inputFile);
    exit(1);
  }

  struct display *d = newDisplay(inputFile, 200, 200);
  struct state *st = newState();

  signed char byte = fgetc(in);
  while(!feof(in))
  {
    dissect(byte, st, d);
    byte = fgetc(in);
  }

  end(d);
  free(st);
  free(d);
  fclose(in);


}

int main(int n, char *args[])
{
if (n==2) extract(args[1]);
else
  {
  fprintf(stderr, "You have to type ./sketch line.sketch\n" );
  exit(1);
  }

}
