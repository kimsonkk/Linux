#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TABLE_SIZE (sizeof(table)/sizeof(*table))  //file의 권한을 비교하기 위해 size를 지정해둡니다.

int main(int argc, char* argv[])
{
	struct{  //파일의 권한을 확인하기 위한 구조체입니다.
		char* text;
		int mode;
	} table[] = {
		{"exists", 0},
		{"execute", 1},
		{"write", 2},
		{"read", 4}
	};
	int i;

	if(argc<2) {  //인자로 받은 명령어가 2개 보다 작을 경우 예외처리를 하고 종료합니다.
		fprintf(stderr, "usage : %s <file>\n",argv[0]);
		exit(1);
	}

	for (i = 0; i < TABLE_SIZE;i++) {  //TABLE_SIZE만큼 반복합니다.
		if(access(argv[1],table[i].mode) != -1) //읽은 file의 권한에 따라 그 권한이 허락되있으면 시행합니다
			printf("%s -ok\n",table[i].text);
		else  //읽은 file이 권한이 없을 경우 시행합니다.
			printf("%s\n", table[i].text);
	}

	exit(0);
}
