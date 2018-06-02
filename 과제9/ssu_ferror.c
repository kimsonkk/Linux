#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
	struct timeval start,end;
	FILE *fp;
	int character;

	gettimeofday(&start,NULL);
	if(argc != 2) {  //인자로 file의 이름을 입력하지 않으면 에러 처리합니다.
		fprintf(stderr,"usage : %s <filename>\n",argv[0]);  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}
	if((fp = fopen(argv[1],"r"))  == NULL) {  //인자로 받은 파일 이름으로 fopen합니다.
		fprintf(stderr,"fopen error for %s\n",argv[1]);
		exit(1);
	}

	character = fgetc(fp);  //file에서 한 글자를 읽어옵니다.

	while(!feof(fp)) {  //file의 끝일 경우까지 반복합니다.
		fputc(character,stdout);  //읽어온 글자를 출력합니다.

		if(ferror(fp)) {  //에러가 있었는지 검사합니다.
			fprintf(stderr,"Error detected!!\n");
			clearerr(fp);
		}

		character = fgetc(fp);  //file에서 한 글자를 읽어옵니다.
	}
	fclose(fp);
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec-start.tv_sec+end.tv_usec/1000000.0-start.tv_usec/1000000.0);
	exit(0);
}
