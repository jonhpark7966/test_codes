#include <stdio.h>
#include "b.h"
#include "a.h"

void printI(){
  printf("I am B!\n");
  printA();
};

void printB(){
  printf("printB() is called!\n");
};
