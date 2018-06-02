#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

int main()
{
	struct timeval start,end;
	gettimeofday(&start,NULL);
	printf("Process ID               = %d\n",getpid());  //프로세스 ID출력합니다.
	printf("Parent Process ID        = %d\n",getppid());  //프로세스의 부모 프로세스 ID를 출력합니다.
	printf("Real user ID             = %d\n",getuid());  //실제 사용자 ID를 출력합니다.
	printf("Effective user ID        = %d\n",geteuid());  //유효 사용자 ID를 출력합니다.
	printf("Real group ID            = %d\n",getgid());  //실제 그룹 ID를 출력합니다.
	printf("Effiective user ID       = %d\n",getegid());  //유효 그룹 ID를 출력합니다.
	gettimeofday(&end,NULL);
	printf("time : %f\n", end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
