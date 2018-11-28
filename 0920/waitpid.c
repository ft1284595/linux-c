#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void do_sig_child(int signo)
{
	/*
	while(!(waitpid(0, NULL, WNOHANG) == -1))
		;
	*/
	int status;
	pid_t pid;

	while( (pid = waitpid(0, &status, WNOHANG)) > 0){
		if(WIFEXITED(status))
			printf("child %d exit %d\n", pid, WEXITSTATUS(status));
		else if(WIFSIGNALED(status))
			printf("child %d cancel signal %d\n", pid, WTERMSIG(status));
	}
}

void sys_err(char *str)
{
	perror(str);
	exit(1);
}

int main(void)
{
	pid_t pid;
	int i;
	//阻塞SIGCHLD信号
	for(i=0; i<10; i++)
	{
		if((pid = fork()) == 0)
			break;
		else if(pid < 0)
			sys_err("fork");
			
	}

	if(pid == 0){
		int n = 18;
		while(n--){
			printf("child ID %d\n", getpid());
			sleep(1);
		}
		return i;
	}
	else if(pid > 0)
	{
		//先设置捕捉函数
		//在解除对SIGCHLD的阻塞
		struct sigaction act;
		act.sa_handler = do_sig_child;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;
		sigaction(SIGCHLD, &act, NULL);
		while(1){
			printf("parent ID %d\n", getpid());
			sleep(1);
		}

	}

	return 0;
}
