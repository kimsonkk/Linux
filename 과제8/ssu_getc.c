#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int character;

	while((character = getc(stdin)) != EOF)  //getc를 이용해 표준 입력으로 부터 입력을 받습니다.
		if(putc(character, stdout) == EOF) {  //putc를 이용해서 입력해서 받은 문자를 출력합니다.
			fprintf(stderr,"standard output error\n");
			exit(1);
		}

	if(ferror(stdin)) {  //에러가 있다면 에러 문장을 출력하고 종료합니다.
		fprintf(stderr,"standard input error\n");
		exit(1);
	}

	exit(0);
}
