#include <dlfcn.h>

int main(){
  void* handle = dlopen("libC.so", RTLD_NOW);

  void (*printI)(void);
  *(void**)(&printI) = dlsym(handle, "printI");

  printI();

  return 0;
}
