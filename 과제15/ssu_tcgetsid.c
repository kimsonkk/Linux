#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <termios.h>

int main(void)
{
	pid_t sid_stderr;
	pid_t sid_stdin;
	pid_t sid_stdout;

	sid_stdin = tcgetsid(STDIN_FILENO);  //표준 입력에 해당하는 제어 터미널과 연관된 세션 리더의 프로세스 그룹 ID를 리턴합니다.

	if(sid_stdin == -1) {  //tcgetsid함수가 실패할 경우 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"tcgetsid error\n");
		exit(1);
	}
	else  //성공하면 세션 리더의 프로세스 그룹 id를 출력합니다.
		printf("Session Leader for stdin: %d\n",sid_stdin);

	sid_stdout = tcgetsid(STDOUT_FILENO);  //표준 출력에 해당하는 제어 터미널과 연관된 세션 리더의 프로세스 그룹 ID를 리턴합니다.
	if(sid_stdout == -1) {  //tcgetsid함수가 실패할 경우 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr, "tcgetsid error\n");
		exit(1);
	}
	else  //성공하면 세션 리더의 프로세스 그룹 id를 출력합니다.
		printf("Session Leader for stdout: %d\n", sid_stdout);

	sid_stderr = tcgetsid(STDERR_FILENO);  //표준 에러에 해당하는 제어 터미널과 연관된 세션 리더의 프로세스 그룹 ID를 리턴합니다.

	if(sid_stderr == -1) {  //tcgetsid함수가 실패할 경우 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr, "tcgetsid error\n");
		exit(1);
	}
	else  //성공하면 세션 리더의 프로세스 그룹 ID를 출력합니다.
		printf("Session Leader for stderr: %d\n", sid_stderr);
	exit(0);
}
