#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pgid;
	pid_t pid;

	if( argc <  2) {  //입력받은 인자가 2개 미만일 경우 예외 처리를 하고 종료합니다.
		fprintf(stderr,"usage: %s <file>\n",argv[0]);
		exit(1);
	}

	pid = getpid();  //프로세스 id를 가져옵니다.
	pgid = getpgid(atoi(argv[1]));  //인자로 받은 argv[1]의 프로세스 그룹 ID가져옵니다.
	printf("pid: %d, pgid: %d\n", pid, pgid);
	exit(0);
}
