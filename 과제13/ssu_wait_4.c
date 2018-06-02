#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
	pid_t child1, child2;
	int pid, status;

	if((child1 = fork()) == 0)  //프로세스를 나누어 첫번째 자식 프로셋를 만들어 진행합니다.
		execlp("date", "date", (char *)0);  //자식 프로세스를 새로운 프로그램으로 나누어 실행합니다.

	if((child2 = fork()) == 0)  //프로세스를 나누어 두번째 자식 프로세스를 만들어 진행합니다.
		execlp("who", "who", (char *)0);  //자식 프로세스를 새로운 프로그램을 나누어 실행합니다.1

	printf("parent: waiting for children\n");

	while(( pid = wait(&status)) != -1) {  //자식들이 모두 종료될때까지 부모 프로세스는 기다리고있습니다.
		if( child1 == pid)  //첫번째 자식프로세스가 종료되었을 경우 실행됩니다.
			printf("parent: first child: %d\n",(status >> 8));
		else if( child2 == pid)  //두번째 자식 프로세스가 종료되었을 경우 실행됩니다.
			printf("parent: second child: %d\n",(status >> 8));
	}
	printf("parent: all children terminated\n");
	exit(0);
}

