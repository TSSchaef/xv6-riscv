#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void test1(){
  printf("Test 1: PASSED");
}

void test2(){
  printf("Test 2: PASSED");
}

int main(int argc, char *argv[]){
  test1();
  test2();
  return 0;
}
