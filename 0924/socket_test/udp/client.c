#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

#define SERVER_PORT 8000
#define MAXLINE 4096

int main(int argc, char *argv[])
{
	struct sockaddr_in serveraddr;
	int confd;
	ssize_t len;
	char ipstr[] = "10.0.1.24";
	char buf[MAXLINE];

	if(argc < 2){
		printf("./client str\n");
		exit(1);
	}

	//1.创建一个socket
	confd = socket(AF_INET, SOCK_DGRAM, 0);
	//2.初始化服务器地址
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	//"10.0.1.24"
	inet_pton(AF_INET, ipstr, &serveraddr.sin_addr.s_addr);
	serveraddr.sin_port = htons(SERVER_PORT);

	//3.向服务器发送数据
	sendto(confd, argv[1], strlen(argv[1]),0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	len = recvfrom(confd, buf, sizeof(buf), 0, NULL, 0);
	write(STDOUT_FILENO, buf, len);

	//5. 关闭socket
	close(confd);

	return 0;
}
