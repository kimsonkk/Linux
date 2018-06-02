#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <utime.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "myfun.h"

int optcount = 0, flag_s = 0,flag_i = 0, flag_l = 0, flag_n = 0, flag_p = 0, flag_r = 0, flag_d = 0;
int pccount;

void option(int argc, char* argv[])
	/*옵션을 받아서 처리 해주는 함수입니다.
	  대문자 소문자 옵션 모두 가능하게 합니다.*/
{
	int option_t;
	while((option_t = getopt(argc,argv,"sSiIlLnNpPrRd:D:")) != -1)
	{
		switch(option_t)
		{
			case 's':
				flag_s++;
				optcount++;
				break;
			case 'S':
				flag_s++;
				optcount++;
				break;
			case 'i':
				flag_i++;
				optcount++;
				break;
			case 'I':
				flag_i++;
				optcount++;
				break;
			case 'l':
				flag_l++;
				optcount++;
				break;
			case 'L' :
				flag_l++;
				optcount++;
				break;
			case 'n':
				flag_n++;
				optcount++;
				break;
			case 'N':
				flag_n++;
				optcount++;
				break;
			case 'p':
				flag_p++;
				optcount++;
				break;
			case 'P':
				flag_p++;
				optcount++;
				break;
			case 'r':
				flag_r++;
				optcount++;
				break;
			case 'R':
				flag_r++;
				optcount++;
				break;
			case 'd':
				flag_d++;
				pccount = atoi(optarg);
				if( (pccount < 1) || (pccount > 10)) {
					fprintf(stderr,"D 옵션 인자 1 10 사이\n");
					printh();
					exit(1);
				}
				optcount++;
				break;
			case 'D':
				flag_d++;
				pccount = atoi(optarg);
				if((pccount < 1) || (pccount > 10)) {
					fprintf(stderr," D 옵션 인자 1 10 사이\n");
					printh();
					exit(1);
				}
				optcount++;
				break;
			case '?':
				exit(1);
		}
	}
}

void optcheck()
	/*받아들인 옵션에서 같은 옵션이 중복으로 들어왔는지
	  아닌지를 확인해주는 함수입니다.
	  정상적으로 들어왔다면 입력받은 옵션을 출력합니다.*/
{
	if((flag_s > 1)||(flag_i>1)||(flag_l>1)||(flag_n>1)||(flag_n>1)||(flag_p>1)||(flag_r>1)||(flag_d>1))
	{
		if(flag_s>1)
			fprintf(stderr,"s option is duplicated\n");
		if(flag_i>1)
			fprintf(stderr,"i option is duplicated\n");
		if(flag_l>1)
			fprintf(stderr,"l option is duplicated\n");
		if(flag_n>1)
			fprintf(stderr,"n option is duplicated\n");
		if(flag_p>1)
			fprintf(stderr,"p option is duplicated\n");
		if(flag_r>1)
			fprintf(stderr,"r option is duplicated\n");
		if(flag_d>1)
			fprintf(stderr,"d option is duplicated\n");
		printh();
		exit(1);
	}
	else {
		if(flag_s == 1)
			printf(" s option is on\n");
		if(flag_i == 1)
			printf(" i option is on\n");
		if(flag_l == 1)
			printf(" l option is on\n");
		if(flag_n == 1)
			printf(" n option is on\n");
		if(flag_p == 1)
			printf(" p option is on\n");
		if(flag_r == 1)
			printf(" r option is on\n");
		if(flag_d == 1)
			printf(" d option is on\n");
	}
}

void cpfile(char* src,char* Target)
	/*src에 [SOURCE]를 받고 그 파일을 [TARGET]에
	  복사하여 만들어 줍니다.*/
{
	struct stat srcstat;
	struct utimbuf time_buf;
	int fsize;
	int fd1,fd2;
	char buf;

	if((fd1 = open(src, O_RDONLY)) < 0 ) {  //[SOURCE]를 열어옵니다.
		fprintf(stderr,"src is no dir or file\n");
		printh();
		exit(1);
	}
	if((fd2 = open(Target,O_RDWR|O_CREAT|O_TRUNC,0666)) < 0) {  //[TARGET]을 만들고 이미 있다면 덮어써 줍니다.
		printf("%s\n",Target);
		fprintf(stderr,"Target creat error\n");
		printh();
		exit(1);
	}
	while(read(fd1,&buf,(size_t)1) > 0){  //[SOURCE]에서 한글자씩 [TARGET]에 복사해줍니다..
		write(fd2,&buf,(size_t)1);
	}
	if(flag_l == 1) {  //l 옵션을 사용할 경우 정보를 복사해줍니다.
		stat(src,&srcstat);
		chown(Target,srcstat.st_uid,srcstat.st_gid);
		chmod(Target,srcstat.st_mode);
		time_buf.actime = srcstat.st_atime;
		time_buf.modtime = srcstat.st_mtime;
		utime(Target,&time_buf);
	}
}

