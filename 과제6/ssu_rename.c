#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
	struct timeval start,end;
	double op_time;
	int fd;

	gettimeofday(&start,NULL);
	if(argc != 3) {  //입력받은 인자의 개수가 3개가 아니면 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr, "Usage: %s <oldname> <newname>\n",argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) < 0 ) {  //argv[1]의 이름의 파일을 열어옵니다.
		fprintf(stderr,"first open error for %s\n",argv[1]);  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}
	else
		close(fd);
	if(rename(argv[1],argv[2]) <0) {  //argv[1]의 파일을 argv[2]의 이름으로 변경합니다.
		fprintf(stderr,"rename error\n");
		exit(1);
	}
	if((fd = open(argv[1],O_RDONLY)) < 0)  //argv[1]의 파일을 열어옵니다.
		printf("second open error for %s\n", argv[1]);
	else {
		fprintf(stderr, "it's very strange!\n");
		exit(1);
	}

	if(( fd = open(argv[2], O_RDONLY)) < 0) {  //argv[2]의 파일을 열어옵니다.
		fprintf(stderr,"third open error for %s\n",argv[2]);
		exit(1);
	}
	printf("Everything is  good!\n");
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
