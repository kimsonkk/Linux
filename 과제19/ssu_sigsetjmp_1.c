#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

void ssu_signal_handler(int signo);

jmp_buf jump_buffer;

int main(void)
{
	signal(SIGINT, ssu_signal_handler);  //SIGINT시그널에 대한 핸들러로 ssu_signal_handler를 등록한다.

	while(1) {
		if(setjmp(jump_buffer) == 0) {  //longjmp 호출시 jump될 위치를 저장한다.
			printf("Hit Ctrl-c at anytime ...\n");
			pause();  //일시정지 상태로 변경한다.
		}
	}
	exit(0);
}

void ssu_signal_handler(int signo) {
	char character;

	signal(signo, SIG_IGN);  //signo에 대해서 무시를 한다.
	printf("Did you hit Ctrl-c?\n" "Do you really want to quit? [y/n] ");
	character = getchar();  //표준 입력에서 한 글자를 받아온다.

	if( character == 'y' || character == 'Y')
		exit(0);
	else {
		signal(SIGINT, ssu_signal_handler);  //SIGINT 시그널에 대한 핸들러로 ssu_signal_handler를 등록한다.
		longjmp(jump_buffer, 1);  //setjmp한 위치로 jump한다.
	}
}
