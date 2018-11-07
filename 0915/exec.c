#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *argvv[] = {"ls", "-l", NULL};
	printf("hello\n");
	//execl("/bin/ls", "ls", "-l", NULL);
	//execlp("ls", "ls", "-l", NULL);
	//execv("/bin/ls", argvv);
	//execvp("ls", argvv);
	execlp("app", "../app", "11", "aa", NULL);
	//execl("/home/zx/study/linux-c/0915/test", "./test", "11", "aaa", NULL);
	printf("world\n");
	return 0;
}
