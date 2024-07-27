#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//echo的作用是将命令行中的文本输出到终端
//
int
main(int argc, char *argv[])
{
  int i;
  //argc 至少为1 因为程序名也算一个参数
  for(i = 1; i < argc; i++){
    write(1, argv[i], strlen(argv[i]));//将参数列表中的指针指向的东西写到标准输出上。
    if(i + 1 < argc){
      write(1, " ", 1);
    } else {
      write(1, "\n", 1);
    }
  }
  exit(0);
}
