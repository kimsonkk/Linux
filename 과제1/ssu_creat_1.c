#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	char *fname = "ssu_test.txt";  //만들file의 이름을 저장하는 변수입니다.
	int fd;  //file descripter를 저장할 변수입니다.

	if((fd = creat(fname,0666)) < 0) {  //creat 함수의 반환값이 0보다 작아 제대로 동작하지 않을시 예외처리를 합니다.
		fprintf(stderr,"creat error for %s\n",fname);
		exit(1);  //에러 메세지를 출력하고 종료합니다.
	}
	else {
		printf("Success!\nFilename : %s\nDiscripter : %d\n",fname,fd);  //생성한 file의 이름과 file descripter를 출력합니다.
		close(fd);
	}

	exit(0);
}
