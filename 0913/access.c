#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	if(access("abc", F_OK)<0){
		perror("access.c");
		exit(1);
	}

	printf("abc is ok\n");

	return 0;
}
