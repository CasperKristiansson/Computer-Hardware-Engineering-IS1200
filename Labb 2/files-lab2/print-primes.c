/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int COUNT = 0;

void print_number(int n) {
  printf("%d ", n); 

  if(COUNT % COLUMNS == 5) {
    printf("\n");
  }
  COUNT++;
}

int is_prime(int n){
  double m = sqrt(n);
  for (int i = 2; i < m; i++)
    if(n % i == 0)
      return 0;
  return 1;
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

  for(int i = 2; i < n; i++){
    int primeNummber = is_prime(i);
    if(primeNummber) {
      print_number(i);
    }
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}
