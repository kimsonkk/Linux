#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define MODE_EXEC (S_IXUSR | S_IXGRP | S_IXOTH)

int main(int argc, char* argv[])
{
	struct stat statbuf;
	int i;

	if(argc < 2) {  //인자로 받은 표준 입력의 수가 2보다 작으면 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr, "Usage : %s <file1> <fil2> ...<fileN>\n",argv[0]);
		exit(1);
	}

	for(i = 1; i < argc; i++)  //인자들의 stat구조체를 순차적으로 받아옵니다.
	{
		if(stat(argv[i],&statbuf) <0) {  //stat구조체를 받아올 때 실패하면 에러메세지를 출력합니다.
			fprintf(stderr,"%s: stat error\n",argv[i]);
			continue;
		}

		statbuf.st_mode |= MODE_EXEC;  //실행 권한들을 줍니다
		statbuf.st_mode ^= (S_IXGRP|S_IXOTH);  //Group과 Other의 실행 권한이 있다면 제거해 주고 없다면 권한을 줍니다.
		if(chmod(argv[i], statbuf.st_mode) < 0)  //권한은 변경합니다.
			fprintf(stderr,"%s : chmod error\n",argv[i]);
		else
			printf("%s : file permission was changed.\n",argv[i]);
	}
	exit(0);
}
