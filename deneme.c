#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int fd = open("data.csv", O_RDONLY, S_IRUSR | S_IWUSR);
  if (fd == -1)
      return(printf("File open error!\n"), -1);
  struct stat st;
  if (fstat(fd, &st) == -1)
      return(printf("Fstat error!\n"), -1);
  printf("File size = %f KB\n", (double)st.st_size / 1024.f);
  char *file_in_memory = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  for (int i = 0; i < (int) st.st_size; i++) {
    printf("%c", file_in_memory[i]);
  }
  return 0;
}
