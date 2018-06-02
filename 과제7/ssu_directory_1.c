#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#define DIRECTORY_SIZE MAXNAMLEN

int main(int argc, char* argv[])
{
	struct timeval start,end;
	struct dirent *dentry;
	struct stat statbuf;  //파일의 정보를 저장할 구조체입니다.
	char filename[DIRECTORY_SIZE +1];  //파일의 이름을 저장할 배열입니다.
	DIR *dirp;  //opendir을 이용해 가져온 디렉터리의 DIR구조체를 저장할 구조체입니다.
	double op_time;

	gettimeofday(&start,NULL);
	if( argc < 2) {  //인자가 2이 미만이면 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"Usage : %s <directory> \n", argv[0]);
		exit(1);
	}

	if((dirp = opendir(argv[1])) ==NULL || chdir(argv[1]) == -1) {  /*디렉터리의 DIR구조체를 얻는게 실패하거나 
																	  작업 디렉터리를 변경하는게 실패하면 에러 
																	  메세지를 출력하고 종료합니다.*/
		fprintf(stderr,"opendir, chdir error for %s\n",argv[1]);
		exit(1);
	}

	while((dentry = readdir(dirp)) != NULL) {  //디렉터리가 끝날 때까지 읽어옵니다.
			if(dentry->d_ino == 0)  //inode가 0이면 다음 파일로 넘어갑니다.
				continue;
			memcpy(filename, dentry->d_name,DIRECTORY_SIZE);  //파일의 이름을 filename에 DIRECTORY_SIZE만큼 복사합니다.
			if(stat(filename,&statbuf) == -1) {  //filename의 stat구조체를 읽어옵니다.
				fprintf(stderr,"stat error for %s\n",filename);  //실패할 경우 에러 메세지를 출력하고 종료합니다.
				break;
			}
			if((statbuf.st_mode & S_IFMT) == S_IFREG)
				printf("%-14s %ld\n",filename, statbuf.st_size);  //filename이 Regular일경우 그 사이즈와 같이 이름을 출력합니다.
			else
				printf("%-14s\n",filename);  //그 외에는 파일 이름만 출력합니다.
	}

	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n", op_time);
	exit(0);
}
