#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	if(fork() == 0)  //프로세스를 나누어 자식 프로세스에서 진행합니다.
		execl("/bin/echo", "echo", "this is", "message one", (char *)0);  //자식 프로세스를 새로운 프로그램으로 실행시킵니다.

	if(fork() == 0)  //프로세스를 나누어 자식 프로세스에서 진행합니다.
		execl("/bin/echo", "echo", "this is", "message Two", (char *)0);  //자식 프로세스를 새로운 프로그램으로 실행시킵니다.

	printf("parent: waiting for children\n");

	while(wait((int*)0) != -1);  //부모 프로세스가 모든 자식의 종료를 기다립니다.

	printf("parent: all children terminated\n");
	exit(0);
}
