#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_file(char *str, char *fname);
void instruct(char *filename);

void instruct(char *filename) {
	printf("Proper Usage: %s <file> <string>\n", filename);
}

int search_file(char *fname, char *str) {
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];

	if((fp = fopen(fname, "r")) == NULL) {
		return(-1);
	}

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			printf("A match found on line: %d\n", line_num);
			printf("\n%s\n", temp);
			find_result++;
		}
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}

	if(fp) {
		fclose(fp);
	}
   	return(0);
}

int main(int argc, char *argv[]) {
  int result, errno;

  if(argc < 3 || argc > 3) {
    instruct(argv[0]);
    exit(1);
  }
  system("clear");

  result = search_file(argv[1], argv[2]);
  if(result == -1) {
    perror("Error");
    printf("Error number = %d\n", errno);
    exit(1);
  }
  return(0);
}
