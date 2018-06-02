#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <time.h>

static void ssu_alarm(int signo);
static void ssu_func(int signo);
void ssu_mask(const char *str);
static volatile sig_atomic_t can_jump;
static sigjmp_buf jump_buf;

int main(void) 
{
	if (signal(SIGUSR1, ssu_func) == SIG_ERR) {  //SIGUSR1 시그널에 대한 핸들러로 ssu_func을 등록합니다.
		fprintf(stderr,"SIGUSR1 error\n");
		exit(1);
	}
	if(signal(SIGALRM, ssu_alarm) == SIG_ERR) {  //SIGALRM 시그널에 대한 핸들러로 ssu_alarm을 등록합니다.
		fprintf(stderr, "SIGALRM error");
		exit(1);
	}

	ssu_mask("starting main: ");
	if(sigsetjmp(jump_buf, 1)) {  //siglogjmp에 대한 jump위치를 저장합니다.
		ssu_mask("ending main: ");
		exit(0);
	}
	can_jump = 1;
	while(1)
		pause();  //일시정지 합니다.
	exit(0);
}

void ssu_mask(const char *str) {
	sigset_t sig_set;
	int err_num;

	err_num = errno;
	if(sigprocmask(0, NULL, &sig_set) < 0) {  //sig_set 시그널 집합에 대해 시그널 마스크를 저장합니다.
		printf("sigprocmask() error");
		exit(1);
	}

	printf("%s", str);

	if(sigismember(&sig_set, SIGINT))  //SIGINT 시그널이 sig_set에 포함되있는지 검사합니다.
		printf("SIGINT ");
	if(sigismember(&sig_set, SIGQUIT))  //SIGQUIT 시그널이 sig_set에 포함되있는지 검사합니다.
		printf("SIGQUIT ");
	if(sigismember(&sig_set, SIGUSR1))  //SIGUSR1 시그널이 sig_set에 포함되있는지 검사합니다.
		printf("SIGUSR1 ");
	if(sigismember(&sig_set, SIGALRM))  //SIGALRM 시그널이 sig_set에 포함되있는지 검사합니다.
		printf("SIGALRM ");

	printf("\n");
	errno = err_num;
}

static void ssu_func(int signo) {
	time_t start_time;

	if(can_jump == 0)
		return;

	ssu_mask("starting ssu_func: ");
	alarm(3);  //3초 후에 SIGALRM을 자신에게 보냅니다.
	start_time = time(NULL);  //현재 시간을 가져옵니다.

	while(1)
		if( time(NULL) > start_time + 5)
			break;
	ssu_mask("ending ssu_func: ");
	can_jump = 0;
	siglongjmp(jump_buf, 1);  //sigsetjmp 지점으로 jump합니다.
}

static void ssu_alarm(int signo) {
	ssu_mask("in ssu_alarm: ");
}
