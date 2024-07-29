#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];
void core(int argc, char *argv[])
{
    const int num=argc+1;
    char* allArgs[num];
    //char buf[512];
    for(int i=1;i<argc;i++)
        allArgs[i-1]=argv[i];
    allArgs[num-1]=0;
    if(fork()==0)
    {
        gets(buf,512);
        buf[strlen(buf)-1]='\0';
        allArgs[num-2]=buf;
        exec(argv[1],allArgs);
        printf("exec error\n");
    }
    else
    {
        wait(0);
        core(argc,argv);
    }
}
//读取命令和参数
int main(int argc, char *argv[])
{
    const int num=argc;
    char* allArgs[num];
    for(int i=1;i<argc;i++)
        allArgs[i-1]=argv[i];
    //allArgs[num-1]=0;
    if(fork()==0)
    {
        gets(buf,512);
        allArgs[num-1]=buf;
        exec(argv[1],allArgs);
        printf("exec error\n");
    }
    else
    {
        wait(0);
        core(argc,argv);
    }
    return 0;
    
}