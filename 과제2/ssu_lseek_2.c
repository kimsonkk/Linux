#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define CREAT_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)  //입력 모드를 지정해줍니다

char buf1[] = "1234567890";
char buf2[] = "ABCDEFGHIJ";

int main() 
{
	char *fname = "ssu_hole.txt";  //creat함수에 사용될 file의 이름을 저장합니다
	int fd;  //file descripter를 저장할 변수입니다.

	if((fd = creat(fname, CREAT_MODE)) <0) {  //file을 생성하고 제대로 동작하지 않을 경우 예외처리 합니다
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1);  //에러 메세지를 출력하고 종료합니다.
	}

	if(write(fd, buf1, (size_t)12) != 12) {  //file decripter가 가르키는 file에 buf1의 내용을  12byte만큼 기록을 하고 예외처리를 합니다 
		fprintf(stderr, "buf1 write error\n");
		exit(1);  //에러 메세지를 출력하고 종료합니다
	}

	if(lseek(fd, (off_t)15000,SEEK_SET) < 0) {  //생성된 file의 시작부터 15000byte만큼 이동시키고 예외 처리를 합니다
		fprintf(stderr, "lseek error\n");
		exit(1);  //에러 메세지를 출력하고 종료합니다
	}

	if(write(fd,buf2,(size_t)12) != 12) {  //file descripter가 가르키는 file에 buf2의 내용을 12byte만큼 기록을 하고 예외처리를 합니다
		fprintf(stderr,"buf2 write error\n");
		exit(1);  //에러 메세지를 출력하고 종료합니다
	}

	exit(0);
}

