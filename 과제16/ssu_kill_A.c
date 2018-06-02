#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {  //인자가 2개가 아닐경우 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr, "usage: %s [Process ID]\n",argv[0]);
		exit(1);
	}
	else
		kill(atoi(argv[1]), SIGKILL);  //1번째 인자의 ID에  SIGKILL 시그널을 보냅니다.
	exit(0);
}
