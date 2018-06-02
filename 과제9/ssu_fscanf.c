#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024

int main()
{
	struct timeval start,end;
	char *fname = "ssu_test.dat";
	char name[BUFFER_SIZE];
	FILE *fp;
	int age;

	gettimeofday(&start,NULL);
	fp = fopen(fname,"r");  //fname을 읽기로 열어옵니다.
	fscanf(fp, "%s%d",name, &age);  //fp에서 name과 age를 읽어옵니다.
	fclose(fp);  //fp를 닫습니다.
	fp = fopen(fname, "w");  //fname을 쓰기모드로 열어옵니다.
	fprintf(fp, "%s is %d years old\n",name, age);  //fp에 새로운 문장으로 출력합니다.
	fclose(fp);
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
