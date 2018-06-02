#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>

static void ssu_signal_handler1(int signo);
static void ssu_signal_handler2(int signo);

sigjmp_buf jmp_buf1;
sigjmp_buf jmp_buf2;

int main(void) 
{
	struct sigaction act_sig1;
	struct sigaction act_sig2;
	int i, ret;

	printf("My PID is %d\n", getpid());
	ret = sigsetjmp(jmp_buf1, 1);  //siglongjmp의 jump지점을 저장합니다.

	if (ret == 0) {
		act_sig1.sa_handler = ssu_signal_handler1;  //sigaction의 핸들러를 등록합니다.
		sigaction(SIGINT, &act_sig1, NULL);  //SIGINT 시그널에 대한 액션으로 act_sig를 등록합니다.
	}
	else if (ret == 3)
		printf("-----------------------\n");

	printf("Starting\n");
	sigsetjmp(jmp_buf2, 2);  //siglongjmp에 대한 jump 지점을 저장합니다.
	act_sig2.sa_handler = ssu_signal_handler2;  //act_sig2에 핸들러로 ssu_signal_handler2를 등록합니다.
	sigaction(SIGUSR1, &act_sig2, NULL);

	for (i = 0; i < 20; i++) {
		printf("i = %d\n", i);
		sleep(1);
	}
	exit(0);
}

static void ssu_signal_handler1(int signo) {
	fprintf(stderr, "\nInterrupted\n");
	siglongjmp(jmp_buf1, 3);  //sigsetjmp 지점으로 jump합니다.
}

static void ssu_signal_handler2(int signo) {
	fprintf(stderr, "\nSIGUSR1\n");
	siglongjmp(jmp_buf2, 2);  //sigsetjmp 지점으로 jump합니다.
}
