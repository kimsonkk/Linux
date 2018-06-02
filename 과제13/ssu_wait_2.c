#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EXIT_CODE 1

int main()
{
	pid_t pid;
	int ret_val, status;

	if((pid = fork()) == 0) {  //fork함수를 이용해서 프로세스를 나눕니다.
		printf("child: pid = %d ppid = %d exit_code = %d\n",  //자식 프로세스는 자신의 pid, 부모의 pid와 종료 상태를 출력합니다.
				getpid(), getppid(), EXIT_CODE);
		exit(EXIT_CODE);
	}

	printf("parent: waiting for child = %d\n",pid);	  //부모는 자신의 pid를 출력합니다.
	ret_val = wait(&status);  //자식 프로세스가 종료될때까지 기다리고 자식의 pid를 저장합니다.
	printf("parent: return vlaue = %d, ",ret_val);  //자식의 pid를 출력합니다.
	printf(" child's status = %x", status);  //자식의 종료 상태를 출력합니다.
	printf(" and shifted = %x\n", (status >> 8));
	exit(0);
}
