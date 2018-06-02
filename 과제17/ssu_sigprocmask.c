#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
	sigset_t sig_set;  //시그널 집합 sig_set을 선언합니다.
	int count;

	sigemptyset(&sig_set);  //sig_set을 빈 집합으로 초기화합니다.
	sigaddset(&sig_set, SIGINT);  //sig_set에 SIGINT를 추가합니다.
	sigprocmask(SIG_BLOCK, &sig_set, NULL);  //sig_set을 프로세스 마스크로 설정합니다.

	for(count = 3; 0 < count; count--) {
		printf("count %d\n",count);
		sleep(1);
	}

	printf("Ctrl -C에 대한 블록을 해제\n");
	sigprocmask(SIG_UNBLOCK, &sig_set, NULL);  //sig_set의 시그널에 대해 시그널 블록을 해제합니다.
	printf("count 중 Ctrl-C입력하면 이 문장은 출력 되지 않음.\n");
	while(1);
	exit(0);
}
