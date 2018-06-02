#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void ssu_signal_handler(int signo);

int main(void)
{
	if(signal(SIGINT, ssu_signal_handler) == SIG_ERR) {  //SIGINT 시그널을 ssu_signal_hanlder로 보냅니다.
		//signal호출에서 에러가 나서 SIG_ERR를 반환하면 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGTERM, ssu_signal_handler) == SIG_ERR) {  //SIGTERM 시그널을  ssu_signal_handler로 보냅니다.
		//signal호출에서 에러가 나서 SIG_ERR를 반환하면 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"cannot handle SIGTERM\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGPROF, SIG_DFL) == SIG_ERR) {  //SIGPROF 시그널에 대해 디폴트로 처리합니다.
		//signal 호출에서 에러가 나서 SIG_ERR를 반환하면 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr, "cannot handle SIGPROF\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGHUP, SIG_DFL) == SIG_ERR) {  //SIGHUP 시그널에 대해 디폴트로 처리합니다.
		//signal 호출에서 에러가 나서 SIG_ERR를 반환하면 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"cannot handle SIGHUP\n");
		exit(EXIT_FAILURE);
	}

	while(1)
		pause();
	exit(0);
}

static void ssu_signal_handler(int signo) {
	if(signo == SIGINT)  //시그널이 SIGINT일 경우 처리합니다.
		printf("caught SIGINT\n");
	else if(signo == SIGTERM)  //시그널이 SIGTERM일 경우 처리합니다.
		printf("caught SIGTERM\n");
	else {  //이외의 시그널이 올 경우 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"unexpected signal\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
