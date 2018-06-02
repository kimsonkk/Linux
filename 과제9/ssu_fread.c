#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

struct ssu_pirate {
	unsigned long booty;
	unsigned int beard_length;
	char name[123];
};

int main()
{
	struct timeval start,end;
	struct ssu_pirate blackbeard = {950,48,"Edward Teach"},pirate;
	char *fname = "ssu_data";
	FILE *fp1, *fp2;

	gettimeofday(&start,NULL);
	if((fp2 = fopen(fname,"w")) == NULL ) {  //fname의 파일을 쓰기 모드로 열어옵니다.
		fprintf(stderr,"fopen error\n");  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	if(fwrite(&blackbeard, sizeof(struct ssu_pirate), 1, fp2) != 1) {  //fp2에 ssu_pirate사이즈 만큼 blackbeard를 출력합니다.
		fprintf(stderr,"fwrite error\n");
		exit(1);
	}

	if(fclose(fp2)) {  //fp2를 닫습니다.
		fprintf(stderr,"fclose error\n");
		exit(1);
	}

	if((fp1 = fopen(fname,"r")) == NULL) {  //fname의 파일을 읽기 모드로 열어옵니다.
		fprintf(stderr,"fopen error\n");  //에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	if(fread(&pirate,sizeof(struct ssu_pirate), 1, fp1) != 1) {  //fp1에 ssu_pirate사이즈 만큼 읽어서 pirate에 저장합니다.
		fprintf(stderr,"fread error\n");
		exit(1);
	}

	if(fclose(fp1)) {  //fp1을 닫습니다.
		fprintf(stderr,"fclose error\n");
		exit(1);
	}

	printf("name = \"%s\" booty=%lu beard_length=%u\n",pirate.name, pirate.booty, pirate.beard_length);
	gettimeofday(&end, NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}
