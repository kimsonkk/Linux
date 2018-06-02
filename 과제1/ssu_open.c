#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
	char *fname = "ssu_test.txt";  //open함수에 사용될 파일의 이름을 저장합니다.
	int fd; // open한 filedescripter를 저장할 변수입니다.

	if((fd = open(fname,O_RDONLY)) < 0) { //open함수의 반환값이 0보다 작은 예외 경우를 처리합니다.
		fprintf(stderr, "open err for %s\n", fname);
		exit(1);  //에러 메세지를 출력하고 종료합니다.
	}
	else 
		printf("Success!\nFilename : %s\nDescripter : %d\n",fname,fd); //정상적으로 동작될 경우 file 이름과 file descripter를 출력합니다.
	exit(0);
}
