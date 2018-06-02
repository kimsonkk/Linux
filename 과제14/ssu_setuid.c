#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char line[256];
	FILE *fp;
	int uid;

	if(argc < 2) {  //표준 입력으로 받아온 인자가 없을 경우 예외처리를 합니다.
		fprintf(stderr,"usage : %s file_name\n",argv[0]);
		exit(1);  //에러 메세지를 출력하고 종료합니다.
	}

	printf("initially uid = %d and euid = %d\n", getuid(), geteuid());
	fp = fopen(argv[1], "r");  //첫번째 인자를 열어옵니다.

	if(fp == NULL) {  //fopen함수가 실패할 경우 예외 처리를 합니다.
		fprintf(stderr,"first open error for %s\n",argv[1]);
		exit(1);
	}
	else {  //열어온 파일을 파일의 끝까지 줄 단위로 읽어서 표준 출력에 출력합니다.
		printf("first open successful\n");
		while(fgets(line,256,fp) != NULL)
			fputs(line, stdout);
		fclose(fp);
	}

	setuid( uid = getuid());  //현재 사용자의 uid를 읽어와서 uid를 변경합니다.
	printf("after setuid(%d):\n uid=%d and euid=%d\n",  //uid와 euid를 출력합니다.
			uid, getuid(), geteuid());
	fp = fopen(argv[1], "r");  //argv[1]의 파일을 열어옵니다.

	if(fp == NULL) { //fopen함수가 실패할 경우 예외 처리를 합니다.
		fprintf(stderr,"second open error for %s\n",argv[1]); 
		exit(1);
	}
	else {  //열어온 파일을 파일의 끝까지 줄 단위로 읽어서 표준 출력에 출력합니다.
		printf("second open seuccessful:\n");
		while(fgets(line,256, fp) != NULL)
			fputs(line, stdout);
		fclose(fp);
	}
	exit(0);
}
