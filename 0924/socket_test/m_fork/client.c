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
	int confd, len;
	char ipstr[] = "10.0.1.24";
	char buf[MAXLINE];

	//1.创建一个socket
	confd = socket(AF_INET, SOCK_STREAM, 0);
	//2.初始化服务器地址
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	//"10.0.1.24"
	inet_pton(AF_INET, ipstr, &serveraddr.sin_addr.s_addr);
	serveraddr.sin_port = htons(SERVER_PORT);
	//3. 连接服务器 
	connect(confd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

	while(fgets(buf, sizeof(buf), stdin)){
		//4.请求服务器处理数据
		write(confd, buf, strlen(buf));
		len = read(confd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, len);
	}
	//5. 关闭socket
	close(confd);

	return 0;
}
