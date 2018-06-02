#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if (argc < 2) {  //입력받은 인자가 2개보다 작을 경우 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"Usage : %s <file1> <file2>\n",argv[0]);
		exit(1);
	}

	if(link(argv[1],argv[2]) == -1) {  //argv[2]이라는 이름의  argv[1]과 같은 파일을 만들어준다.
		fprintf(stderr,"link error for %s\n",argv[1]);
		exit(1);
	}

	exit(0);
}
