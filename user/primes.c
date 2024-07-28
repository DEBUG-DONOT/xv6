#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
//筛选素数
//遇到素数就print出来
//遇到除本身除不尽的就传递给下一个
//问题就在于这里只能用fork创建新的进程
//

void core(int pipeIn)
{
    int prime;
    read(pipeIn,&prime,sizeof(int));
    printf("prime %d\n",prime);
    int curr;
    // while (read(pipeIn,&curr,sizeof(int)))
    // {
    //     if(curr%prime==0) continue;
    //     else break;
    // }
    int flag=read(pipeIn,&curr,sizeof(int));
    if(!flag) return ;
    int newPipe[2];
    pipe(newPipe);
    if(fork()==0)
    {
        close(newPipe[1]);
        core(newPipe[0]);
    }
    else
    {   
        close(newPipe[0]);
        if(curr%prime!=0) write(newPipe[1],&curr,sizeof(int));
        //因为前面为了判断后面还有没有数字进行了一次read，fd中的尾部移动了，所以这里要补一个write
        while (read(pipeIn,&curr,sizeof(int)))
        {
            if(curr%prime!=0) write(newPipe[1],&curr,sizeof(int));
        }
        close(pipeIn);
        close(newPipe[1]);
        wait(0);
    }
    exit(0);
}

int main()
{
    int pp[2];
    pipe(pp);
    if(fork()==0)
    {
        close(pp[1]);
        core(pp[0]);
    }
    else
    {
        close(pp[0]);
        for(int i=2;i<=35;i++)
        {
             write(pp[1],&i,sizeof(int));
        }
        close(pp[1]);
        wait(0);
        exit(0);
    }
    return 0;
}

