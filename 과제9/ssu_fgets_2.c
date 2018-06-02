#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_MAX 256

int main() 
{
	struct timeval start,end;
	char command [BUFFER_MAX];
	char *prompt = "Prompt>>";

	gettimeofday(&start,NULL);
	while(1) {
		fputs(prompt,stdout);  //표준 출력에 prompt를 출력합니다.
		if(fgets(command, sizeof(command), stdin) == NULL)  //표준 입력에서 한 문장을 읽어옵니다.
			break;  
		system(command);  //읽어온 문장을 실행합니다.
	}

	fprintf(stdout,"Good bye...\n");  //표준 출력에 출력합니다.
	fflush(stdout);  //버퍼에 있는 문장들을 비워줍니다.
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
