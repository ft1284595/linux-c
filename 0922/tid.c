#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
 * 思考:pthread_self获得的tid和pthread_create函数里得到的tid是否会出现不一致?
 *
 * 会出现不一致
 *
 */

pthread_t ntid;

void printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int) pid, (unsigned int)tid, (unsigned int)tid);
}

void *thr_fn(void *arg)
{
	printids(arg);
	return NULL;
}

int main(void)
{
	int err;

	err = pthread_create(&ntid, NULL, thr_fn, "new thread: ");
	if(err != 0){
		fprintf(stderr, "can't create thread: %s\n", strerror(err));
		exit(-1);
	}

	printids("main thread:");
	sleep(1);

	return 0;
}
