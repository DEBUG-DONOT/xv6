struct stat;

// system calls
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(const char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);//返回fd文件信息，填充到stat中
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);

// ulib.c
int stat(const char*, struct stat*);//获取一个文件的状态信息
//const char *n: 要获取状态信息的文件路径
//struct stat *st: 用于存储文件状态信息的结构体指针

char* strcpy(char*, const char*);//后面的复制到前面里面去

void *memmove(void*, const void*, int);//将内存中的一个区域的值复制到另一个区域
//void *vdst: 目标内存区域的起始地址
//const void *vsrc: 源内存区域的起始地址
//int n: 要复制的字节数

char* strchr(const char*, char c);//查找c在一个字符中出现的第一个位置
int strcmp(const char*, const char*);//两个字符串相同返回0
void fprintf(int, const char*, ...);
void printf(const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);//将指定的从给定指针起始位置后unit个字符设置为int
void* malloc(uint);
void free(void*);
int atoi(const char*);
int memcmp(const void *, const void *, uint);
void *memcpy(void *, const void *, uint);
