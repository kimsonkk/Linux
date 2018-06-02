#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main() 
{
	char buf[BUFFER_SIZE];  //읽어들인 내용을 저장할 변수입니다.
	char *fname = "ssu_test.txt";
	int count;  //읽은 실제 byte수를 저장할 변수입니다.
	int fd1, fd2;  //file descripter를 저장할 변수입니다.

	if(( fd1 = open(fname,O_RDONLY,0644)) < 0) {  //fname 이름의 파일을 열고 에러시 예외처리를 하고 종료합니다.
		fprintf(stderr,"open error for %s\n",fname);
		exit(1);
	}

	fd2 = dup(fd1);  //fd1의 file descripter를 복사하여 새로운 file descripter를 제공한다.
	count = read(fd1, buf, 12);  //fd1에서 실제로 읽은 byte수를 저장한다
	buf[count] = 0;  //읽은 문장 뒤에 개행을 넣는다
	printf("fd1's printf : %s\n",buf);
	lseek(fd1, (off_t)1, SEEK_CUR);  //파일의 offset을 현재위치에서 1만큼 뒤로 움직인다.
	count = read(fd2, buf, 12);  //fd2에서 실제로 읽은 byte수를 저장한다
	buf[count] = 0;  //읽은 문장 뒤에 개행을 넣는다
	printf("fd2's printf : %s\n",buf);
	exit(0);
}
