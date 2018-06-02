#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	if(fork() == 0) {  //fork함수를 이용해 자식 프로세스를 만들어 자식 프로세스에서 진행합니다.
		execl("/bin/echo", "echo", "this is", "message one", (char*)0); //execl함수를 이용해서 자식 프로세스를 새로운 프롣그램으로 만들어 실행합니다.
		fprintf(stderr,"exec error\n");
		exit(1);
	}
	if(fork() == 0) {  //fork함수를 이용해서 자식 프로세스를 만들어 자식 프로세스에서 진행합니다.
		execl("/bin/echo", "echo", "this is", "message two", (char*)0);  //execl함수를 이용해서 자식 프로세스를 새로운 프로그램으로 만들어 실행합니다 
		fprintf(stderr,"exec error\n");
		exit(1);
	}
	if(fork() == 0) {  //fork함수를 이용해서 자식 프로세스를 만들어 자식 프로세스에서 진행합니다.
		execl("/bin/echo", "echo", "this is", "message three", (char*)0);  //execl함수를 이용해서 자식 프로세스를 새로운 프로그램으로 만들어 실행합니다.
		fprintf(stderr,"exec error\n");
		exit(1);
	}

	printf("Parent program ending\n");
	exit(0);
}
