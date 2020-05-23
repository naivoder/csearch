#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int result, errno;

  if(argc < 3 || argc > 3) {
    Usage(argv[0]);
    exit(1);
  }
  system("clear");

  result = Search_File(argv[1], argv[2]);
  if(result == -1) {
    perror("Error");
    printf("Error number = %d\n", errno)
    exit(1)
  }
  return(0);
}
