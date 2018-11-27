#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void printsigset(const sigset_t *set)
{
	int i;
	for(i=1; i<32; i++)
	{
		if(sigismember(set, i) == 1)
			putchar('1');
		else
			putchar('0');
	}
	puts("");
}

int main(void)
{
	int i = 0;
	sigset_t s, p;
	sigemptyset(&s);
	sigaddset(&s, SIGINT);
	sigaddset(&s, SIGQUIT);
	sigprocmask(SIG_BLOCK, &s, NULL);
	while(1){
		sigpending(&p);
		printsigset(&p);
		if(i = 10){
			sigdelset(&s, SIGQUIT);
			sigprocmask(SIG_UNBLOCK, &s, NULL);
		}
		sleep(1);
		i++;
	}
	return 0;
}
