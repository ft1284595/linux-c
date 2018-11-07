#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid, pid_c;
	//调用1次返回2次,在父进程返回子进程的PID,在子进程返回0;
	
	int n = 10;
	pid = fork();

	if(pid > 0){
		//in parent
		while(1){
			printf("I am parent %d\n", getpid());
			pid_c = wait(NULL);	//wait是一个阻塞函数,等待回收子进程资源,如果没有子进程,wait返回-1
			printf("wait for child %d\n", pid_c);
			sleep(1);
		}
	}
	else if(pid ==0){
		//in child
			printf("I am child %d\n", getpid());
			sleep(10);
	}
	else{
		perror("fork");
		exit(1);
	}

	return 0;
}
