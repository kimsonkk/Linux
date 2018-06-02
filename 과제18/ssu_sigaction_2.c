#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_check_pending(int signo, char *signame);
void ssu_signal_handler(int signo);

int main(void)
{
	struct sigaction sig_act;
	sigset_t sig_set;

	sigemptyset(&sig_act.sa_mask);  //sig_act의 sa_mask 시그널 집합의 시그널들을 0으로 초기화합니다.
	sig_act.sa_flags = 0;
	sig_act.sa_handler = ssu_signal_handler;  //sig_act의 시그널 핸들러를 설정합니다.

	if(sigaction(SIGUSR1, &sig_act, NULL) != 0) {  //sigaction함수를 호출해서 SIGUSR1 시그널의 액션을 설정합니다.
		fprintf(stderr, "sigaction() error\n");
		exit(1);
	}
	else {
		sigemptyset(&sig_set);  //sig_set 시그널 집합의 시그널들을 0으로 초기화합니다.
		sigaddset(&sig_set, SIGUSR1);  //sig_set에 SIGUSR1 시그널을 출가합니다.

		if(sigprocmask(SIG_SETMASK, &sig_set, NULL) != 0) {  //sigprocmsk를 통해 SIGUSR1을 블락합니다.
			fprintf(stderr, "sigprocmask() error\n");
			exit(1);
		}
		else {
			printf("SIGUSR1 signals are now blocked\n");
			kill(getpid(), SIGUSR1);  //현재 프로세스에 SIGUSR1 시그널을 보냅니다.
			printf("after kill() \n");
			ssu_check_pending(SIGUSR1, "SIGUSR1");  
			sigemptyset(&sig_set);  //sig_set의 시그널 집합의 시그널을 저눕 0으로 초기화합니다.
			sigprocmask(SIG_SETMASK, &sig_set, NULL);  //sig_set으로 블락을 초기화합니다.
			printf("SIGUSR1 signals are no longer blocked\n");
			ssu_check_pending(SIGUSR1, "SIGUSR1");
		}
	}
	exit(0);
}

void ssu_check_pending(int signo, char *signame) {
	sigset_t sig_set;

	if(sigpending(&sig_set) != 0)  //sig_set을 통해 시그널이 블락되있는지 확인합니다.
		printf("sigpending() error\n");
	else if (sigismember(&sig_set, signo))  //signo가 sig_set의 멤버인지 확인합니다.
		printf("a %s signal is pending\n", signame);
	else
		printf("%s signals are not pending\n",signame);
}

void ssu_signal_handler(int signo) {
	printf("in ssu_signal_handler function\n");
}
