#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void do_sig(int num)
{
	int n = 5;
	printf("I am do_sig()\n");
	printf("num = %d\n", num);
	
}
int main(void)
{
	struct sigaction act;

	act.sa_handler = do_sig;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGUSR1, &act, NULL);

	while(1){
		printf("**************\n");
		sleep(1);
	}

	return 0;
}
