#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
	struct timeval start,end;
	double op_time;
	gettimeofday(&start,NULL);
	if(argc != 3) {  //입력받은 인자가 3개가 아니면 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"Usage: %s <oldname> <newname>\n",argv[0]);
		exit(1);
	}
	if(link(argv[1], argv[2]) <0) {  //argv[2]에 argv[1]의 link를 만들어 줍니다.
		fprintf(stderr,"link error\n");  //에러 메세지를 출력하고 종료한다.
		exit(1);
	}
	else
		printf("step1 passed.\n");
	if(remove(argv[1]) < 0) {  //argv[1]을 삭제합니다.
		fprintf(stderr, "remove error\n");  //에러 메세지를 출력하고 종료합니다
		exit(1);
	}
	else
		printf("step2 passed.\n");
	printf("Success!\n");
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
