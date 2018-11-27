#include <stdio.h>

int main(void)
{
	int a = 0;
	char *str = "hello";
	//*str = 'H';			//段错误, 11, SIGSEGV
	
	//printf("%d\n", 3/a);//浮点数例外, 8 ：SIGFPE

	while(1);
	return 0;
}
