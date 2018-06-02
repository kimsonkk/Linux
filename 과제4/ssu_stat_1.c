#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main( int argc, char* argv[])
{
	struct stat statbuf;  //stat 구조체를 저장할 변수입니다.

	if(argc != 2) {  //인자로 받은 명령어의 개수가 2개가 아니면 예외처리를 하고 종료합니다.
		fprintf(stderr, "usage : %s <file>\n",argv[0]);
		exit(1);
	}

	if((stat(argv[1], &statbuf)) < 0) {  //입력받은 file의 stat구조체를 가져올 때 에러 시 예외처리를 하고 종료합니다.
		fprintf(stderr, "stat error\n");
		exit(1);
	}

	printf("%s is %ld bytes\n", argv[1], statbuf.st_size);  //가져온 file의 이름과 stat구조체의 byte단위 크기를 출력합니다.
	exit(0);
}
