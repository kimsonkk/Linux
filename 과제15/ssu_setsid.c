#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	if((pid = fork()) < 0) {  //fork함수를 이용해서 자식 프로세스를 만듭니다.
		fprintf(stderr,"fork error\n");  //fork함수가 실패할 경우 예외 처리를 하고 종료합니다.
		exit(1);
	}
	else if(pid != 0)  //부모 프로세스의 경우 종료합니다.
		exit(1);

	printf("before pid = %d, sid = %d\n", getpid(), getsid(getpid()));
	setsid();  //자식 프로세스가 새로운 세션을 만듭니다.
	printf("atfer pid = %d, sid = %d\n", getpid(), getsid(getpid()));
	exit(0);
}
