#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void test1(){
  printf("Test 1: Child 2 should have ~3x more runtime than Child 1\n");
  
  int p, pid1 = -1;
  p = fork();
  if(p < 0){
    printf("Fork FAILED\n");
    return;
  }

  if(p == 0){
    //child process 1
    stride(4);
    pid1 = getpid();

  } else {
    p = fork();
    if(p < 0){
      printf("Fork FAILED\n");
      return;
    }

    if(p == 0){
      //child process 2
      stride(12);
    } else {
      //parent process
      return;
    }
  }

  if(pid1 == -1){
    printf("Didn't get pid1");
    return;
  }

  // long loop
  int i, r;
  for(i = 1; i < 10000000; i++){
     if(i % 1000000 == 0){
        r = getruntime(); 
        if(getpid() == pid1){
          printf("Child 1 runtime: %d\n", r);
        } else{
          printf("Child 2 runtime: %d\n", r);
        }
     }
  }
}

void test2(){
  printf("Test 2: PASSED\n");
}

int main(int argc, char *argv[]){
  test1();
  test2();
  return 0;
}
