#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_alarm(int signo);

int main(void)
{
	printf("Alarm Setting\n");
	signal(SIGALRM, ssu_alarm);  //SIGALRM 시그널이 들어오면 ssu_alarm으로 보낸다.
	alarm(2);  //2초 후에 SIGALRM을 보낸다.

	while(1) { 
		printf("done\n");
		pause();  //시그널이 발생할떄까지 프로세스를 대기 상태로 만듭니다.
		alarm(2);  //2초 후에 SIGALRM시그널을 보냅니다.
	}
	exit(0);
}
void ssu_alarm(int signo) {
	printf("alarm..!!!\n");
}
