#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NLOOP 5000
int counter;	/* incremented by threads */

//1.锁是全局变量,可以静态初始化
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *doit(void *);

int main(int argc, char *argv[])
{
	/*
	pthread_mutex_t mutex;
	//2.锁是函数内定义的,可以动态初始化
	pthread_mutex_init(&mutex, NULL);
	 */
	pthread_t tidA, tidB;

	pthread_create(&tidA, NULL, &doit, NULL);
	pthread_create(&tidB, NULL, &doit, NULL);

	/* wait for both threads to terminate */
	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);

	return 0;
}

void *doit(void *vptr)
{
	int		i, val;
		//临界区,锁住的范围
	for(i=0; i<NLOOP; i++){
		//谁要操作全局资源counter谁哪所,锁只有一把
		//拿锁
		pthread_mutex_lock(&counter_mutex);
		val = counter;
		printf("%x: %d\n", (unsigned int)pthread_self(),val + 1);
		counter = val + 1;
		//解锁
		pthread_mutex_unlock(&counter_mutex);
	}

	return NULL;
}
