#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char* argv[])
{
	int i;

	if(argc < 2) {  //인자로 받은 명령어의 개수가 2개보다 작을 시 예외처리를 하고 종료합니다.
		fprintf(stderr, "usage : %s <file1> <file2>  ... <fileN>\n", argv[0]);
		exit(1);
	}

	for( i = 1; i < argc; i++) {  //인자로 받은 file의 개수만큼 반복합니다.
		if(access(argv[i], F_OK) < 0) { //file이 존재하지 않을 경우 예외처리를 하고 종료합니다.
			fprintf(stderr, "%s doesn't exist. \n", argv[i]);
			continue;
		}

		if(access(argv[i], R_OK) == 0)  //file의 읽기 권한이 있을 경우 출력합니다.
			printf("User can read %s\n", argv[i]);
		if(access(argv[i], W_OK) == 0)  //file의 쓰기 권한이 있을 경우 출력합니다.
			printf("User can write %s\n", argv[i]);
		if(access(argv[i], X_OK) == 0)  //file의 실행 권한이 있을 경우 출력합니다.
			printf("User can execute %s\n",argv[i]);
	}
	exit(0);
}
