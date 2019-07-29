/* Calculate a grade from a mark. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

// Integer constants representing grades.
enum { G1, G21, G22, G3, Fail, Invalid };

// Function to check if a variable is part of an array including all decimal numbers.
bool IsDecimal(char x)
{
  int i;
  for (i = 0; i<10; i++ )
  {
    char decimals[] = {'0','1','2','3','4','5','6','7','8','9'};
    if (decimals[i] == x) return true;
  }
  return false;
}

// Check whether a mark string is properly formatted and in range.
bool valid(int n, const char mark[])
{
  if ((n == 1) && IsDecimal(mark[0]) == true  ) return true;
  if ((n == 2) && (IsDecimal(mark[0]) == true) && (IsDecimal(mark[1]) == true) && (mark[0] - '0' != 0) ) return true;
  if ((n == 3) && (IsDecimal(mark[0]) == true) && (IsDecimal(mark[1]) == true) && (IsDecimal(mark[2]) == true) && (mark[0] - '0' != 0)) return true;
  if (n>3) return false;
  else return false;

}

// Convert a mark string into an integer.
int convert(int n, const char mark[])
{
  if (valid (n, mark))
  {
  if (n == 3) return (((mark[0] - '0')*100) + ((mark [1] - '0')*10) + (mark[2] - '0'));
  if (n == 1) return mark[0] - '0';
  if (n==2) return (((mark[0] - '0')*10) + (mark [1] - '0'));
  }
  else return -1;
}

// Convert a mark string into a grade.
int grade(int n, const char mark[])
{
    int m = convert(n,mark);
    if (m < 40 && m >= 0) return Fail;
    else if (m < 50 && m >= 40) return G3;
    else if (m < 60 && m >= 50) return G22;
    else if (m < 70 && m >= 60) return G21;
    else if (m <= 100 && m >= 70) return G1;
    else return Invalid;
}

// -----------------------------------------------------------------------------
// User interface and testing.

// Print out a grade.
void print(int grade) {
    if (grade == G1) printf("First\n");
    else if (grade == G21) printf("Upper second\n");
    else if (grade == G22) printf("Lower second\n");
    else if (grade == G3) printf("Third\n");
    else if (grade == Fail) printf("Fail\n");
    else if (grade == Invalid) printf("Invalid mark\n");
}

// Check that you haven't changed the grade constants.  (If you do, it spoils
// automatic marking, when your program is linked with a test program.)
void checkConstants() {
    assert(G1==0 && G21==1 && G22==2 && G3==3 && Fail==4 && Invalid==5);
}

// Test each grade (tests 1 to 5)
void testGrades() {
    assert(grade(2, "35") == Fail);
    assert(grade(2, "45") == G3);
    assert(grade(2, "55") == G22);
    assert(grade(2, "65") == G21);
    assert(grade(2, "75") == G1);
}

// Test the boundary points of the grades (tests 6 to 15)
void testBoundaries() {
    assert(grade(1, "0") == Fail);
    assert(grade(2, "39") == Fail);
    assert(grade(2, "40") == G3);
    assert(grade(2, "49") == G3);
    assert(grade(2, "50") == G22);
    assert(grade(2, "59") == G22);
    assert(grade(2, "60") == G21);
    assert(grade(2, "69") == G21);
    assert(grade(2, "70") == G1);
    assert(grade(3, "100") == G1);
}

// Test that grade only accepts valid marks, and rejects non-digits, numbers
// outside the range 0..100, and unnecessary leading zeros (tests 16 to 25)
void testValidity() {
    assert(grade(4, "40.5") == Invalid);
    assert(grade(1, "x") == Invalid);
    assert(grade(2, "-1") == Invalid);
    assert(grade(4, "40x5") == Invalid);
    assert(grade(3, " 40") == Invalid);
    assert(grade(3, "40 ") == Invalid);
    assert(grade(3, "101") == Invalid);
    assert(grade(3, "547") == Invalid);
    assert(grade(2, "01") == Invalid);
    assert(grade(3, "040") == Invalid);
}

// Run the tests.
void test() {
    checkConstants();
    testGrades();
    testBoundaries();
    testValidity();
    printf("All tests pass\n");
}

// Deal with input and output. If there are no arguments call test. If there is
// one argument, calculate and print the grade.
int main(int n, char *args[n]) {
    if (n == 1) test();
    else if (n == 2) print(grade(strlen(args[1]), args[1]));
    else {
        fprintf(stderr, "Use:   ./grade   or   ./grade m\n");
        fprintf(stderr, "where m is an integer mark from 0 to 100\n");
        return 1;
    }
    return 0;
}
