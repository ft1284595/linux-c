#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	close(STDOUT_FILENO);
	fd = open("test", O_CREAT|O_APPEND|O_RDWR);	
	printf("%s\n", "helloworld");

	return 0;
}
