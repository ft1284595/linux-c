#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void iterateDir(char *path){
	DIR* dir = NULL;
	struct dirent* s_dir = NULL;
	struct stat statbuf;
	int i = 0;
	char cwd[1024];
	char newPath[1024] = {0}; 
	dir = opendir(path);
	if(dir == NULL){
		perror("open dir");
		exit(-1);
	}
	chdir(path);
	errno = 0;
	while((s_dir = readdir(dir)) != NULL ){
		/*
		printf("%s\n", getcwd(cwd, sizeof(cwd)));	
		printf("%s\n",s_dir->d_name);			
		*/
		if((strcmp(s_dir->d_name, ".") == 0) || (strcmp(s_dir->d_name, "..") == 0))
		{
			continue;
		}
		i = stat(s_dir->d_name, &statbuf);
		if(i == -1)
		{
			printf("^^^^^%s\n", s_dir->d_name);
			perror("dirwalk");
			errno = 0;
			continue;
		}
		
		//printf("i=%d\n", i);
		//printf("errno=%d\n", errno);
		if((statbuf.st_mode & S_IFMT) == S_IFDIR){
			printf("*******************dir %s\n", s_dir->d_name);
			printf("----st_mode=%x\n", statbuf.st_mode);
			sprintf(newPath, "%s/%s", path,s_dir->d_name);
			iterateDir(newPath);
		}else{
			printf("%s\n",s_dir->d_name);			
		}
	}
	closedir(dir);
}
int main(int argc, char *argv[])
{
	char path[1024] = "/home/zx/study/linux-c";
	
	iterateDir(path);

	return 0;
}
