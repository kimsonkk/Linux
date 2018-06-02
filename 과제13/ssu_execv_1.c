#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/wait.h>

double ssu_maketime(struct timeval *time);

void term_stat(int stat);

void ssu_print_child_info(int stat, struct rusage *rusage);

int main()
{
	struct rusage rusage;
	pid_t pid;
	int status;

	if((pid = fork()) == 0) {  //fork함수를 이용해 프로세스를 나누어 자식 프로세스에서 진행합니다.
		char *args[] = {"find", "/", "-maxdepth", "4", "-name", "stdio.h", NULL};

		if(execv("/usr/bin/find",args) < 0) {  //자식 프로세스를 새로운 프로그램으로 만들어 실행합니다.
			fprintf(stderr,"exec error\n");  //execv함수가 실패할 경우 에러 메세지를 출력하고 종료합니다.
			exit(1);
		}
	}

	if(wait3(&status, 0 , &rusage) == pid)  //종료된 자식 프로세스가 사용한 자원 사용량에 대한 정보를 얻어옵니다.
		ssu_print_child_info(status,&rusage);  //자워의 사용량을 출력합니다.
	else {
		fprintf(stderr,"wait3 error\n");
		exit(1);
	}

	exit(0);
}

double ssu_maketime(struct timeval *time) {  //timeval구조체의 시간을 계산해서 반환합니다.
	return ((double)time -> tv_sec + (double)time -> tv_usec/1000000.0);
}

void term_stat(int stat) {  //프로세스의 종료상태를 출력합니다.
	if(WIFEXITED(stat))  //자식이 정상적으로 종료되었을 경우입니다.
		printf("normally terminated, exit status = %d\n", WEXITSTATUS(stat));
	else if( WIFSIGNALED(stat))  //자식 프로세스가 시그널을 받았으나 그것을 처리하지 않아 비정상적을 종료되었을 경우 입니다.
		printf("abnormal termination by signal %d, %s\n", WTERMSIG(stat),
#ifdef WCOREDUMP
				WCOREDUMP(stat)?"core dumped":"no core"  //코어 파일이 생성된 경우 core dump를 출력합니다.
#else
				NULL
#endif
			  );
	else if(WIFSTOPPED(stat))  //자식 프로세스가 현재 종료상태일 경우입니다.
		printf("stopped by signal %d\n", WSTOPSIG(stat));
}

void ssu_print_child_info(int stat, struct rusage *rusage) {  //프로세스의 자원의 사용량을 출력합니다.
	printf("Termination info follows\n");
	term_stat(stat);
	printf("user CPU time : %.2f(sec)\n", ssu_maketime(&rusage->ru_utime));
	printf("system CPU time : %.2f(sec)\n", ssu_maketime(&rusage->ru_stime));
}
