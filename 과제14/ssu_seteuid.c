#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
	int fd, state;

	state = seteuid(1000);  //euid를 1000으로 설정하고 반환값을 state변수에 저장합니다.

	if(state < 0) {  //seteuid가 에러가 나서state가 0보다 작을 경우 예외 처리를 합니다.
		fprintf(stderr, "seteuid error\n");
		exit(1);
	}

	if (( fd = open ("ssu_test.txt", O_CREAT|O_RDWR, S_IRWXU)) < 0) {  //ssu_test.txt 이름으로 파일을 만듭니다.
		fprintf(stderr,"open error\n");
		exit(1);
	}
	close(fd);
	exit(0);
}
