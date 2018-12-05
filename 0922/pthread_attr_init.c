#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *th_fun(void *arg)
{
	int n = 20;
	while(n--){
		printf("%x    %d\n", (unsigned int)pthread_self(), n);
		sleep(1);
	}
	return (void *)1;
}

int main(void)
{
	pthread_t tid;
	pthread_attr_t attr;	//attr里面是垃圾值
	int err;

	pthread_attr_init(&attr);//attr里面保存创建线程的默认属性

	//int detachstate : PTHREAD_CREATE_DETACHED PTHREAD_CREATE_JOINABLE
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	//设置线程为分离属性

	pthread_create(&tid, &attr, th_fun, NULL);

	err = pthread_join(tid, NULL);
	while(1){
		if(err !=0 ){
			printf("%s\n", strerror(err));
			sleep(10);
			pthread_exit((void *)1);
		}
	}



}
