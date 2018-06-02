#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main()
{
	char buf[BUFFER_SIZE];  //파일의 내용을 저장하는 배열입니다.
	char *fname = "ssu_test.txt";
	int fd;  //file descripter를 저장할 변수입니다.
	int length;

	if((fd = open(fname,O_RDONLY)) < 0) {  //fname 이름의 file을 열고 실패할 경우 예외처리를 하고 종료합니다.
		fprintf(stderr,"open error for %s\n",fname);
		exit(1);
	}

	if(dup2(1,4) != 4) {  //표준 출력에 4번 file descripter를 부여하고 실패시 예외 처리를 합니다
		fprintf(stderr,"dup2 call failed\n");
		exit(1);
	}

	while(1) {
		length = read(fd , buf, BUFFER_SIZE);  //fd에서 BUFFER_SIZE만큼 읽어 buf에 저장하고 읽은 byte를 length에 저장합니다
		if( length <= 0)  //읽은 byte가 없을 경우 반복문을 빠져 나갑니다.
			break;

		write(4, buf, length);  //표준 출력에 buf의 내용을 length만큼 출력합니다.
	}
	exit(0);
}
