#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 8192

int main(int argc, char *argv[])
{
	char buf[SIZE];
	int fd_src, fd_dest, len;

	if(argc < 3)
	{
		printf("./mycp src dest\n");
		exit(1);
	}

	fd_src = open(argv[1], O_RDONLY);
	fd_dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	
	/**
	 * read()函数成功返回读到的字节数
	 * 读到文件末尾返回0
	 * 读取失败返回-1
	 */
	while(len = read(fd_src, buf, sizeof(buf)))
	{
		write(fd_dest, buf, len);
	}

	close(fd_src);
	close(fd_dest);

	return 0;
}
