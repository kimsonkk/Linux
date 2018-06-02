#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void ssu_signal_handler(int signo);
void ssu_timestamp(char *str);

int main(void)
{
	struct sigaction sig_act;
	sigset_t blk_set;

	sigfillset(&blk_set);  //blk_set 시그널 집합에 모든 시그널을 추가합니다.
	sigdelset(&blk_set, SIGALRM);  //blk_set에서 SIGALRM 시그널을 제거합니다.
	sigemptyset(&sig_act.sa_mask);  //sig_act.sa_mask 시그널 집합을 시그널이 업는 상태로 초기화합니다.
	sig_act.sa_flags = 0;
	sig_act.sa_handler = ssu_signal_handler;  //sig_act의 핸들러를 ssu_signal_handler로 등록합니다.
	sigaction(SIGALRM, &sig_act, NULL);  //SIGALRM 시그널에 대해 액션을 등록합니다.
	ssu_timestamp("before sigsuspend()");
	alarm(5);  //5초 후에 SIGALRM을 발생시킵니다.
	sigsuspend(&blk_set);  //blK_set의 시그널이 들어오기 전까지 유보합니다.
	ssu_timestamp("after sigsuspend()");
	exit(0);
}

void ssu_signal_handler(int signo) {
	printf("in ssu_signal_handler() function\n");
}

void ssu_timestamp(char *str) {
	time_t time_val;

	time(&time_val);  // 현재 시간을 저장합니다.
	printf("%s the time is %s\n", str, ctime(&time_val));
}
