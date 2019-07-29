#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

  char value[200];
  strcpy(value, "/system/lib/i386-linux-gnu/windows/dlls/:");
  strcat(value, getenv("LD_LIBRARY_PATH"));

  setenv("LD_LIBRARY_PATH", value, 1);

  char* result = getenv("LD_LIBRARY_PATH");
  printf("%s\n", result);

  return 0;

}
