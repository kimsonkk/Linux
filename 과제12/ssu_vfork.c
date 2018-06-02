#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

void ssu_local_func(void);

int main(void)
{
	printf("Before vfork\n");
	ssu_local_func();
	printf("After ssu_local_func, my PID is %d\n", getpid());
	exit(0);
}

void ssu_local_func(void) {
	pid_t pid;

	if((pid = vfork()) == 0)  //vfork함수를 이용해서 프로세스를 나눕니다.
		printf("I'm child, My PID is %d\n",getpid());  //자식 프로세스가 수행합니다.
	else if (pid > 0)  //부모 프로세스가 수행합니다.
		sleep(3);
	else
		fprintf(stderr,"vfork error\n");  //실패 시 에러 처리를 합니다.

}
