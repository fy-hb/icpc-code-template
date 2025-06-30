#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int fd = 0; // 0 为 stdin ; 其他文件用 int fd = open("*.in", O_RDONLY);
struct stat state; fstat(fd, &state); int len = state.st_size;
char* addr = (char*) mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
