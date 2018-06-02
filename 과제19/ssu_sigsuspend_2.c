#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

static void ssu_func(int signo);
void ssu_print_mask(const char *str);

int main(void)
{
	sigset_t new_mask, old_mask, wait_mask;
	ssu_print_mask("program start: ");

	if(signal(SIGINT, ssu_func) == SIG_ERR) {  //SIGINT 시느러에 ssu_func핸들러를 등록합니다.
		fprintf(stderr, "signal(SIGINT) error\n");
		exit(1);
	}

	sigemptyset(&wait_mask);  //sait_mask 시그널 집합을 시그널이 모두 없는 상태로 초기화합니다.
	sigaddset(&wait_mask, SIGUSR1);  //wait_mask에 SIGUSR1 시그널을 추가합니다.
	sigemptyset(&new_mask);  //new_mask 시그널 집합을 시그널이 모두 없는 상태로 초기화합니다.
	sigaddset(&new_mask, SIGINT);  //new_mask에 SIGINT 시그널을 추가합니다.

	if(sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {  //new_maks와 old_mask의 합을 시그널 블록으로 지정합니다.
		fprintf(stderr, "SIG_BLOCK() error\n");
		exit(1);
	}

	ssu_print_mask("in critical region: ");

	if(sigsuspend(&wait_mask) != -1) {  //wait_maks의 시그널이 발생할때까지 유보합니다.
		fprintf(stderr, "sigsuspend() error\n");
		exit(1);
	}

	ssu_print_mask("after return from sigsuspend: ");

	if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {  //old_mask로 시그널 블록을 설정합니다.
		fprintf(stderr, "SIG_SETMASK() error\n");
		exit(1);
	}

	ssu_print_mask("program exit: ");
	exit(0);
}

void ssu_print_mask(const char *str) {
	sigset_t sig_set;
	int err_num;

	err_num = errno;
	if(sigprocmask(0, NULL, &sig_set) < 0) {  //sig_set으로 시그널 블락을 지정합니다.
		fprintf(stderr, "sigprocmask() error\n");
		exit(1);
	}

	printf("%s", str);

	if(sigismember(&sig_set, SIGINT))  //SIGINT가 sig_set에 포함되있는지 검사합니다.
		printf("SIGINT ");
	if(sigismember(&sig_set, SIGQUIT))  //SIGQUIT가 sig_set에 포함되있는지 검사합니다.
		printf("SIGQUIT ");
	if(sigismember(&sig_set, SIGUSR1))  //SIGUSR1가 sig_set에 포함되있는지 검사합니다.
		printf("SIGUSR1 ");
	if(sigismember(&sig_set, SIGALRM))  //SIGALRM가 sig_set에 포함되있는지 검사합니다.
		printf("SIGALRM ");

	printf("\n");
	errno = err_num;
}

static void ssu_func(int signo) {
	ssu_print_mask("\nin ssu_funcL ");
}
