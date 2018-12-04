#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * 每隔10s在/tmp/daemon.log中写入当前时间
 */

void sys_err(char *str, int returnNo)
{
	perror(str);
	exit(returnNo);
}

void daemonize()
{
	pid_t pid;
	pid_t pid_s;
	if((pid=fork()) < 0)
	{
		sys_err("fork", 1);
	}else if(pid > 0){	//parent
		exit(0);
	}
	pid_s = setsid();
	if(pid_s < 0)
	{
		sys_err("setsid", 2);
	}
	if(chdir("/") < 0){
		sys_err("chdir", 3);
	}
	umask(0);
	if(close(0) != 0){
		sys_err("close", 4);
	}
	if(open("/dev/null", O_RDWR) < 0){
		sys_err("open", 5);
	}
	if(dup2(0,1) == -1)
	{
		sys_err("dup2",6);
	}
	if(dup2(0,2) == -1)
	{
		sys_err("dup2",6);
	}
}

int main(void)
{
	time_t t;
	int fd;
	char buf[512];
	daemonize();
	fd = open("/tmp/daemon.log", O_RDWR|O_CREAT|O_APPEND, S_IRWXU|S_IRWXG|S_IRWXO);
	if(fd < 0){
		sys_err("main open", 5);
	}

	while(1){
		time(&t);
		ctime_r(&t, buf);
		write(fd, buf, strlen(buf));
		sleep(10);
	}

	if(close(fd) != 0){
		sys_err("main close", 6);
	}

	return 0;
}
