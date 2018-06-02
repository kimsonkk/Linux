#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
	sigset_t pendingsigset;
	sigset_t sig_set;
	int count = 0;

	sigfillset(&sig_set);  //signal 집합인 pendingsigset을 전부 1로 채웁니다.
	sigprocmask(SIG_SETMASK, &sig_set, NULL);  //signal을 pendingsigset으로 블록합니다.

	while(1) {
		printf("count: %d\n", count++);
		sleep(1);

		if(sigpending(&pendingsigset) == 0) {  //SIGINT 시그널이 포함되어 있는지 검사합니다.
			if (sigismember(&pendingsigset, SIGINT)) {  //SIGINT 시그널이 pendingsigset의 멤버인지 검사합니다.
				printf("SIGINT가 블록되어 대기 중. 무한 루프를 종료.\n");
				break;
			}
		}
	}
	exit(0);
}
