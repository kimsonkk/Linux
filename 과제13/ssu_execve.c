#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *argv[] = {
		"ssu_execl_test_1", "param1", "param2", (char *)0
	};
	char *env[] = {  //새로운 프로그램에 지정해줄 환경변수입니다.
		"NAME = value",
		"nextname=nextvalue",
		"HOME=/home/kimchangyeop",
		(char *)0
	};

	printf("this is the original program\n");
	execve("./ssu_execl_test_1", argv, env);  //execve함수를 이용해서 새로운 프로그램에 만들어준 새로운 환경변수르르 지정해서 실행합니다. 
	printf("%s\n", "this line should never get printed\n");
	exit(0);
}
