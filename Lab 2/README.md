# Lab 2
## Assignment 1
```c
#include <stdio.h>

int is_prime(int n){
  for (int i = 2; i < n; i++)
    if(n % i == 0)
      return 0;

  return 1;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
```

## Assignment 2
```c
#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int is_prime(int n){
  for (int i = 2; i < n; i++)
    if(n % i == 0)
      return 0;

  return 1;
}
int numOfPrints = 0;
void print_number(int n){
  printf("%10d ", n);
  
  if(numOfPrints % COLUMNS == 5){
    printf("\n");
  }
  numOfPrints++;
  
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
  for(int i = 2; i < n; i++){
    int isPrime = is_prime(i);
    if(isPrime == 1){
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
```


• What does it mean when a function does not return a value? How do you state that in a program? How can then the function (or more precisely, the procedure) perform anything useful? 

Answer: When a function doesn’t return a value it means that the function only updates arguments or variables but does not return anything to where the function was called.
Stating that a function won’t return a value is done with keyword void.
The function can still be useful since variables and arguments can be changed.

• How did you implement the side effect that is needed to make print_number behave correctly?

Answer: (Supposed that the side effect was that if the function was called more than once it would separate the numbers into rows after a certain amount of columns was filled) It was implemented by creating an int called numOfPrints and adding 1 for every prime number that was printed and by checking that numOfPrints / COLUMNS would give the remainder 5. 


## Assignment 3
### Task 1
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6

int numOfPrints = 0;
void print_number(int n){
  printf("%10d ", n);
  
  if(numOfPrints % COLUMNS == 5){
    printf("\n");
  }
  numOfPrints++;  
}

void print_sieves(int maxPNumVar){
  char arr[maxPNumVar];
   for (int i = 0; i <= maxPNumVar; i++){
     arr[i] = 1;
   }

   for (int i = 2; i <= sqrt(maxPNumVar); i++){
     if (arr[i]){
       for(int j = pow(i,2); j <=maxPNumVar; j += i ){
          arr[j] = 0;
       }
     }
   }
   for (int i = 2; i <= maxPNumVar; i++){
     if(arr[i]){
      print_number(i);
     }
   }
}
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0; 
}
```

### Task 2
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>


#define COLUMNS 6

int numOfPrints = 0;
void print_number(int n){
  printf("%10d ", n);
  
  if(numOfPrints % COLUMNS == 5){
    printf("\n");
  }
  numOfPrints++;
  
}

void print_sieves(int maxPNumVar){
  char* p = (char*) malloc(maxPNumVar*sizeof(char));
   for (int i = 0; i <= maxPNumVar; i++){
     p[i] = 1;
   }

   for (int i = 2; i <= sqrt(maxPNumVar); i++){
     if (p[i]){
       for(int j = pow(i,2); j <=maxPNumVar; j += i ){
          p[j] = 0;
       }
     }
   }
   for (int i = 2; i <= maxPNumVar; i++){
     if(p[i]){
      print_number(i);
     }
   }
   free(p);
}
int main(int argc, char *argv[]){
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    if(argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an interger number.\n");


    gettimeofday(&stop, NULL);
    printf("took %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000); 
  return 0;
}
```

1. How did you represent the marking of 'prime' and 'not a prime' in the memory array?

Answer: The marking of prime was represented by either a 1, meaning that the number is prime, or a 0 meaning that the number is not prime.

2. Which are the main steps in the algorithm? How have you implemented these steps? 

Answer: The main step in the algorithm is first to mark all numbers with 1. Then to mark all the multiples of 2, 3, 5, 7, up until the square root of the parameter value with 0. After this procedure, only the prime numbers will have the value 1. 
Implemted using following commands:
```c
for (int i = 2; i <= sqrt(maxPNumVar); i++){
     if (p[i]){
       for(int j = pow(i,2); j <=maxPNumVar; j += i ){
          p[j] = 0;
       }
     }
   }
```

3. What is the largest prime number that you can print within 2 seconds of computation? What is the largest number you can print within 10 seconds? Is it the same for print_prime.c, sieves.c, and sieves-heap.c? Why or why not? 

Answer: Print-primes 2s	Print-primes 10s	Sieves-heap 2s	Sieves-heap 10s	Sieves 2s	Sieves 10s Around 8000	Around 50000 	Around 2000	Around 8000	Around 11000	Around 50000

The stack is faster because the access pattern is much simpler to allocate and deallocate memory. While heap is much more complex when allocation or deallocation. In the stack, each byte tends to be reused more frequently which maps out the processor’s cache which improves the speed even more.

## Assignment 4
```c
#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

int list1[20];
int list2[20];
int count = 0;
void copycodes(char* text, int* list, int* count){
  while (*text != 0){
    *list = *text;
    (*count)++;
    text++;
    list++;
  }
}

void work(){
  copycodes(text1, list1, &count);
  copycodes(text2, list2, &count);
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}
int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
```
1. Explain how you get the pointer addresses to the two char arrays (text1 and text2) and the counter variable (count) in function work()

