#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main() 
{
	struct timeval start,end;
	double op_time;
	char *fname = "ssu_test.txt";
	FILE *fp;

	gettimeofday(&start,NULL);
	if((fp = fopen(fname, "r")) == NULL) {  //fname의 파일을 읽기 모드로 열어옵니다.
		fprintf(stderr,"fopen error for %s\n",fname);  //에러시 예외 처리를 합니다.
		exit(1);
	}
	else {
		printf("Success!\n");
		printf("Opening \"%s\" in \"r\" mode!\n",fname);
	}

	fclose(fp);  //오픈한 파일을 닫습니다.
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
