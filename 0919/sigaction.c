#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void do_sig(int num)
{
	int n = 5;
	printf("I am do_sig()\n");
	while(n--){
		printf("num = %d\n", num);
		sleep(1);
	}
	
}
int main(void)
{
	struct sigaction act;

	act.sa_handler = do_sig;
	//act.sa_handler = SIG_IGN;
	//act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = 0;

	sigaction(SIGINT, &act, NULL);

	while(1){
		printf("**************\n");
		sleep(1);
	}

	return 0;
}
