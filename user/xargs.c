#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void core(char* allArgs[],int num)
{
   char newBuf[50];
   int p[2];
   pipe(p);
   if(fork()==0)
   {
        gets(newBuf,50);
        int i=0;
        if(strlen(newBuf) ==0)
        {
            i=-1;
            write(p[1],&i,sizeof(int));
            close(p[1]);
            return ;
        } 
        newBuf[strlen(newBuf)-1]='\0';
        //printf("core child: buf is%s\n",newBuf);
        allArgs[num-1]=newBuf;
        write(p[1],&i,sizeof(int));
        close(p[1]);
        exec(allArgs[0],allArgs);
        printf("exec error\n");
   }
   else
   {
        wait(0);
        //printf("core pa\n");
        int i=0;
        read(p[0],&i,sizeof(int));
        close(p[0]);
        //printf("core before return\n");
        if(i==-1)
        {
          //  printf("i=-1\n");
            return ;
        }
        //printf("core after return\n");
        core(allArgs,num);
   }
}
//读取命令和参数
int main(int argc, char *argv[])
{
    const int num=argc;
    char* allArgs[num];
    char buf[50];
    for(int i=1;i<argc;i++)
        allArgs[i-1]=argv[i];
    if(fork()==0)
    {
        gets(buf,50);
        if(buf==0) return 0; 
        buf[strlen(buf)-1]='\0';
        //printf("main child: buf is%s\n",buf);
        allArgs[num-1]=buf;
        exec(allArgs[0],allArgs);
        printf("exec error\n");
    }
    else
    {
        wait(0);
        //printf("main pa\n");
        core(allArgs,num);
        exit(0);
    }
    return 0;
}