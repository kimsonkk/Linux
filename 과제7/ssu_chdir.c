#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
	struct timeval start,end;
	double op_time;

	gettimeofday(&start,NULL);
	if(chdir("/etc") < 0) {  //작업 디렉터리를 변경해준다.
		fprintf(stderr,"chdir error\n");  //실패할 경우 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	printf("chdir to /etc succeeded.\n");
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
