#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024

int main()
{
	struct timeval start,end;
	char buf[BUFFER_SIZE];

	gettimeofday(&start,NULL);
	while(fgets(buf,BUFFER_SIZE,stdin) != NULL)  //표준 입력에서 한 문장을 읽어옵니다.
		if (fputs(buf,stdout) == EOF) {  //읽어온 문장을 표준 출력에 출력합니다. EOF일 경우 에러 메세지를 출력하고 종료합니다.
			fprintf(stderr,"standard output error\n");
				exit(1);
		}

	if(ferror(stdin)) {  //표준 입력에서 에러가 났는지 검사합니다.
		fprintf(stderr,"standard input error\n");
		exit(1);
	}
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
