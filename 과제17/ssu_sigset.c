#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(void) 
{
	sigset_t set;  //시그널 집합 set을 선언합니다.
	sigemptyset(&set);  //set을 빈 집합으로 초기화한다.
	sigaddset(&set, SIGINT);  //set에 SIGINT 시그널을 추가한다.

	switch(sigismember(&set, SIGINT))  //set에 SIGINT가 있는지 검사한다.
	{
		case 1 :  //SIGINT가 set에 있는 경우입니다.
			printf("SIGINT is included.\n");
			break;
		case 0 :  //SIGINT가 set에 없는 경우입니다.
			printf("SIGINT is not included.\n");
			break;
		default :  //sigismember()에 에러가 난 경우입니다.
			printf("failed to call sigismember() \n");
	}

	switch(sigismember(&set, SIGSYS))  //set에 SIGSYS가 있는지 검사한다.
	{
		case 1 :  //SIGSYS가 set에 있는 경우입니다.
			printf("SIGSYS is included.\n");
			break;
		case 0 :  //SIGSYS가 set에 없는 경우입니다.
			printf("SIGSYS is not included.\n");
			break;
		default :  //setismember()에 에러가 난 경우입니다.
			printf("failed to call sigismember()\n");
	}
	exit(0);
}
