#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(void)
{
	char buf[1024];

	read(STDIN_FILENO,buf, sizeof(buf));
	write(STDOUT_FILENO,buf, strlen(buf));

	return 0;
}

