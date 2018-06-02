#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024

int main() {
	struct timeval start,end;
	double op_time;
	char buf[BUFFER_SIZE];  //버퍼링에 사용할 배열이다.

	gettimeofday(&start,NULL);
	setbuf(stdout,buf);  //표준 출력에 buf를 이용해서 버퍼링하여 출력한다.
	printf("Hellon, ");
	sleep(1);
	printf("OSLAB!!");
	sleep(1);
	printf("\n");
	sleep(1);

	setbuf(stdout,NULL);  //버퍼링을 이용하지 않고 바로 표준출력으로 출력한다.
	printf("How");
	sleep(1);
	printf(" are");
	sleep(1);
	printf(" you?");
	sleep(1);
	printf("\n");
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
