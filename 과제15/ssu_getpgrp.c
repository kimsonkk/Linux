#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pgid;
	pid_t pid;

	pid = getpid();  //프로세스 id를 저장합니다.
	pgid = getpgrp();  //프로세스의 프로세스 그룹 ID얻어옵니다.
	printf("pid: %d, pgid: %d\n", pid, pgid);
	exit(0);
}
