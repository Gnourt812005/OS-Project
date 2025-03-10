#include "kernel/types.h"
// #include "kernel/sysinfo.h"
#include "user/user.h"

void testcall(void) {
  struct sysinfo tmp;
  if (sysinfo(&tmp) < 0) {
    printf("sys_info failed\n");
    exit(1);
  }
  printf("sys_info call succeeded\n");
}

uint64 testmem(void) {
  struct sysinfo tmp;
  if (sysinfo(&tmp) < 0) {
    printf("sys_info failed\n");
    exit(1);
  }
  if (tmp.freemem <= 0) {
    printf("sys_info: invalid free memory: %d\n", tmp.freemem);
    exit(1);
  }
  printf("sys_info: free memory: %d bytes\n", tmp.freemem);
  return tmp.freemem;
}

uint64 testproc(void) {
  struct sysinfo tmp;
  if (sysinfo(&tmp) < 0) {
    printf("sys_info failed\n");
    exit(1);
  }
  if (tmp.nproc <= 0) {
    printf("sys_info: invalid number of processes: %d\n", tmp.nproc);
    exit(1);
  }
  printf("sys_info: number of processes: %d\n", tmp.nproc);
  return tmp.nproc;
}

int main(void) {
  printf("========================INIT=======================\n");
  // printf("sysinfotest: starting\n");
  testcall();
  uint64 m1 = testmem();
  uint64 t1 = testproc();

  printf("\n==================After using folk=================\n");
  int pid = fork();
  if (pid == 0) {
    printf("Child\n");
    testcall();
    testmem();
    testproc();
    exit(0);
  }
  else {
      wait(0);
  }

  printf("\n===========After child process completed===========\n");
  testcall();
  uint64 m2 = testmem();
  uint64 t2 = testproc();
  if (m1 == m2 && t1 == t2) printf("\nsysinfotest: OK\n");
  else printf("\nsysinfotest: error\n");

  exit(0);
}