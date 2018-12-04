#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void *th_fun(void *arg)
{
	int *p = (int *)arg;
	printf("thread PID = %d\n", getpid());
	printf("thread ID = %x\n", (unsigned int)pthread_self());
	printf("thread *arg = %d\n", *p);
	sleep(1);
	
	return NULL;
}

int main(void)
{
	pthread_t tid;
	int n = 10;

	pthread_create(&tid,NULL, th_fun, (void *)&n);// 1.创建线程 2.线程号填写到tid 3.返回函数调用
	//主线程里的pthread_create 返回值tid == 子线程里pthread_self()的返回值 ??
	//不一定
	printf("main thread ID = %x\n", (unsigned int)pthread_self());
	printf("main child thread ID = %x\n", (unsigned int)tid);
	printf("main PID = %d\n", getpid());
	sleep(2);

	return 0;
}
