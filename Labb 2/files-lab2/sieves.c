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
