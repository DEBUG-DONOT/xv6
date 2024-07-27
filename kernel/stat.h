#define T_DIR     1   // Directory
#define T_FILE    2   // File
#define T_DEVICE  3   // Device
//文件描述结构体
struct stat {
  int dev;     // File system's disk device
  uint ino;    // Inode number 这个是关键，每个文件具有唯一的inode number,可以有很多别名
  short type;  // Type of file
  short nlink; // Number of links to file
  uint64 size; // Size of file in bytes
};
