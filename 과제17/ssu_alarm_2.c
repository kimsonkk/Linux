#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define LINE_MAX 2048

static void ssu_alarm(int signo);

int main(void)
{
	char buf[LINE_MAX];
	int n;
	if(signal(SIGALRM, ssu_alarm) == SIG_ERR) {  //SIGALRM 시그널을 ssu_alarm으로 보낸다.
		fprintf(stderr, "SIGALRM error\n");  //오류 시 에러 메세지를 출력하고 종료한다.
		exit(1);
	}

	alarm(10);  //10초가 지나면 SIGALRM 시느얼을 보낸다.

	if((n = read(STDIN_FILENO, buf, LINE_MAX)) < 0) {  //표준 입력에서 읽어 들여 buf에 저장합니다.
		fprintf(stderr,"read() error\n");  //read 함수가 에러 시 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	alarm(0);  //0초 후에 SIGALRM 시그널을 보낸다.
	write(STDOUT_FILENO, buf, n);
	exit(0);
}

static void ssu_alarm(int signo) {  //SIGALRM을 받으면 동작합니다.
	printf("ssu_alarm() called\n");
}