Because the two char arrays text1 and text2 are declared globally they can be accessed within any functions, which in this case is work(). This works as well with the global variable count.

2. What does it mean to increment a pointer? What is the difference between incrementing the pointer that points to the ASCII text string, and incrementing the pointer that points to the integer array? In what way is the assembler code and the C code different? 

The result when incrementing a pointer pointing to the ASCII text string is the second letter in the string. The same goes for the integer array, if incremented by one it will point to the next number in the array. But the difference is an int will increase with 4 bytes and the pointer that points to the text string will increase 1 byte.

The difference between assembly code and c code is that a manual increase of 4 is needed in assembly for the pointer that points to the int array. But in c you don't need to specify how many bytes it needs to increase.

3. What is the difference between incrementing a pointer and incrementing a variable that a pointer points to? Explain how your code is incrementing the count variable.

Incrementing the variable that a pointer points to will not affect the pointer in any way but the variable’s value will be changed.
Incrementing a pointer will change the address which leads to the pointer pointing to something else.
```
(*count)++
```

4. Explain a statement in your code where you are dereferencing a pointer. What does this mean? Explain by comparing with the corresponding assembler code.

Dereferencing a pointer means accessing the data/value that the pointer points to with the corresponding address. 
```
lb	$t0,0($a0)
lw	$t1,0($a2)
```

5. Is your computer using big-endian or little-endian? How did you come to your conclusion? Is there any benefit of using either of the two alternatives?

The computer is There is no benefit to using either alternatives. 
By looking at the MSB and the LSB we came to our conclusion that the computer was using Little Endian

## Assignment 5
6. Consider AM18, AM19, and AF1. Explain why gv ends up with the incremented value, but m does not. 

Answer: When the function “fun(m)” is called, it’s parameter is the variable m. The function takes in m as an int called “param”. The first thing that happens is ‘param++’ which means adding +1 to param. The function then proceeds to saveword(“AF1: param”, &param); which in means add the text and the address of param. After this gv = param; This means that gv which is a global variable has been changed to param => m + 1. 
The reason for m staying the same is because no actual change has affected m. Since m isn’t a global variable the only way to change the value of m is to change the value which is addressed in. 

7. Pointer cp is a character pointer that points to a sequence of bytes. What is the size of the cp pointer itself? 

Answer: A pointer points to the address of a data-type, doesn’t matter if it’s an int, char, double array or anything in between. The pointer will only point to the address of the data-type in question. An address will always consist of 8 hexadecimal figures ⇔ 8 nibbles ⇔ 4 bytes. This means that a pointer will always have the size of 4 bytes wherever the address may lead. Therefore the point cp is the size of 4 bytes.

8. Explain how a C string is laid out in memory. Why does the character string that cp points to have to be 9 bytes? 

Answer: A string in C is laid out in memory as a char array with a null byte at the end. 
Eg. The string “Hello” in C is stored as such: 
 
 The same principle goes for the string “Bonjour!”. This means that for a string with n letters, the size of the char array will be n+1 to make room for the null byte at the end.

9. Which addresses have fun and main? Which sections are they located in? What kind of memory are they stored in? What is the meaning of the data that these symbols points to? 

Answer: The address of fun and main is gathered from the ChipKit program. Address for fun: 9D001180, address for main: 9D0011D8. The functions are located in the section 0x9D000000 and are stored in Program Flash according to the memory map.
The data that these symbols point to are the first instructions in the respective.

10. Which addresses are variables in and gv located at? Which memory sections according to the PIC32 memory map? Why? 

Answer: 
“in” is stored in address: A0000008
“gv” is stored in address: A000000C
The memory sections according to the PIC32 memory map are 0xA0000000 and are stored in RAM. The reason for this is because both variables are global which means that they are stored on the heap which stores in RAM.

11. Variables p and m are not global variables. Where are they allocated? Which memory section is used for these variables? Why are the address numbers for p and m much larger than for in and gv?

Answer: 
“p” is stored in address: A0003FE8
“m” is stored in address: A0003FE4
According to the memory map both variables are stored in Reserved and since they are local variables they are stored on the stack. The reason for why the addresses are much larger than for the global variables is because things stored on the heap are stored in very low addresses while things stored on the stack are stored on very high addresses. This is to avoid conflicting overwriting stack-stored variables and heap-stored variables.

12. At print statement AM5, what is the address of pointer p, what is the value of pointer p, and what value is pointer p pointing to?

“p” is stored in address: A0003FE8
P points to A0003FE4 which has the value 7.

13. At print statement AM7, what is the address of pointer p, what is the value of pointer p, and what value is pointer p pointing to?

“p” is stored in address: A0003FE8
P points to A0003FE4 which has the value 8.

14. Consider AM14 to AM17. Is the PIC32 processor using big-endian or little-endian? Why?

The PIC32 processor is little-endian because the value of pointer p gets changed to 0x1234abcd and the data in the char array is ordered as follows: cd, ab, 34, 12 which is the LSB ordered first and MSB ordered last.

