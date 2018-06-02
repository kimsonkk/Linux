#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	char c;
	int fd;

	if (( fd = open("ssu_test.txt",O_RDONLY)) < 0) {  //ssu_text.tet을 읽기 모드로 읽고 제대로 동작하지 않으면 예외 처리를 합니다
			fprintf(stderr, "open error for %s\n","ssu_test.txt");
			exit(1);
	}

	while(1) {
		if(read(fd,&c,1) > 0)  /*read함수를 사용해 file의 끝을 읽거나 제대로 동작하지
								 않을때까지 file에서 한 글자 씩 읽어 출력합니다*/
			putchar(c);
		else
			break;
	}

	exit(0);
}
