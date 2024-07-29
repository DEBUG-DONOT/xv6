#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

//问题在于怎么样把文件名弄出来
//以及怎么去递归
char* fmtname(char *path);
//@param path 用来打印路径的
void find(char* name,char* path)
{
    //print 递归
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    if((fd=open(path,O_RDONLY))<0)
    {
        fprintf(2,"find:cannot open %s\n",name);
        return ;
    }
    if(fstat(fd,&st)<0)
    {
        fprintf(2, "find: cannot stat %s\n", name);
        close(fd);
        return;
    }
    strcpy(buf,path);
    p=buf+strlen(buf);
    *p++='/';
    switch (st.type)
    {
    case T_DEVICE:
        break;
    case T_FILE:
        break;
    case T_DIR:
        while (read(fd,&de,sizeof(de))==sizeof(de))
        {
            if(de.inum==0) continue;
            if(strcmp(de.name,".")==0||strcmp(de.name,"..")==0) continue;
            //printf("de.name is %s\n",de.name);
            char* temp=p;
            strcpy(temp,de.name);
            if(strcmp(name,de.name)==0) //名字相同
            {
                //printf("find it!\n");
                //printf("buf is %s\n",buf);
                printf("%s\n",buf);
            } 
            //printf("buf now is %s\n",buf);
            find(name,buf);
        }
        break;
    default:
        break;
    }
    close(fd);
    return ;
}

int main(int argc, char *argv[])
{
    if(argc==1) 
    {
        printf("you should input file name\n");
        return 0;
    }
    char* name=argv[2];
    char* beginPath=argv[1];
    find(name,beginPath);
    return 0;
}