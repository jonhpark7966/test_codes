#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THR 5

void set_fs_register(unsigned int val){
  __asm__ __volatile__(
      "push %%eax\n\t\
                                   movl %0, %%eax\n\t\
                                   movl %%eax, %%fs\n\t\
                                   pop %%eax" ::"r"(val)
      : "%eax");

}


void* t_function(void*data){

	while(1){
      printf("%d\n", *((int*)data));
	  set_fs_register(*((int*)data));
	  sleep(1);
	}
}


int main(){

  pthread_t p_thread[NUM_THR];
  int thr_id;
  int status;
  int id[NUM_THR];
  int i;

  for(i =0; i < NUM_THR; ++i){
	 id[i] = i;
     thr_id = pthread_create(&p_thread[i], NULL, t_function, (void*)&(id[i]));
	 if(thr_id<0){
	   perror("thread create error: ");
	   exit(0);
	 }
  }

  for(i = 0; i < NUM_THR; ++i){
    pthread_join(p_thread[i], (void**)&status); 
  }

  return 0;
}
