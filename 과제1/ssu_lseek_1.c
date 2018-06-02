#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
	char *fname = "ssu_test.txt";  //file의 이름을 저장합니다.
	off_t fsize;  //file의 오프셋을 저장할 변수입니다.
	int fd;  //file descripter를 저장할 변수입니다.

	if((fd = open(fname,O_RDONLY)) < 0) {  //file을 읽기 모드로 open함수를 사용할 때 제대로 동작하지 않는 경우 예외 처리입니다.
		fprintf(stderr,"open error for %s\n",fname);
		exit(1);  //에러 메세지를 출력하고 종료합니다.
	}

	if((fsize = lseek(fd,(off_t)0,SEEK_END)) < 0) {  //lseek함수를 이용해 file의 오프셋을 구할때 제대로 동작하지 않는 경우 예외 처리입니다.
		fprintf(stderr, "lseek error\n");
		exit(1);  //에러 메세지를 출력하고 종료합니다.
	}
	printf("The size of <%s> is %d bytes. \n",fname,fsize);	 //file 이름과 file의 사이즈를 출력합니다.
	exit(0);
}
