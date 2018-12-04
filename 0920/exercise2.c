#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
/*
 * 编写监控/home/usr/目录下文件创建与更改的守护进程,日志文件放在/home/usr/filechangelog中
 */

struct fileItem{
	char fileName[512];
	char modifyTime[256];
	time_t mTime;
} fileArray[8192];

int arr_index = 0;


//typedef struct FILEITEM FileItem;

void sys_err(char *str, int exitNum)
{
	perror(str);
	exit(exitNum);
}

void daemonize(void)
{
	pid_t pid;
	pid_t pid_s;
	if((pid = fork()) < 0){
		sys_err("fork", 1);
	}else if(pid > 0){
		exit(0);
	}
	pid_s = setsid();
	if(pid_s < 0){
		sys_err("setsid", 2);
	}
	if(chdir("/") < 0){
		sys_err("chdir", 3);
	}
	umask(0);
	if(close(0) != 0){
		sys_err("close", 4);
	}
	if(open("/dev/null", O_RDWR) < 0){
		sys_err("open", 5);
	}
	if(dup2(0, 1) == -1){
		sys_err("dup2", 6);
	}
	if(dup2(0, 2) == -1){
		sys_err("dup2", 6);
	}
}

/*
 * check whether the filename is already exist in the fileArray,
 * if exists, return the index of the fileArray
 * else return 0
 */ 
int alreadExist(char *name)
{
	int i;
	for(i=0; i<arr_index; i++)
	{
		if(strcmp(name, fileArray[i].fileName) == 0){
			return i;
		}
	}
	return -1;
}

void printFileItem()
{
	int i;
	for(i=0; i< arr_index; i++)
	{
		printf("%s----%s\n", fileArray[i].fileName, ctime(&fileArray[i].mTime));
	}
}

void monitorDir(char path[1024], struct fileItem fileArray[], int index, int fd)
{
	extern int errno;
	DIR *dir;
	struct dirent *dp; 
	struct stat sb;
	char tmpStr[1024] = {0};
	
	
	if((dir = opendir(path)))
	{
		errno = 0;
		while((dp = readdir(dir))){
			//if((strcmp(".", dp->d_name) == 0) || (strcmp("..", dp->d_name) == 0)){
			if(!strcmp(".", dp->d_name) || !strcmp("..", dp->d_name)){
				continue;
			}
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
			if(S_ISDIR(sb.st_mode))
			{
				//printf("%s-----d\n", catPath);
				monitorDir(catPath, fileArray, arr_index, fd);
			}else{
				//printf("%s\n", dp->d_name);
				//printf("st_mtime=%ld\n", sb.st_mtime);	
				//printf("%s---->%s\n", catPath, ctime(&sb.st_mtime));
				int exist_index = alreadExist(catPath);
				if(exist_index == -1){
					strcpy(fileArray[arr_index].fileName,catPath);
					fileArray[arr_index].mTime = sb.st_mtime;
					strcpy(fileArray[arr_index].modifyTime, ctime(&sb.st_mtime));

					sprintf(tmpStr, "create file %s at %s", fileArray[arr_index].fileName, fileArray[arr_index].modifyTime);
					//printf("%s\n", tmpStr);
					if(write(fd, tmpStr, strlen(tmpStr)) == -1){
						perror("write to file");
						exit(-5);
					}
					arr_index ++;
				}else{
					if(fileArray[exist_index].mTime != sb.st_mtime){
						fileArray[exist_index].mTime = sb.st_mtime;
						strcpy(fileArray[exist_index].modifyTime, ctime(&sb.st_mtime));
						sprintf(tmpStr, "modify file %s at %s", fileArray[exist_index].fileName, fileArray[exist_index].modifyTime);
						//printf("%s\n", tmpStr);
						if(write(fd, tmpStr, strlen(tmpStr)) == -1){
							perror("write to file");
							exit(-5);
						}
					}

				}
				
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

int main(void)
{
	int fd;

	daemonize();

	fd = open("/tmp/zhangxin-monitorDir.txt", O_CREAT|O_APPEND|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	if(fd == -1){
		perror("open file");
		exit(-4);
	}
	while(1){
		monitorDir("/home/zx/study/linux-c", fileArray, 0, fd);
		sleep(3);
	}
	printf("*****************main()\n");		
	//printFileItem();

	close(fd);

	return 0;
}
