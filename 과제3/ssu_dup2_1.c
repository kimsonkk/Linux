#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() 
{
	char *fname = "ssu_test.txt";
	int fd;  //file descripter를 저장할 변수입니다.

	if(( fd = creat(fname,0666)) < 0) {  //fname의 파일을 생성하고 실패할 경우 예외처리를 하고 종료합니다.
		fprintf(stderr," open error for %s\n",fname);
		exit(1);
	}

	printf("First printf is on the screen.\n");  //표준 출력에 출력한다
	dup2(fd,1);  //fd file descripter를 표준 출력 1번 file descripter로 복사한다.
	printf("Second printf is in this file.\n");  //새로 만든 파일에 출력한다.
	exit(0);
}
