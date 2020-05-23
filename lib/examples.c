#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "examples.h"

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
			printf("Match on line: %d\n", line_num);
			printf("'%s'\n", temp);
			find_result++;
		}
		line_num++;
	}

	if(fp) {
		fclose(fp);
	}

  return find_result;
}
