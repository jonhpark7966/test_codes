#include <stdio.h>
#include "a.h"
#include "b.h"

void printI(){
  printf("I am A!\n");
  printB();
}

void printA(){
  printf("printA() is called!\n");
};
