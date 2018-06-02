#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main ()
{
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt";
	int count;
	int fd1,fd2;

	fd1 = open(fname,O_RDONLY,0644);
	fd2 = open(fname,O_RDONLY,0644);  //같은 file을 open하여 file dexcirpter를 각각 저장합니다

	if(fd1 < 0 || fd2 < 0) {  //둘 중 하나라도 open이 제대로 동작하지 않을 경우 예외 처리를 합니다
		fprintf(stderr,"open error for %s\n",fname);
		exit(1);
	}

	count = read(fd1,buf,25);  //file에서 25byte만큼 읽어 buf에 저장하고 읽은 bytee수 만큼 count에 저장합니다
	buf[count] = 0;
	printf("fd1's first printf : %s\n",buf);  //읽은 내용을 출력합니다
	lseek(fd1,(off_t)1, SEEK_CUR);  //파일의 오프셋을 현재 위치에서 한 칸 뒤로 옮깁니다

	count = read(fd1,buf,24);  //file에서 24byte만큼 읽어 buf에 저장하고 읽은 byte수 만큼 count에 저장합니다
	buf[count] = 0;
	printf("fd1's second printf : %s\n",buf);

	/*
	   file이 open함수를 사용하여 열릴 때마다 각각의 프로세스 별로 다른 file descritper를 받기 때문에
	   아래의 과정은 위와 동일한 결과를 출력합니다
	   */
	count = read(fd2,buf,25);
	buf[count] - 0;
	printf("fd2's first printf : %s\n",buf);

	lseek(fd2,(off_t)1,SEEK_CUR);
	count = read(fd2,buf,24);
	buf[count] = 0;
	printf("fd2's second printf : %s\n",buf);

	exit(0);
}
