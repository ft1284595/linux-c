#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	while(i < argc)
		printf("%s\n", argv[i++]);

	return 8;
}
