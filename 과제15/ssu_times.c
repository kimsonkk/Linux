#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/wait.h>

void ssu_do_cmd(char *cmd);
void ssu_print_times(clock_t real, struct tms *tms_start, struct tms *tms_emd);
void ssu_echo_exit(int status);

int main(int argc, char *argv[])
{
	int i;

	setbuf(stdout, NULL);  //표준 출력에 출력 버프를 NULL로 설정합니다.

	for (i = 1; i < argc; i++)  //인자로 받은 argc수 만큼 반복합니다.
		ssu_do_cmd(argv[i]);
	exit(0);
}

void ssu_do_cmd(char *cmd) {  //인자로 받은 명령을 실행하고 수행하는데 사용된 시간과 종료상태를 출력합니다.
	struct tms tms_start, tms_end;
	clock_t start, end;
	int status;

	printf("\ncommand: %s\n", cmd);
	if((start = times(&tms_start)) == -1) {  //명령을 수행하기 이전 시가을 저장합니다.
		fprintf(stderr,"times error\n");
		exit(1);
	}

	if((status = system(cmd)) <0) {  //system함수를 이용해서 인자로 받아온 명령어를 실행합니다.
		fprintf(stderr,"times error\n");
		exit(1);
	}

	if((end = times(&tms_end)) == -1) {  //명령을 수행하고 난 이후의 시간을 저장합니다.
		fprintf(stderr,"times error\n");
		exit(1);
	}

	ssu_print_times(end-start,&tms_start,&tms_end);  //시간을 계산해서 출력합니다.
	ssu_echo_exit(status);  //종료상태를 출력합니다.
}

void ssu_print_times(clock_t real, struct tms *tms_start, struct tms *tms_end) {  //인자로 받은 시간을 계산해서 출력합니다.
	static long clocktick = 0;

	if(clocktick == 0)
		if((clocktick = sysconf(_SC_CLK_TCK)) < 0) {  //초당 사용되는 cllok ticks수를 가져옵니다.
			fprintf(stderr,"sysconf error\n");
			exit(1);
		}

	printf("  real: %7.2f\n",real/(double)clocktick);  //클록 시간을 출력합니다.
	printf("  user: %7.2f\n",
			(tms_end->tms_utime - tms_start->tms_utime) / (double)clocktick);  //cpu의 시간을 출력합니다.
	printf("  sys:  %7.2f\n",
			(tms_end->tms_stime - tms_start->tms_stime) / (double)clocktick);  //시스템 CPU 시간을 출력합니다.
	printf("  child user: %7.2f\n",
			(tms_end->tms_cutime - tms_start->tms_cutime) / (double)clocktick);  //자식 프로세스의 CPU 시간을 출력합니다.
	printf("  child sys:  %7.2f\n",
			(tms_end->tms_cstime - tms_start->tms_cstime) / (double)clocktick);  //자식 프로세스의 시스쳄 CPU 시간을 출력합니다.
}

void ssu_echo_exit(int status) {  //종료 상태를 출력하는 함수입니다.
	if(WIFEXITED(status))
		printf("normal termination, exit status = %d\n",  //정상 종료일 경우 종료 상태를 출력합니다.
				WEXITSTATUS(status));
	else if(WIFSIGNALED(status))  //프로세스가 시그널을 받아 비정상 종료할 경우 상태와 코어 덤프 여부를 출력합니다.
		printf("abnormal termination, signal number = %d%s\n",
				WTERMSIG(status),
#ifdef WCOREDUMP
				WCOREDUMP(status) ? "(core file generated)" : "");
#else
	"");
#endif
	else if(WIFSTOPPED(status))  //일시 정지 살태일 경우 출력합니다.
		printf("child stopped, signal number = %d\n",
				WSTOPSIG(status));
}
