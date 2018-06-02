#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

struct ssu_id {
	char name[64];
	int id;
};

int main()
{
	struct timeval start,end;
	struct ssu_id test1,test2;
	char *fname = "ssu_exam.dat";
	FILE *fp;

	gettimeofday(&start,NULL);
	if(( fp = fopen(fname,"w")) == NULL) {  //읽기 모드로 파일을 열어옵니다.
		fprintf(stderr,"fopen error for %s\n",fname);  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	printf("Input ID>> ");
	scanf("%d",&test1.id);
	printf("Input name>> ");
	scanf("%s",test1.name);

	if(fwrite(&test1, sizeof(struct ssu_id), 1, fp) != 1) {  //fp에 ssu_id사이즈 만큼 test1을 1번 출력합니다.
		fprintf(stderr, "fwrite error\n");  //출력한 객체가 1개가 아닐경우 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	fclose(fp);  //fp를 닫습니다.

	if((fp = fopen(fname, "r")) == NULL) {  //fname파일을 읽기 모드로 열어옵니다.
		fprintf(stderr, "fopen error for %s\n",fname);  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	if(fread(&test2,sizeof(struct ssu_id), 1 , fp) != 1) {  //fp에서 ssu_id사이즈 만큼 읽어서 test2에 저장합니다.
		fprintf(stderr, "fread error\n");
		exit(1);
	}

	printf("\nID     name\n");
	printf("=================\n");
	printf("%d       %s\n",test2.id, test2.name);
	fclose(fp);
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
