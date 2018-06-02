#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
	struct timeval start,end;
	double op_time;
	char* fname = "ssu_test.txt";
	char *mode = "r";

	gettimeofday(&start,NULL);
	if(fopen(fname,mode) == NULL) {  //fopen으로 파일을 읽기 모드로 오픈합니다.
		fprintf(stderr,"fopen erro for %s\n",fname);  //에러 시 예외 처리를 합니다.
		exit(1);
	}
	else
		printf("Success!\nFilename: <%s>, mode: <%s>\n",fname,mode);
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);

	exit(0);
}
