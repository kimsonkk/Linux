#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo);  //받아온 시그널을 처리할 핸들러입니다.

void (*ssu_func)(int);

int main(void)
{
	ssu_func = signal(SIGINT, ssu_signal_handler);  /*SIGINT 시그널이 발생하면 ssu_signal_handler로 보내서 처리하고
													  이전 핸들러의 주소를 반환해서 ssu_func에 저장한다.*/

	while(1) {  //무한 반복한다.
		printf("process running...\n");
		sleep(1);
	}
	exit(0);
}

void ssu_signal_handler(int signo) {
	printf("SIGINT 시그널 발생.\n");
	printf("SIGINT를 SIG_DFL로 재설정 함.\n");
	signal(SIGINT, ssu_func);  //SIGINT 시그널이 발생하면 ssu_func가 호출되어 디폴트인 종료를 수행한다.
}
