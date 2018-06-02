#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define RW_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main() 
{
	char *fname1 = "ssu_file1";
	char *fname2 = "ssu_file2";

	umask(0);  //mask의 값을 0으로 설정합니다.

	if(creat(fname1, RW_MODE) < 0) {  //fanme1 이름의 0666mode 파일을 생성합니다.
		fprintf(stderr,"creat error for %s\n", fname1);  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);  //mask의 값을 0066으로 설정합니다.

	if(creat(fname2, RW_MODE) < 0) {  //fname2 이름의 0666mode 파일을 생성합니다.
		fprintf(stderr,"creat error for %s\n",fname2);  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}
	exit(0);
}
