#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("before system()\n");
	system("pwd");  //pwd명령어를 실행하여 현재의 경로를 출력합니다.
	printf("after system()\n");
	exit(0);
}
