#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
	char character;
	int fd;
	int line_count=0;  //읽어온 file의 줄을 수를 셈하기 위한 변수입니다

	if((fd = open("ssu_test.txt",O_RDONLY)) < 0) {  //ssu_test.txt file을 읽기 모드로 open하고 예외처리를 합니다
		fprintf(stderr,"open error for %s\n", "ssu_test.txt");
		exit(1);
	}

	while(1) {
		if(read(fd,&character,1) > 0) {  //file의 끝이나 에러가 나지 않을 때까지 1 byte씩 읽어옵니다
			if(character == '\n')
				line_count++;  //한 줄을 읽을 때마다 하나씩 증가합니다
		}
		else
			break;
	}

	printf("Total line : %d\n",line_count);
	exit(0);
}
