#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define PATH_MAX 1024

int main()
{
	struct timeval start,end;
	double op_time;
	char* pathname;

	gettimeofday(&start,NULL);
	if(chdir("/home/kimchangyeop/리시프/과제7") < 0) {  //작업 디렉터리를 변경해줍니다.
		fprintf(stderr,"shdir error\n");  //실패할 경우 에러메세지를 출력하고 종료합니다.
		exit(1);
	}
	pathname = malloc(PATH_MAX);

	if(getcwd(pathname, PATH_MAX) == NULL) {  //현재 작업 디렉터리에 대한 전체 경로 명을 받아옵니다.
		fprintf(stderr,"getcwd error\n");  //실패할 경우 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	printf("current directory = %s\n",pathname);  //현재의 경로를 출력합니다.
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
