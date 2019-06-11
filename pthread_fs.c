#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <asm/ldt.h>
#include <sys/syscall.h>
#include <mutex>

#define NUM_THR 20

#define LDT_FIRST_ENTRY 512
#define LDT_SIZE 8192

/* the local copy of the LDT */
struct ldt_local_copy {
  void* base;          /* base address or 0 if entry is free   */
  unsigned long limit; /* limit in bytes or 0 if entry is free */
};

static struct ldt_local_copy ldt_info[LDT_SIZE] = {
{0, 0},
};

static int mLdtIndex = -1;
std::recursive_mutex mtx_;


static inline int modify_ldt(int func, void* ptr, unsigned long count) {
  return syscall(__NR_modify_ldt, func, ptr, count);
}



void construct_ldt_entry() {
  int i;
  /* initialize LDT_ENTRY list */
  for (i = LDT_FIRST_ENTRY; i < LDT_SIZE; i++) {
    ldt_info[i].base = NULL;
    ldt_info[i].limit = 0;
  }
}



int get_free_ldt_index() {
  std::lock_guard<std::recursive_mutex> lg(mtx_);
  int i;
  for (i = LDT_FIRST_ENTRY; i < LDT_SIZE; i++) {
    if (ldt_info[i].base == NULL && ldt_info[i].limit == 0) {
      return i;
    }
  }
  return -1;
}

int set_ldt_entry(int index, void* addr, int size) {
  std::lock_guard<std::recursive_mutex> lg(mtx_);
  struct user_desc entry = {
      0,
  };

  if (index < LDT_FIRST_ENTRY) {
    return -1; /* cannot modify reserved entries */
  }

  /* make new request */
  entry.entry_number = (unsigned int)index;
  entry.base_addr = (unsigned long)addr;
  entry.limit = size;
  entry.seg_32bit = 0x1;
  entry.contents = 0x0;
  entry.read_exec_only = 0x0;
  entry.limit_in_pages = 0x0;
  entry.seg_not_present = 0x0;
  entry.useable = 0x1;

  /* set ldt */
  if (modify_ldt(0x11, (void*)&entry, sizeof(entry)) < 0) {
    return -1;
  }

  /* mark entry ia occupied */
  ldt_info[index].base = addr;
  ldt_info[index].limit = size;

  return 0;
}



void set_fs_register(unsigned int val){
  __asm__ __volatile__(
      "push %%eax\n\t\
                                   movl %0, %%eax\n\t\
                                   movl %%eax, %%fs\n\t\
                                   pop %%eax" ::"r"(val)
      : "%eax");

}

unsigned int ldt_index_to_selector(int index) {
  //http://ezbeat.tistory.com/143 밑에 보기.
  //fsregisterVal = 0b 0000000000000  0 00
  //                    index        TI RPL  (TI는 0이면 GDT, 1이면 LDT)
  //                             1    1  11

  return (index << 3 | 0x1 << 2 | 0x1 << 1 | 0x1);
}




void* t_function(void*data){

      int ldtIndex = get_free_ldt_index();
      if (set_ldt_entry(ldtIndex, NULL, 
                                    0x100) < 0) {
        exit(-1);
      }
      set_fs_register(
          ldt_index_to_selector(ldtIndex));

	  sleep(5);
}


int main(){

  pthread_t p_thread[NUM_THR];
  int thr_id;
  int status;
  int i;

  for(i =0; i < NUM_THR; ++i){
     thr_id = pthread_create(&p_thread[i], NULL, t_function, NULL);
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
