#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
	pid_t pid;
	char character, first, last;
	long i;

	if((pid = fork()) > 0) {  //부모 프로세스는 변수에 대문자를 저장합니다.
		first = 'A';
		last = 'Z';
	}
	else if (pid == 0) {  //자식 프로세스는 변수에 소문자를 저장합니다.
		first = 'a';
		last = 'z';
	}
	else {  //fork에 실패하면 에러 처리를 하고 정리합니다.
		fprintf(stderr,"%s\n",argv[0]);
		exit(1);
	}

	for(character = first; character <= last; character++) {  //표준 출력에 a혹은 A부터 z혹은 Z까지 출력합니다.
		for (i = 0; i < 100000; i++)
			;
		write(1, &character, 1);
	}

	printf("\n");
	exit(0);
}
