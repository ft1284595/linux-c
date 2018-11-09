#include <stdio.h>

int main(int argc, char *argv[])
{
	char *str = "hello";
	printf("%s\n", str);
	*str = 'H';
	printf("%s\n", str);
	return 8;
}
