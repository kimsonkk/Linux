#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
	sigset_t old_set;
	sigset_t sig_set;

	sigemptyset(&sig_set);  //sig_set 시그널 집합을 시그널이 없는 상태로 초기화합니다.
	sigaddset(&sig_set, SIGINT);  //sig_set에 SIGINT 시그널을 추가합니다.
	sigprocmask(SIG_BLOCK, &sig_set, &old_set);  //sig_set에 old_set을 합하여 새로운 시그널 블락을 지정합니다.
	sigsuspend(&old_set);  //old_set에 있는 시그널이 발생할 때까지 유보합니다.
	exit(0);
}
