#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void ssu_echo_exit(int status);

int main()
{
	pid_t pid;
	int status;

	if((pid = fork()) < 0) {  //fork함수를 이용해서 프로세스를 나눕니다.
		fprintf(stderr,"fork error\n");
		exit(1);
	}

	else if(pid == 0)  //자식 프로세스를 정상종료합니다.
		exit(7);

	if(wait(&status) != pid) {  //부모 프로세스가 자식 프로세스가 종료될때까지 기다립니다.
		fprintf(stderr,"wait error\n");
		exit(1);
	}

	ssu_echo_exit(status);  //자식의 종료 상태를 출력합니다.

	if((pid = fork()) <0) {  //fork함수를 이용해서 프로세스를 나눕니다.
		fprintf(stderr,"fork error\n");
		exit(1);
	}
	else if (pid == 0)  //자식 프로세스는 abort함수를 이용해서 비정상적으로 종료시킵니다.
		abort();

	if(wait(&status) != pid) {  //부모 프로세스는 자식 프로세스가 종료될때까지 기다립니다.
		fprintf(stderr,"wait error\n");
		exit(1);
	}

	ssu_echo_exit(status);  //자식 프로세스의 종료 상태를 출력합니다.

	if((pid = fork()) < 0) {  //fork함수를 이용해서 프로세스를 나눕니다.
		fprintf(stderr,"fork error\n");
		exit(1);
	}
	else if(pid == 0)  //자식 프로레스는 0으로 나누는 연산을 하여 비정상 종료합니다.
		status /= 0;

	if(wait(&status) != pid) {  //부모 프로세스는 자식 프로세스가 종료될때까지 기다립니다.
		fprintf(stderr,"wait error\n");
		exit(1);
	}
	 ssu_echo_exit(status);  //자식 프로세스의 종료 상태를 출력합니다.
	 exit(0);
}

void ssu_echo_exit(int status) {
	if(WIFEXITED(status))  //프로세스가 정상적으로 종료되었으면 동작합니다. 
		printf("normal termination, exit status = %d\n",
				WEXITSTATUS(status));
	else if(WIFSIGNALED(status))  //자식이 시그널을 받앗으나 그것을 처리하지 않아 비정상 종료되었을 경우입니다.
		printf("abnormal termination, signal number = %d%s\n",
				WTERMSIG(status),
#ifdef WCOREDUMP  //코어 파일이 정의된 경우
				WCOREDUMP(status) ? "(core file generated)" : "");
#else  //코어 파일이 정의되 있지 않은 경우
	"");
#endif
	else if (WIFSTOPPED(status))  //자식 프로세스가 현재 중지 상태인 경우입니다.
		printf("child stopped, signal number = %d\n",WSTOPSIG(status));
}
