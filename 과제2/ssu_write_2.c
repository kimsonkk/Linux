#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define S_MODE 0644
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char buf[BUFFER_SIZE];
	int fd1,fd2;
	int length;

	if(argc != 3) {  //명령어가 3 글자가 아닐 경우 에러메세지를 출력하고 종료한다.
		fprintf(stderr,"Usage %s filein fileout\n", argv[0]);
		exit(1);
	}

	if(( fd1 = open(argv[1],O_RDONLY)) < 0) {  //실행 파일 뒤에 오는 단어의 file을 읽기 모드로 open하고 제대로 동작하지 않을 경우 예외처리를 한다
		fprintf(stderr,"open error for %s\n", argv[1]);
		exit(1);
	}

	if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_MODE)) < 0) {  //두 번째 단어의 file이 있다면 내용을 지우고 쓰기 모드로 열고 없다면 file을 생성하여 open한다
		fprintf(stderr,"open error for %s\n",argv[2]);
		exit(1);
	}

	while(( length = read(fd1, buf, BUFFER_SIZE)) >0)  //file descripter fd1이 가르키는 file의 내용을 BUFFER_SIZE만큼 읽어 buf에 저장하고 읽은 byte수를 length에 저장한다 
		write(fd2,buf,length);  //file descripter fd2가 가르키는 file에 buf에 저장된 내용을 length 길이만큼 입력한다.
	exit(0);
}
