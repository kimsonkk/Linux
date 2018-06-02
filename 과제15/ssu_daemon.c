#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>

int ssu_daemon_init(void);

int main(void) 
{
	pid_t pid;

	pid = getpid();  //현재 프로세스 ID를 가져옵니다.
	printf("parent process : %d\n",pid);
	printf("daemon process initialization\n");

	if(ssu_daemon_init() < 0) {  //디몬 프로세를 실행합니다.
		fprintf(stderr,"ssu_daemon_init dailed\n");  //실패할 경우 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}
	exit(0);
}

int ssu_daemon_init(void) {
	pid_t pid;
	int fd, maxfd;

	if(( pid = fork()) < 0) {  //fork함수를 이용해서 자식 프로세스를 생성합니다.
		fprintf(stderr,"fork error\n");  //fork함수가 실패할 경우 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}
	else if(pid != 0)  //부모 프로세스의 경우 종료합니다.
		exit(0);

	pid = getpid();  //현재 프로세스의 프로세스 id를 가져옵니다.
	printf("process %d running as daemon\n",pid);
	setsid();  //새로운 프로셋스 세션을 만듭니다.
	signal(SIGTTIN, SIG_IGN);  //SIGTTIN 시그널을 무시합니다.
	signal(SIGTTOU, SIG_IGN);  //SIGTTOU 시그널을 무시합니다.
	signal(SIGTSTP, SIG_IGN);  //SIGTSTP 시느널을 무시합니다.
	maxfd = getdtablesize();  //파일 디스크립터 테이블의 최대값을 가져옵니다.

	for (fd = 0; fd < maxfd ; fd++)  //모든 파일 디스크립터를 닫습니다.
		close(fd);
	umask(0);  //umask 값을 0으로 만듭니다.
	chdir("/");  //루트로 디렉터리를 변경합니다.
	fd = open("/dev/null", O_RDWR);  //표준 입출력과 에러에 대한 파일 디스크립터를 전부 /dev/null로 재지정합니다.
	dup(0);
	dup(0);
	return 0;
}
