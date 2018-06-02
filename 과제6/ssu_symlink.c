#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
	struct timeval start,end;
	double op_time;

	gettimeofday(&start,NULL);
	if (argc != 3) {  //입력받은 인자가 3개가 아닐 경우 사용법을 출력하고 종료합니다.
		fprintf(stderr, "Usage: %s <actualname> <symname>\n",argv[0]);
		exit(1);
	}

	if(symlink(argv[1], argv[2]) < 0) {  //argc[1]의 파일을 argv[2]라는 이름의 심볼릭 링크 파일을 생성한다.
		fprintf(stderr,"symlink error\n");
		exit(1);
	}
	else 
		printf("symlink: %s -> %s\n",argv[2], argv[1]);
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - end.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
