#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
char* itoa(int value, char* str) {
    char* pos = str;
    if (value < 0) {
        *pos++ = '-';
        value = -value;
    }
    int digit = value % 10;
    if ((value / 10) > 0) {
        pos = itoa(value / 10, pos);
    }
    *pos++ = digit + '0';
    *pos = '\0';
    return str;
}
int main()
{
  int ping[2];
  int pong[2];
  int op[2];
  close(0);
  close(1);
  pipe(op);
  pipe(ping);
  pipe(pong);
  int pid=fork();
  if(pid==0)//子进程
  {
    //close(1);
  
    int childPid=getpid();
    char cc[512];
    itoa(childPid,cc);
    write(pong[1],"pong",4);
    close(pong[0]);
    close(pong[1]);
    char buf[4];
    read(ping[0],buf,4);
    write(op[1],cc,strlen(cc));
    write(op[1],": received ping\n",17);
    exit(0);
  }
  else//父进程
  {
    //wait(&pid);加wait会死锁

    int parentPid=getpid();
    char cp[512];
    char buf[4];
    itoa(parentPid,cp);
    read(pong[0],buf,4);
    write(op[1],cp,strlen(cp));
    write(op[1],": received pong\n",17);

    write(ping[1],"ping",4);
    close(ping[0]);
    close(ping[1]);
    exit(0);
  }
}