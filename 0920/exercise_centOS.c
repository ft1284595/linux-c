#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
/*
 * 编写监控/home/usr/目录下文件创建与更改的守护进程,日志文件放在/home/usr/filechangelog中
 */

struct {
	char fileName[512];
	char modifyTime[256];
} FILEITEM;

typedef struct FILEITEM fileItem;

void listDir(char path[1024])
{
	extern int errno;
	DIR *dir;
	struct dirent *dp; 
	struct stat sb;
	
	
	if(dir = opendir(path))
	{
		errno = 0;
		while(dp = readdir(dir)){
			//if((strcmp(".", dp->d_name) == 0) || (strcmp("..", dp->d_name) == 0)){
			if(!strcmp(".", dp->d_name) || !strcmp("..", dp->d_name)){
				continue;
			}
			//if(strcmp(".git", dp->d_name) == 0){
				//printf("^^^^^^^^^^.git\n");
				char catPath[1024] = {0};
				strcat(catPath, path);
				strcat(catPath, "/");
				strcat(catPath, dp->d_name);
		
				//printf("strlen(catPath)=%ld\n", strlen(catPath));
				//printf("catPath=%s\n", catPath);

				if(stat(catPath, &sb) != 0){
					perror("stat");
					exit(-3);
				}
			//}
			if(S_ISDIR(sb.st_mode))
			{
				printf("%s-----d\n", catPath);
			}else{
				printf("%s\n", dp->d_name);
			}
			
		}
		if(dp == NULL)
		{
			if(errno != 0){
				printf("errno=%d\n", errno);
				perror("readdir");	
				exit(-1);
			}
		}
		
		
	}else{
		perror("opendir");
		exit(-2);
	}
	closedir(dir);
}

void main(void)
{
	listDir("/home/zx/study/linux-c");
	printf("*****************main()\n");		
}
