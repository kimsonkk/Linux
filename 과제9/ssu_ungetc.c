#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/time.h>

int main()
{
	struct timeval start,end;
	char operator;  //연산자를 저장할 변수입니다.
	FILE *fp;
	int character;
	int number = 0;

	gettimeofday(&start,NULL);
	if((fp = fopen("ssu_expr.txt","r")) == NULL) {  //ssu_expr.txt파일을 읽기 모드로 읽어옵니다.
		fprintf(stderr,"fopen error for ssu_expr.txt\n");  //에러시 메세지를 출력하고 종료합니다.
		exit(1);
	}

	while(!feof(fp)) {  //파일의 끝까지 반복합니다.
		while((character = fgetc(fp)) != EOF && isdigit(character))  //파일에서 한 글자를 읽고 그 글자가 숫자일 경우 반복합니다.
			number = 10 * number + character - 48;

		fprintf(stdout, " %d\n",number);  //수를 표준 출력에 출력합니다.
		number = 0;

		if(character != EOF) {  
			ungetc(character,fp);  //읽어온 글자를 다시 되돌립니다.
			operator = fgetc(fp);  //되돌린 글자를 읽어 저장합니다.
			printf("Operator => %c\n", operator);
		}
	}

	fclose(fp);
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
