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
