#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit()
{
  int exitcode;
  if(argint(0,&exitcode) < 0){
	cprintf("Error in sys_exit\n");
	return -1;
  }
  exit(exitcode);
  return -1;
}

int
sys_wait(void)
{
  int *pt;
  if(argptr(0, (char **)&pt, sizeof(pt)) < 0){
     cprintf("Error in sys_wait !\n");
     return -1;
  }
  return wait(pt);
}

int 
sys_update_prior(void){
   int prior;
   if(argint(0, &prior) < 0){
 	cprintf("Error in sys_update_prior\n");
   	return -1;
   }
   return update_prior(prior);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
