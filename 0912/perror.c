#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h



int main(void)
{
	int fd = open("abc", O_WRONLY);
	if(fd < 0)
	{
		printf("zx %s\n", strerror(errno));
		//printf("errno = %d\n", errno);
		//perror("main open");
	}
	printf("fd=%d\n", fd);





	return 0;
}
