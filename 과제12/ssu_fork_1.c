#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

char glob_str[] = "write to standard output\n";
int glob_val = 10;

int main(void)
{
	struct timeval start,end;
	pid_t pid;
	int loc_val;

	gettimeofday(&start,NULL);
	loc_val = 100;
	if(write(STDOUT_FILENO,  //표준 출력에 글을 입력합니다. 
				glob_str, sizeof(glob_str) - 1) != sizeof(glob_str) - 1) {  //입력한 글의 사이즈가 드러면 에러 처리를 합니다.
		fprintf(stderr,"write error\n");
		exit(1);
	}

	printf("before fork\n");

	if((pid = fork()) < 0) {  //fork의 결과가 0 보다 작으면 예외 처리를 합니다.
		fprintf(stderr,"fork error\n");
		exit(1);
	}
	else if(pid == 0) {  //자식 프로세스가 진행합니다.
		glob_val++;  //변수들의 값에 1을 추가합니다.
		loc_val++;
	}
	else  //부모 프로세스는 3초간 멈춥니다.
		sleep(3);

	printf("pid = %d, glob_val = %d, loc_val = %d\n",
			getpid(), glob_val, loc_val);  //pid값과 각 변수들을 출력합니다.
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
