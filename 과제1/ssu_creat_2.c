#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char *fname = "ssu_test.txt";  //생성할 file의 이름을 저장합니다.
	int fd;  //file descripter를 저장할 변수입니다.

	if((fd = creat(fname,0666)) < 0 ) {  //creat함수의 반환값이 0보다 작아 제대로 동작하지 않은 경우의 예외 처리를 합니다.
		fprintf(stderr, "creat error for %s\n",fname);
		exit(1);  //에러 메세지를 출력하고 종료합니다.
	}
	else {
		close(fd);
		fd = open(fname,O_RDWR); //생성한 file을 닫고 그 file을 혼용 모드로 open함수를 사용합니다.
		printf("Success!\n<%s> is new readable and writable\n", fname);  //file 이름과 결과를 출력합니다.
	}
	exit(0);
}
