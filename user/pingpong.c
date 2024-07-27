#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int p[2];
    pipe(p);
    int pid=fork();
    if(pid==0)
    {
        
        char buf[4];
        read(p[1],buf,4);
        printf("%d: received ping\n",getpid());
        write(p[0],"pong",4);
        exit(0);
    }
    else
    {
        write(p[1],"ping",4);
        close(p[1]);
        wait(&pid);
        char buf[4];
        read(p[0],buf,4);
        close(p[0]);
        printf("%d: received pong\n",getpid());
        exit(0);
    }

}