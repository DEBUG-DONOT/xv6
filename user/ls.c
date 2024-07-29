#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  //找到最后一个斜杠之后的第一个字符
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));//把p复制到buf里面
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));//将p后面的字符设置为空
  return buf;
}

void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, O_RDONLY)) < 0)
  {
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }//打开失败

  if(fstat(fd, &st) < 0)
  {
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }//查询fd指向的文件的信息

  switch(st.type)
  {
  case T_DEVICE:
  case T_FILE:
    printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;//如果是文件就给出这个文件的信息

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
    {
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);//到结尾
    *p++ = '/';//结尾加/
    while(read(fd, &de, sizeof(de)) == sizeof(de))//把fd的内容读到de中，de是一个目录文件的structure
    {
      if(de.inum == 0)//
        continue;
      memmove(p, de.name, DIRSIZ);
      //printf("de.name is %s",de.name);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){//获取文件信息
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit(0);
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit(0);
}
