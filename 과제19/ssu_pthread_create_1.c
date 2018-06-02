#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *ssu_thread(void *arg);

int main(void)
{
	pthread_t tid;
	pid_t pid;

	if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0) {  //ssu_thread에서 실행하는 스레드를 생성합니다.
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	pid = getpid();  //현재 프로세스 ID얻어옵니다.
	tid = pthread_self();  //스레드의 아이디를 가져옵니다.
	printf("Main THread: pid %u tid %u \n",
			(unsigned int)pid, (unsigned int)tid);
		sleep(1);  //1초 동안 프로세스를 정지합니다.
	exit(0);
}

void *ssu_thread(void *arg) {
	pthread_t tid;
		pid_t pid;

	pid = getpid();  //프로세스 ID 얻어옵니다.
	tid = pthread_self();  //현재 스레드의 ID얻어옵니다.
	printf("New Thread: pid %d tid %u \n", (int)pid, (unsigned int)tid);
	return NULL;
}
