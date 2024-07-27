#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc==1)//用户忘记传递参数
    {
        write(1,"Error:you should input sleep time",33);
        exit(0);
    }
    //从命令行中取得整数
    int sleepTime=atoi(argv[1]);
    sleep(sleepTime);
    exit(2);
}