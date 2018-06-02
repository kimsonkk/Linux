#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024

void ssu_setbuf(FILE *fp, char *buf);  //setvbuf 함수를 이용해 구현한 함수이다.

int main()
{
	struct timeval start,end;
	double op_time;
	char buf[BUFFER_SIZE];
	char *fname = "/dev/pts/4";
	FILE *fp;

	gettimeofday(&start,NULL);
	if((fp = fopen(fname,"w")) == NULL) {  //fname의 파일을 쓰기 모드로 열어온다.
		fprintf(stderr,"fopen error for %s",fname);
		exit(1);
	}

	ssu_setbuf(fp,buf);  //읽어온 FILE포인터와 buf배열로 함수를 동작합니다.
	fprintf(fp,"Hello ");
	sleep(1);
	fprintf(fp,"UNIX!!");
	sleep(1);
	fprintf(fp,"\n");
	sleep(1);
	ssu_setbuf(fp,NULL);
	fprintf(fp,"HOW");
	sleep(1);
	fprintf(fp," ARE");
	sleep(1);
	fprintf(fp," YOU?");
	sleep(1);
	fprintf(fp,"\n");
	sleep(1);
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}

void ssu_setbuf(FILE *fp, char* buf) {
	size_t size;  //buf의 사이즈를 저장할 변수입니다.
	int fd;
	int mode;

	fd = fileno(fp);  //FILE 포인터가 가리키는 파일의 디스크립터를 가져옵니다.
	if(isatty(fd))   //tty명령어를 통해 터미널의 번호를 확인합니다.
		mode = _IOLBF;
	else
		mode = _IOFBF;

	if(buf == NULL) {
		mode = _IONBF;
		size = 0;
	}
	else
		size = BUFFER_SIZE;

	setvbuf(fp,buf,mode,size);  //fp에 buf를 사용해 버퍼를 설정합니다.
}
