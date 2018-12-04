#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
//编译时 gcc pthread.c -lpthread -o pthread
void *th_fun(void *arg)
{
	int *p = (int *)arg;
	int i = 0;
	printf("thread PID = %d\n", getpid());
	printf("thread ID = %x\n", (unsigned int)pthread_self());
	printf("thread *arg = %d\n", *p);
	while(1){
		i++;
		pthread_testcancel();
	}
	
	return NULL;
}

//执行起来, ps -eLf 和 ps -Lw pid
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
	pthread_cancel(tid);
	while(1)
		sleep(1);

	return 0;
}
