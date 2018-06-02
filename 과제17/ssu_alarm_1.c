#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo);

int count = 0;

int main(void)
{
	signal(SIGALRM, ssu_signal_handler);  //SIGALRM 시느얼을 받으면 ssu_signal_handler로 보낸다.
	alarm(1);  //1초가 지나면 SIGALRM을 보낸다.

	while(1);

	exit(0);
}

void ssu_signal_handler(int signo) {
	printf("alarm %d\n", count++);  //count를 출럭합니다.
	alarm(1);  //1초가 지나면 SIGALRM을 보낸다.
}
