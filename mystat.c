#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	struct stat statbuf;
	int i;
	i = stat("/home/zx/study/linux-c/.gitignore", &statbuf);

	printf("%d\n", i);

	return 0;
}
