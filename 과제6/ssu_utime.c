#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>
#include <sys/time.h>

int main(int argc,char* argv[])
{
	struct timeval end,start;
	double op_time;
	struct utimbuf time_buf;  //utimebuf 구조체를 저장할 변수입니다.
	struct stat statbuf;  //stat 구조체를 저장할 변수입니다.
	int fd;  //파일 디스크립터를 저장할 변수입니다.
	int i;

	gettimeofday(&start,NULL);
	for(i = 1; i < argc; i++) { 
		if(stat(argv[i], &statbuf) < 0) {  //argv[i]의 stat 구조체를 가져옵니다.
			fprintf(stderr, "stat error for %s\n", argv[i]);  //실패할 경우 에러 메세지를 출력하고 다음으로 넘어갑니다.
			continue;
		}

		if((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {  //argv[i]의 파일을 열어옵니다.
			fprintf(stderr,"open error for %s\n",argv[i]);  //실패할 경우 에러 메세지를 출력하고 다음으로 넘어갑니다.
			continue;
		}
		close(fd);
		time_buf.actime = statbuf.st_atime;  //stat 구조체의 접근 시간을 utimabuf의 접근 시간에 저장합니다.
		time_buf.modtime = statbuf.st_mtime;  //stat 구조체의 수정 시간을 utimebuf의 수정 시간에 저장합니다.

		if(utime(argv[i], &time_buf) < 0) {  //argv[i] 파일의 수정 , 접근 시간을 open전으로 저장합니다.
			fprintf(stderr,"utime error for %s\n",argv[i]);
			continue;
		}
	}
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
