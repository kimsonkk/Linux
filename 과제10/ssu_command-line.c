#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main( int argc, char* argv[])
{
	struct timeval start,end;
	int i;

	gettimeofday(&start,NULL);
	for ( i = 0; i < argc; i++)
		printf("argv[%d] : %s\n",i,argv[i]);  //명령어 인자들을 출력합니다.
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
