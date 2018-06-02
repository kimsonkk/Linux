#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024

int main()
{
	struct timeval start,end;
	double op_time;
	gettimeofday(&start,NULL);
	char buf[BUFFER_SIZE];  //출력에 이용할 버퍼를 담을 배열입니다.

	setbuf(stdout,buf);  //표준 출력에 buf를 이용해서 버퍼링해 출력한다.
	printf("Soongsil ");
	sleep(1);
	printf("University!");
	sleep(1);
	printf("\n");
	sleep(1);

	setbuf(stdout,NULL);  //버퍼를 사용하지 않고 표준출력으로 출력한다.
	printf("Computer ");
	sleep(1);
	printf("Science & ");
	sleep(1);
	printf("Engineering");
	sleep(1);
	printf("\n");
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
