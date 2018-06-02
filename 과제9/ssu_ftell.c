#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
	struct timeval start,end;
	char *fname = "ssu_test.txt";
	FILE *fp;
	long fsize;

	gettimeofday(&start,NULL);
	if((fp = fopen(fname,"r")) == NULL) {  //fname의 파일을 읽기 모드로 열어옵니다.
		fprintf(stderr,"fopen error for %s\n", fname);  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	fseek(fp,0,SEEK_END);  //파일의 끝으로 이동합니다.
	fsize = ftell(fp);  //파일포인터의 현재 위치를 저장합니다.
	printf("The size of <%s> is %ld bytes\n",fname,fsize);
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
