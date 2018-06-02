#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo) {  //signal 핸들러 함수입니다.
	printf("ssu_signal_handler control\n");
}

int main(void) {
	struct sigaction sig_act;
	sigset_t sig_set;

	sigemptyset(&sig_act.sa_mask);  //sig_act의 sa_mask의 시그널 집합을 전부 0으로 초기화합니다.
	sig_act.sa_flags = 0;  //sig_act의 sa_flag에 0을 저장합니다.
	sig_act.sa_handler = ssu_signal_handler;  //sig_act의 핸들러를 지정합니다.
	sigaction(SIGUSR1, &sig_act, NULL);  //sigaction함수를 호출해 SIGUSR1 시그널의 액션을 지정합니다.
	printf("before first kill()\n");
	kill(getpid(), SIGUSR1);  //현재 프로세스에 SIGUSR1 시그널을 보냅니다.
	sigemptyset(&sig_set);  //sig_set의 시그널 집합을 전부 0으로 초기화합니다.
	sigaddset(&sig_set, SIGUSR1);  //sig_set에 SIGUSR1을 추가합니다.
	sigprocmask(SIG_SETMASK, &sig_set, NULL);  //sig_set의 시그널을 블락합니다.
	printf("before second kill()\n");
	kill(getpid(), SIGUSR1);  //현재 프로세스에 SIGUSR1 시그널을 보냅니다.
	printf("after second kill()\n");
	exit(0);
}