void printh()
	//사용법을 출력해주는 함수입니다.
{
	printf("usage : in case of file\n");
	printf("cp [-i/n][-l][-p]         [source][target]\n");
	printf("or cp [-s][source][target]\n");
	printf("in case of directory cp [-i/n][-l][-p][-r][-d][N]\n");
}

void printinfo(char* fname,struct stat statbuf)
	//입력받은 파일의 정보들을 출력해주는 함수입니다.
{
	struct tm *at,*mt,*ct;
	at = localtime(&statbuf.st_atime);
	mt = localtime(&statbuf.st_mtime);
	ct = localtime(&statbuf.st_ctime);
	printf("******************file info*******************\n");
	printf("파일 이름 : %s\n",fname);
	printf("데이터의 마지막 읽은 시간: %s\n",timeTostr(at));
	printf("데이터의 마지막 수정 시간: %s\n",timeTostr(mt));
	printf("데이터의 마지막 변경 시간: %s\n",timeTostr(ct));
	printf("OWNER : %s\n",getpwuid(statbuf.st_uid)->pw_name);
	printf("GROUP : %s\n",getgrgid(statbuf.st_gid)->gr_name);
	printf("file size : %ld\n",(long)statbuf.st_size);
}

char* timeTostr(struct tm *t)
	//시간의 형태로 구성되있는 구조체를 문장으로 변형해주는 함수입니다.
{
	static char s[20];
	sprintf(s,"%04d-%02d-%02d %02d:%02d:%02d",t->tm_year+1900, t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	return s;
}

void cpdir(char* src, char* Target)
	/*입력받은 [SOURCE] 디렉터리를 [TARGET]으로 복사해주는 함수입니다.
	  r 옵션을 사용할 경우 이용하는 함수입니다.*/
{
	struct dirent **namelist;
	struct stat statbuf;
	struct utimbuf time_buf;
	int count;
	int i;
	char from[1024];
	char dest[1024];

	if(access(Target,F_OK) != 0) {  //타겟 디렉터리가 없을 경우 새로 만들어줍니다.
		if(mkdir(Target,0777) < 0) {
			fprintf(stderr,"mkdir error for %s\n",Target);
			exit(1);
		}
	}
	if((count = scandir(src,&namelist,NULL, alphasort)) == -1)  //디렉터리의 정보를 스캔합니다.
	{
		fprintf(stderr,"%s Directory Scan Error : %s\n",src, strerror(errno));
		exit(1);
	}
	for(i = 0; i < count; i++) {  //디렉터리의 내부 파일의 개수만큼 반복합니다.
		sprintf(from,"%s/%s",src,namelist[i]->d_name);
		from[strlen(src)+strlen(namelist[i]->d_name)+3] = '\0';
		sprintf(dest,"%s/%s",Target,namelist[i]->d_name);
		dest[strlen(Target)+strlen(namelist[i]->d_name)+3] = '\0';
		if((!strcmp(namelist[i]->d_name, ".")) || (!strcmp(namelist[i]->d_name, "..")))
			continue;
		if(lstat(from,&statbuf) < 0) {
			fprintf(stderr,"stat error for %s\n",from);
			exit(1);
		}
		if(S_ISDIR(statbuf.st_mode)) {  //디렉터리 안에 디렉터리가 있을 경우 재귀적으로 복사해줍니다.
			cpdir(from,dest);
		}
		else
			cpfile(from,dest);  //파일일 경우 그 파일을 복사해줍니다.
		from[0] = '\0';
	}
	for( i = 0;i < count; i++)
		free(namelist[i]);
	free(namelist);
}

void cpdirps(char* src, char* Target, int pccount)
	/*입력받은 디렉터리를 복사할 경우에 사용하는 함수입니다.
	 d 옵션을 이용하여 복사할 때 사용합니다.
	 fork함수를 이용해서 프러세스를 나누어서 진행합니다.*/
{
	struct dirent **namelist;
	struct stat statbuf;
	struct utimbuf time_buf;
	int count,status;
	int i = 0;
	pid_t pid;
	char from[1024];
	char dest[1024];

	if(access(Target,F_OK) != 0) {  //[TARGET] 디렉터리가 없을 경우 만들어줍니다.
		if(mkdir(Target,0777) < 0) {
			fprintf(stderr,"mkdir error for %s\n",Target);
			exit(1);
		}
	}
	if(stat(src,&statbuf) < 0 ) {
		fprintf(stderr,"stat error for %s\n",src);
		exit(1);
	}
	if(flag_l == 1) {  //l 옵션이 있을 경우 정보를 복사해줍니다.
		chown(Target,statbuf.st_uid,statbuf.st_gid);
		chmod(Target,statbuf.st_mode);
		time_buf.actime = statbuf.st_atime;
		time_buf.modtime = statbuf.st_mtime;
		utime(Target,&time_buf);
	}
	if(( count = scandir(src, &namelist, NULL, alphasort)) == -1)
	{
		fprintf(stderr,"%s Directory Scan Error : %s\n", src, strerror(errno));
		exit(1);
	}

	i = 2;
	while((pccount != 0) && (i < count) )  //입력받은 프로세스의 숫자 혹은 디렉터리 내부의 개수만큼 반복합니다.
	{
		sprintf(from,"%s/%s",src,namelist[i]->d_name);
		from[strlen(src)+strlen(namelist[i]->d_name)+3] = '\0';
		sprintf(dest,"%s/%s",Target,namelist[i]->d_name);
		from[strlen(Target)+strlen(namelist[i]->d_name)+3] = '\0';
		if((!strcmp(namelist[i]->d_name, ".")) || (!strcmp(namelist[i]->d_name, "..")))
			continue;
		if(lstat(from,&statbuf) < 0) {
			fprintf(stderr,"stat error for %s\n",from);
			exit(1);
		}
		if(S_ISDIR(statbuf.st_mode)) {  //디렉터리 내부에 디렉터리가 있을 경우  fork함수를 이용해서 프로세스를 나누어줍니다.
			pid = fork();
			pccount--;
		}
		if(pid < 0) {  //fork함수가 에러가 났을경우 종료합니다.
			fprintf(stderr,"process error \n");
			exit(1);
		}
		else if(pid == 0) {  //자식 프로세스가 복사하는 디렉터리의 이름과 pid값을 출력하면서 복사합니다.
			printf("PID : %ld, directory : %s\n",(long)getpid(),from);
			cpdir(from,dest);
			exit(0);
		}
		else {  //부모 프로세스가 파일을 복사합니다.
			wait(&status);
			if(S_ISREG(statbuf.st_mode))
					cpfile(from,dest);
		}
		from[0] = '\0';
		i++;
	}

	if(i < count)  //프로세스 수보다 하위 디렉터리가 많을 경우 나머지는 부모 프로세스에서 복사합니다.
	{
		for(;i < count;i++) {
			sprintf(from,"%s/%s",src,namelist[i]->d_name);
			from[strlen(src)+strlen(namelist[i]->d_name)+3] = '\0';
			sprintf(dest,"%s/%s",Target,namelist[i]->d_name);
			from[strlen(dest)+strlen(namelist[i]->d_name)+3] = '\0';
			if(lstat(from,&statbuf) < 0) {
				fprintf(stderr,"stat error for %s\n",namelist[i]->d_name);
				exit(1);
			}
			if(S_ISDIR(statbuf.st_mode)) {
				printf("PID : %ld, directory : %s\n",(long)getpid(),from);
				cpdir(from,dest);
			}
			else
				cpfile(from,dest);
		}
	}
	if(lstat(src,&statbuf) < 0) {
		fprintf(stderr,"stat error for %s\n",src);
		exit(1);
	}
	for(i = 0; i < count; i++)
		free(namelist[i]);
	free(namelist);
}
