#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024

int main()
{
	struct timeval start,end;
	double op_time;
	char buf[BUFFER_SIZE];  //버퍼링에 이용할 배열입니다.
	int a,b;
	int i;

	gettimeofday(&start,NULL);
	setbuf(stdin,buf);  //표준 입력에서 입력받은 글자들을 buf 배열에 저장합니다.
	scanf("%d %d", &a,&b);

	for(i = 0; buf[i] != '\n'; i++)  //표준 입력을 통해 입력받은 글자를 출력합니다
		putchar(buf[i]);

	putchar('\n');
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
