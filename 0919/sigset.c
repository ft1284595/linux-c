#include <stdio.h>
#include <signal.h>

int main(void)
{
	printf("sizeof(sigset_t) = %ld\n", sizeof(sigset_t));
	return 0;
}
