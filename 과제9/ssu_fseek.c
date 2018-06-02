#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
	struct timeval start,end;
	char *fname = "ssu_test.txt";
	FILE *fp;
	long position;
	int character;

	gettimeofday(&start,NULL);
	if((fp = fopen(fname, "r")) == NULL) {  //fname파일을 읽기 모드로 열어옵니다.
		fprintf(stderr,"fopen error for %s\n",fname);  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	printf("Input number >>");
	scanf("%ld",&position);
	fseek(fp,position -1, SEEK_SET);  //position - 1 만큼 처음에서 이동합니다.
	character = getc(fp);  //fp에서 한 글자를 읽어옵니다.
	printf("%ldth character => %c\n",position ,character);
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
