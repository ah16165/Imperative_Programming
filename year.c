// Take an input from the user in the form of a  past year from the 20 or 21st century
// and give the user information about said year.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


// Function to check if a variable array is part of an array including all decimal numbers.
bool IsDecimal(char x[])
{
  int i;
  for (i = 0; i<4; i++)
  {
    if((x[i] != '1') && (x[i] != '2') && (x[i] != '3') && (x[i] != '4') && (x[i] != '5') &&
    (x[i] != '6') && (x[i] != '7') && (x[i] != '8') && (x[i] != '9') && (x[i] != '0')) return false;
  }
  return true;
}

// Function to check input year is within correct range, and of correct format.
bool valid(int n, char x[])
{
  int year = atoi(x);
  if (IsDecimal(x) == false) return false;
  if (year<1900) return false;
  if (year>2017) return false;
  else return true;
}

// Function to check if year is prime.
bool prime(int x)
{
  for (int i=2; i<x; i++)
  {
    if (x % i == 0) return false;
  }
  return true;
}

// Function to check if year is even.
bool even(int x)
{
  if (x % 2 == 0) return true;
  else return false;
}

//Function to check if year is palindromic.
bool palin(char a[])
{
  if ((a[0] == a[3]) && (a[1] == a[2])) return true;
  else return false;
}

// Function to check if year is a leap year.
bool leap(int x)
{
  if(x % 400 == 0) return true;
  if((x % 4 == 0) && (x % 100 != 0)) return true;
  else return false;
}

//Function that checks all previous function and prints the statistics of each function.
//Also converts the string into an integer for the previous functions to use.
void stats(int n, char a[])
{
  int num = atoi(a);
  if (prime(num) == true) printf("%d is a prime number.\n",num);
  if (prime(num) == false) printf("%d is not a prime number.\n",num);
  if (even(num) == true) printf("%d is an even number.\n",num);
  if (even(num) == false) printf("%d is an odd number.\n",num);
  if (palin(a) == true) printf("%d is a palindromic number.\n",num);
  if (palin(a) == false) printf("%d is not a palindromic number.\n",num);
  if (leap(num) == true) printf("%d is a leap year.\n",num);
  if (leap(num) == false) printf("%d is not a leap year.\n",num);
}


// Testing:

// Test the input string is a valid year
void testvalid()
{
  assert(valid(4,"2000") == true);
  assert(valid(4,"2015") == true);
  assert(valid(4,"1900") == true);
  assert(valid(4,"1953") == true);
  assert(valid(4,"2018") == false);
  assert(valid(4,"1873") == false);
  assert(valid(4,"12") == false);
  assert(valid(4,"30000") == false);
}

// Tests the input is prime.
void testprime()
{
  assert(prime(2000) == false);
  assert(prime(1993) == true);
  assert(prime(1953) == false);
  assert(prime(2017) == true);
}

//Test the input is even.
void testeven()
{
  assert(even(2000) == true);
  assert(even(1999) == false);
  assert(even(1905) ==  false);
  assert(even(2016) == true);
}

//Tests the input is palindromic.
void testpalin()
{
  assert(palin("2002") == true);
  assert(palin("1997") == false);
  assert(palin("1991") == true);
  assert(palin("2012") == false);
}

//Tests the input is a leap year.
void testleap()
{
  assert(leap(1952) == true);
  assert(leap(1904) == true);
  assert(leap(2000) == true);
  assert(leap(2012) == true);
  assert(leap(2006) == false);
  assert(leap(1963) == false);

}

// Overall testing
void test()
{
    testvalid();
    testprime();
    testeven();
    testpalin();
    testleap();
    printf("All tests passed.\n");
}


// Run the program with no args to carry out the tests, or with a string to
// run the programme.
int main(int n, char *args[n]) {
    if (n == 1) test();
    else if (valid(strlen(args[1]), args[1]) == false)
    {
        fprintf(stderr, "Use:   ./year   or   ./year m where m is a year from 1900 to 2017\n");
        return 1;
    }
    else if (n == 2) stats(strlen(args[1]), args[1]);
    else
    {
        fprintf(stderr, "Use:   ./year   or   ./year m where m is a year from 1900 to 2017\n");
        return 1;
    }
    return 0;
}
