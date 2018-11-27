#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
	if(kill(-1, 9) < 0){
		perror("kill");
		exit(-1);
	}

	return 0;
}
