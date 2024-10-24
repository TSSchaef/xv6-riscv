#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/*
 * Used to test scheduler functionalities and see that processes are 
 * getting the proper runtimes. Can be run inside fo the xv6 shell with
 * "schedtestc", prints output to the shell terminal
 */


void test1(){
  printf("Test 1: Child 2 should have ~3x more runtime than Child 1\n");
  
  int p, pid1 = -1;
  p = fork();
  if(p < 0){
    printf("Fork FAILED\n");
    exit(1);
  }

  if(p == 0){
    //child process 1
    stride(4);
    pid1 = getpid();

  } else {
    p = fork();
    if(p < 0){
      printf("Fork FAILED\n");
      exit(1);
    }

    if(p == 0){
      //child process 2
      stride(12);
    } else {
      //parent process
      exit(getpid());
    }
  }

  // long loop
  long long i;
  int r;
  for(i = 1; i < 1000000000; i++){
     if(i % 100000000 == 0){
       //Useless print function to avoid error in compilation
       printf("X\b");
     }
  }

  r = getruntime(); 
  if(getpid() == pid1){
    printf("Child 1 runtime: %d\n", r);
    exit(pid1);
  } else{
    printf("Child 2 runtime: %d\n", r);
  }
}




void test2(){
  printf("Test 2: \n");
  
  int p, pid1 = -1;
  p = fork();
  if(p < 0){
    printf("Fork FAILED\n");
    exit(1);
  }

  if(p == 0){
    //child process 1
    stride(4);
    pid1 = getpid();

    // long loop
    long long i;
    for(i = 1; i < 1000000000; i++){
      if(i % 100000000 == 0){
        //Useless print function to avoid error in compilation
        printf("X\b");
      }
    }

  } else {
    p = fork();
    if(p < 0){
      printf("Fork FAILED\n");
      exit(1);
    }

    if(p == 0){
      //child process 2
      stride(12);
      // "I/O" loop
      long long i;
      for(i = 1; i < 100; i++){
        sleep(1);
      }
    } else {
      //parent process
      exit(getpid());
    }
  }

  int r;
  r = getruntime(); 
  if(getpid() == pid1){
    printf("Child 1 runtime: %d\n", r);
    exit(pid1);
  } else{
    printf("Child 2 runtime: %d\n", r);
  }
}

int main(int argc, char *argv[]){
  test1();
  test2();
  return 0;
}
