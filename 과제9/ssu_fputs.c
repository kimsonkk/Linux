#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
	struct timeval start,end;
	char buf[BUFFER_SIZE];
	FILE *fp;

	gettimeofday(&start,NULL);
	if(argc != 2) {  //인자가 2개가 아닌 경우 에러 처리를 합니다.
		fprintf(stderr,"usage: %s <file>\n",argv[0]);
		exit(1);
	}

	if((fp = fopen(argv[1],"w+")) == NULL) {  //확장 읽기 모드로 argv[1]를 열어 옵니다.
		fprintf(stderr,"fopen error for %s\n",argv[1]);  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	fputs("Input String >> ",stdout);
	gets(buf);  //buf에 문장을 읽어옵니다.
	fputs(buf,fp);  //fp에 buf를 출력합니다.
	rewind(fp);  //fp의 위치를 처음으로 돌립니다.
	fgets(buf,sizeof(buf),fp);  //fp에서 buf 사이즈만큼 읽어옵니다.
	puts(buf);  //표준 출력에 buf를 출력합니다.
	fclose(fp);
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
