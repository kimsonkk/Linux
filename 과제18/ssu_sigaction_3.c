#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static void ssu_signal_handler1(int signo);
static void ssu_signal_handler2(int signo);

int main(void)
{
	struct sigaction act_int, act_quit;

	act_int.sa_handler = ssu_signal_handler1;  //act_int의 시그널 핸들러를 설정합니다.
	sigemptyset(&act_int.sa_mask);  //act_int의 sa_mask 시그널 집합의 시그널들을 0으로 초기화합니다.
	sigaddset(&act_int.sa_mask, SIGQUIT);  //act_int의 sa_mask에 SIGQUIT를 추가합니다.
	act_quit.sa_flags = 0;

	if(sigaction(SIGINT, &act_int, NULL) < 0) {  //SIGINT 시그널의 액션을 설정합니다.
		fprintf(stderr, "sigaction(SIGINT) error\n");
		exit(1);
	}

	act_quit.sa_handler = ssu_signal_handler2;  //act_quit의 시그널 핸들러를 설정합니다.
	sigemptyset(&act_quit.sa_mask);  //act_quit의 sa_mask 시그널 집합의 시그널들을 0으로 초기화합니다.
	sigaddset(&act_quit.sa_mask, SIGINT);  //act_quit의 sa_mask에 SIGINT추가합니다.
	act_int.sa_flags = 0;

	if(sigaction(SIGQUIT, &act_quit, NULL) < 0) {  //SIGQUIT 시그널의 액션을 설정합니다.
		fprintf(stderr, "sigaction(SIGQUIT) error\n");
		exit(1);
	}

	pause();
	exit(0);
}

static void ssu_signal_handler1(int signo) {
	printf("SIgnal handler of SIGINT : %d\n",signo);
	printf("SIGQUIT signal is blocked : %d\n", signo);
	printf("sleeping 3 sec\n");
	sleep(3);
	printf("Signal handler of SIGINT ended\n");
}

static void ssu_signal_handler2(int signo) {
	printf("SIgnal handler of SIGQUIT : %d\n",signo);
	printf("SIGINT signal is blocked : %d\n", signo);
	printf("sleeping 3 sec\n");
	sleep(3);
	printf("Signal handler of SIGQUIT ended\n");
}
