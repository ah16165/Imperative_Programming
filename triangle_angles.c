/* Program that takes inputted angles and outputs a classfication of triangle.
Testing section is an adaptation from the triangle.c testing section produced by
Ian Hoyler. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

// Integer constants representing types of triangle.
enum { Equilateral, Isosceles, Right, Scalene, Flat, Impossible, Illegal };

// Function to check if an inputed character is part of an array including all
// decimal numbers, and returning false is the charcter is not a decimal integer.
bool IsDecimal(char x)
{
  long i;
  for (i = 0; i<10; i++ )
  {
    char decimals[] = {'0','1','2','3','4','5','6','7','8','9'};
    if (decimals[i] == x) return true;
  }
  return false;
}

// Function that uses a loop to check if any member of the input array is invalid
// (is not a decimal number via IsDecimal function, or the string starts with a 0
// when the string is greater than one character).
bool valid(const char angle[])
{
  long l = strlen (angle);
  long i;
  for (i = 0; i < l; i++)
  {
      if (IsDecimal(angle[i]) == false) return false;
      if ((strlen(angle) > 1) && angle[0] - '0' == 0) return false;
  }
  return true;
}

// Function that uses the atoi fucntion to convert the inputted string into the
// relative integer values. Returns the integer if the sting was valid, and
// returns -1 if not in order to cause an Illegal output.
long convert(const char angle[])
{
  long n = atoi (angle);
  if ((valid(angle)) == true) return n;
  else return -1;
}

// Function that takes in 3 strings from the user and converts these strings to
// integers using the convert function. Then returns a triangle type, or Illegal
// depending on inputted strings.
long triangle(const char a1[], const char a2[], const char a3[])
{
  long a = convert (a1);
  long b = convert (a2);
  long c = convert (a3);

  if (a < 0 || b < 0 || c < 0) return Illegal;
  if (a == 0 || b == 0 || c == 0) return Flat;
  if ((a + b + c) != 180) return Impossible;
  if (a == 60 && b == 60 && c == 60) return Equilateral;
  if (a == 90 || b == 90 || c == 90) return Right;
  if (((a == b) && (a != c)) || ((a == c) && (a != b)) || ((b == c) && (b != a))) return Isosceles;
  else return Scalene;
}

// -----------------------------------------------------------------------------
// User interface and testing.

void print(int type)
{
    switch (type)
    {
        case Equilateral: printf("Equilateral"); break;
        case Isosceles: printf("Isosceles"); break;
        case Right: printf("Right"); break;
        case Scalene: printf("Scalene"); break;
        case Flat: printf("Flat"); break;
        case Impossible: printf("Impossible"); break;
        case Illegal: printf("Illegal"); break;
    }
    printf("\n");
}

// Check that you haven't changed the triangle type constants.  (If you do, it
// spoils automatic marking, when your program is linked with a test program.)
void checkConstants()
{
    assert(Equilateral==0 && Isosceles==1 && Right==2 && Scalene==3);
    assert(Flat==4 && Impossible==5 && Illegal==6);
}

// Tests 1 to 2: check equilateral
void testEquilateral()
{
    assert(triangle("60", "60", "60") == Equilateral);
}

// Tests 3 to 5: check isosceles
void testIsosceles()
{
    assert(triangle("25", "25", "130") == Isosceles);
    assert(triangle("25", "130", "25") == Isosceles);
    assert(triangle("130", "25", "25") == Isosceles);
}

// Tests 6 to 14: check right angled
void testRight()
{
    assert(triangle("90", "50", "40") == Right);
    assert(triangle("40", "50", "90") == Right);
    assert(triangle("50", "90", "40") == Right);
    assert(triangle("90", "10", "80") == Right);
    assert(triangle("10", "90", "80") == Right);
    assert(triangle("80", "10", "90") == Right);
    assert(triangle("90", "45", "45") == Right);
    assert(triangle("45", "45", "90") == Right);
    assert(triangle("45", "90", "45") == Right);
}

// Tests 15 to 20: check scalene
void testScalene()
{
    assert(triangle("55", "62", "63") == Scalene);
    assert(triangle("55", "63", "62") == Scalene);
    assert(triangle("62", "55", "63") == Scalene);
    assert(triangle("62", "63", "55") == Scalene);
    assert(triangle("63", "55", "62") == Scalene);
    assert(triangle("63", "62", "55") == Scalene);
}

// Tests 21 to 25: check flat
void testFlat()
{
    assert(triangle("0", "0", "0") == Flat);
}

// Tests 26 to 31: check impossible
void testImpossible() {
    assert(triangle("2", "3", "13") == Impossible);
    assert(triangle("2", "13", "3") == Impossible);
    assert(triangle("3", "2", "13") == Impossible);
    assert(triangle("3", "13", "2") == Impossible);
    assert(triangle("13", "2", "3") == Impossible);
    assert(triangle("13", "3", "2") == Impossible);
}

// Tests 32 to 42: check illegal
void testIllegal()
{
    assert(triangle("-1", "-1", "-1") == Illegal);
    assert(triangle("-1", "10", "12") == Illegal);
    assert(triangle("10", "-1", "12") == Illegal);
    assert(triangle("10", "12", "-1") == Illegal);
    assert(triangle("x", "y", "z") == Illegal);
    assert(triangle("3", "4y", "5") == Illegal);
    assert(triangle("10", "12", "13.4") == Illegal);
    assert(triangle("03", "4", "5") == Illegal);
}

// Tests 43 to 47: check the upper limits on lengths
void testLimits()
{
    assert(triangle("2147483647","2147483647","2147483647") == Impossible);
    assert(triangle("2147483648","2147483647","2147483647") == Illegal);
    assert(triangle("2147483647","2147483648","2147483647") == Illegal);
    assert(triangle("2147483647","2147483647","2147483648") == Illegal);
    assert(triangle("2147483649","2147483649","2147483649") == Illegal);
}

// Tests 48 to 50: check for correct handling of overflow
void testOverflow() {
    assert(triangle("1100000000","1705032704","1805032704") == Impossible);
    assert(triangle("2000000001","2000000002","2000000003") == Impossible);
    assert(triangle("150000002","666666671","683333338") == Impossible);
}

// Run tests on the triangle function.
void test() {
    checkConstants();
    testEquilateral();
    testIsosceles();
    testRight();
    testScalene();
    testFlat();
    testImpossible();
    testIllegal();
    testLimits();
    testOverflow();
    printf("All tests passed\n");
}

// Run the program or, if there are no arguments, test it.
int main(int n, char **argv) {
    if (n == 1) {
        test();
    }
    else if (n == 4) {
        int result = triangle(argv[1], argv[2], argv[3]);
        print(result);
    }
    else {
        fprintf(stderr, "Use e.g.: ./triangle 3 4 5\n");
        exit(1);
    }
    return 0;
}
