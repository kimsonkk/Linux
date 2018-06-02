#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <termios.h>

#define STDIN_NUMBER 0

static void ssu_sig_hup(int signum);
static void ssu_print_ids(char *name);

int main(void)
{
	pid_t pid;
	char character;

	ssu_print_ids("parent");  //부모 프로세스의 정보를 출력합니다.
	if((pid = fork()) < 0) {  //fork함수를 이용해서 자식 프러세스를 만듭니다.
		fprintf(stderr,"fork error\n");  //fork함수가 실패할 경우 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}
	else if(pid > 0) {  //부모 프로세스의 경우 3초간 기다렸다가 종료합니다.
		sleep(3);
		exit(0);
	}
	else {  //자식 프로세스의 경우 수행합니다.
		ssu_print_ids("child");  //자식 프로세스의 정보를 출력합니다.
		signal(SIGHUP,ssu_sig_hup);  //프로세스의 SIGHUP시그널을 받으면 핸들러로 전달해줍니다.
		kill(getpid(), SIGTSTP);  //스스로에게 SIGSTP시그널을 전달합니다.
		ssu_print_ids("child");  //자식 프로세스의 정보를 출력합니다.

		if(read(STDIN_FILENO, &character, 1) != 1)  //표준 입력으로부터 한글자를 받아옵니다.
			fprintf(stderr, "read error\n");
		exit(0);
	}
}

static void ssu_sig_hup(int signum) {  //시그널을 받으면 현재의 pid를 출력합니다.
	printf("ssu_SIG_HUP received, pid = %d\n", getpid());
}

static void ssu_print_ids(char *name) {  //인자로 받아온 name을 출력하고 현재 프로세스의 id 정보들을 출력합니다.
	printf("[%s] : pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n",
			name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_NUMBER));
	fflush(stdout);
}
