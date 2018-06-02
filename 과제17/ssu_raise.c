#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void ssu_signal_handler1(int signo);
void ssu_signal_handler2(int signo);

int main(void)
{
	if (signal(SIGINT, ssu_signal_handler1) == SIG_ERR) {  //SIGINT 시그널을 받으면 ssu_signal_handler1로 보낸다.
		fprintf(stderr,"cannot handle SIGINT\n");  //오류 시 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}
	if( signal(SIGUSR1, ssu_signal_handler2) == SIG_ERR) {  //SIGUSR1 시그널을 받으면 ssu_signaler_handler2로 보낸다.
		fprintf(stderr, "cannot handle SIGUSR1\n");  //오류 시 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	raise(SIGINT);  //자신에게 SIGINT시그널을 보냅니다.
	raise(SIGUSR1);  //자신에게 SIGUSR1 시그널을 보냅니다.
	printf("main return\n");
	exit(0);
}

void ssu_signal_handler1(int signo) {  //SIGINT을 처리하기 위한 핸들러입니다.
	printf("SIGINT 시그널 발생\n");
}
void ssu_signal_handler2(int signo) {  //SIGUSR1을 처리하기 위한 핸들러입니다.
	printf("SIGUSR1 시그널 발생\n");
}
