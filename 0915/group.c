#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	int n = 3;
	while(n--){
		pid = fork();
		if(pid == 0)
			break;
	}
	if(pid == 0){
		while(1){
			printf("I am child %d\n", getpid());
			sleep(3);
		}
	}
	else if(pid > 0){
		pid_t pid_c;
		while(1){
			pid_c = wait(NULL);
			if(pid_c == -1)
				break;
			else
				printf("wait for child %d\n", pid_c);
		}
	}

	return 0;
}
