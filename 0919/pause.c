#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int mysleep(int n)
{
	signal(SIGALRM, do_sig);
	alarm(n);
	pause();
}

void do_sig(int n)
{

}

int main(void)
{
	struct sigaction act;

	//act.sa_handler = do_sig;
	//act.sa_handler = SIG_IGN;
	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGUSR1, &act, NULL);

	pause();
	printf("hello world\n");

	return 0;
}
