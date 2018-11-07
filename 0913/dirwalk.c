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
	//printf("iterateDir path=%s\n", path);
	dir = opendir(path);
	if(dir == NULL){
		perror("open dir");
		exit(-1);
	}
	while((s_dir = readdir(dir)) != NULL ){
		/*
		printf("%s\n", getcwd(cwd, sizeof(cwd)));	
		printf("%s\n",s_dir->d_name);			
		*/
		//printf("^^^^^%s\n", s_dir->d_name);
		//printf("------%s\n", getcwd(cwd, sizeof(cwd)));
		if((strcmp(s_dir->d_name, ".") == 0) || (strcmp(s_dir->d_name, "..") == 0))
		{
			continue;
		}
		sprintf(newPath, "%s/%s", path,s_dir->d_name);
		i = stat(newPath, &statbuf);
		if(i == -1)
		{
			perror("dirwalk");
			errno = 0;
			continue;
		}
		
		//printf("i=%d\n", i);
		//printf("errno=%d\n", errno);
		if((statbuf.st_mode & S_IFMT) == S_IFDIR){
			//printf("*******************dir %s\n", s_dir->d_name);
			//printf("----st_mode=%x\n", statbuf.st_mode);
			//sprintf(newPath, "%s/%s", path,s_dir->d_name);
			//printf("++++++newPath=%s", newPath);
			iterateDir(newPath);
		}else{
			//printf("%s\n",s_dir->d_name);			
			printf("%s\n", newPath);
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
