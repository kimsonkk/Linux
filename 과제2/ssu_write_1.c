#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main()
{
	char buf[BUFFER_SIZE];
	int length;

	length = read(0, buf, BUFFER_SIZE);  /*표준 입력에서 받아들인 내용을 buf에 BUFFER_SIZE만큼
										   저장하고 저장한 byte를 length에 저장한다*/
	write(1, buf, length);  //buf의 내용을 length만큼 표준 출력에 출력한다.
	exit(0);
}
