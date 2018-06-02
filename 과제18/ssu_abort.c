#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("abort terminate this program\n");
	abort();  //abort함수를 이용해 프로세스를 비정상 종료합니다.
	printf("this line is never reached\n");
	exit(0);
}
