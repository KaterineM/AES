#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define F 128

void printer(int array[F], int n);
void bitGenerator(int b[128]);

void bitGenerator(int b[128]){
	srand ( time(NULL) );
	for(int i=0 ; i<128 ; i++)
		b[i] = rand() % 2;
}

void printer(int array[F], int n){
  for(int i=0 ; i<n ; i++){
    printf("%u", array[i]);
  }
  printf("\n");
}

int main(int argc, char const *argv[]) {

  int b[128];
  bitGenerator(b);
  printf("b: \n");
  printer(b,F);

  return 0;
}
