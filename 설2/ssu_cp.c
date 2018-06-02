#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "myfun.h"

int optcount,flag_s, flag_i, flag_l,flag_n, flag_p, flag_r,flag_d;
int pccount;

int main( int argc, char* argv[])
{
	struct stat file_info,Target_info;
	char file[BUFSIZ];
	option(argc,argv);
	optcheck();
	char* src = argv[argc-2];
	char* Target = argv[argc-1];
	char opt_i;

	if(argc == 1) {  //[SOURCE]와 [TARGET]이 주어지지 않았을 경우 종료합니다.
		printf("No source and target\n");
		printh();
		exit(1);
	}
	if((strlen(src) > PATH_MAX) || (strlen(Target) > PATH_MAX)) {  //경로의 길이가 PATH_MAX보다 긴 경우 에러 처리합니다.
		if(strlen(src) > PATH_MAX)
			printf("ssu_cp: [SOURCE] is too long\n");
		if(strlen(Target) > PATH_MAX)
			printf("ssu_cp: [TARGET] is too long\n");
		printh();
		exit(1);
	}


	//src이나 Target이 없을 경우 종료합니다.
	if((src[0] == '-') || (Target[0] == '-') || (argc -2 == 0)){
		if(src[0] == '-')
			printf("No Target\n");
		if(argc -2 == 0)
			printf("No source\n");
		else if(Target[0] == '-')
			printf("No Source\n");
		printh();
		exit(1);
	}
	printf("target : %s\nsrc : %s\n",Target,src);

	//Target과 SOURCE가 같은 경우 종료합니다.
	if(strcmp(src,Target) == 0) {
		printf("ssu_cp: [SOURCE] and [TARGET] is same\n");
		printh();
		exit(1);
	}

	//SOURCE가 없을 경우 종료합니다.
	if(access(src,F_OK) < 0) {
		fprintf(stderr,"ssu_cp: %s: No such file or directory\n",src);
		printh();
		exit(1);
	}

	//n option and Target이 존재할 경우 종료합니다.
	if((flag_n == 1) && (access(Target,F_OK) == 0))
		exit(0);

	if(stat(src, &file_info) < 0) {
		fprintf(stderr,"stat error\n");
		printh();
		exit(1);
	}
	if(access(Target,F_OK) == 0) {  // [SOURCE]와 [TARGET]이 같은 파일일 경우 예외처리합니다.
		if(stat(Target,&Target_info) < 0) {
			fprintf(stderr,"stat error for %s\n",Target);
			exit(1);
		}
		if(file_info.st_ino == Target_info.st_ino) {
			fprintf(stderr,"ssu_cp: [SOURCE] [TARGET] are same.\n");
			exit(1);
		}
	}

	if(S_ISDIR(file_info.st_mode)) {
		//[SOURCE]가 디렉터리일 경우입니다.
		if(optcount == 0) {  //옵션없이 복사하려 할 경우 에러 메세지를 출력하고 종료합니다.
			printf("ssu_cp: Can't copy directory without option\n");
			printh();
			exit(1);
		}
		if((flag_d == 1) && (flag_r == 1)) {  //d 옵션과 r 옵션을 같이 사용하려고 하면 종료합니다.
			printf("ssu_cp: Can't use both d option and r option\n");
			printh();
			exit(1);
		}
		if((flag_d == 0) && (flag_r == 0)) {  //d 옵션과 r 옵션 없이 디렉터리를 복사하려 하면 종료합니다.
			printf("ssu_cp: Can't copy directory without d option or roption\n");
			printh();
			exit(1);
		}
		if((flag_i ==1) && (flag_n == 1)) {  //i 와 n옵션을 같이 사용하려 하면 에러 처리합니다.
			printf("ssu_cp: Can't use both i option and n option\n");
			printh();
			exit(1);
		}
		if(flag_s == 1) {
			printf("Source가 디렉터리일 경우 s 옵션은 생략합니다\n");
		}
		//[SOURCE]를 복사합니다.
		if(flag_l == 1) {  //l옵션의 경우 정보를 복사해 [TARGET]에 저장합니다.
			struct utimbuf time_buf;
			chown(Target,file_info.st_uid,file_info.st_gid);
			chmod(Target,file_info.st_mode);
			time_buf.actime = file_info.st_atime;
			time_buf.modtime = file_info.st_mtime;
			utime(Target,&time_buf);
		}
		if(flag_r == 1) {  //r 옵션을 사용할 때의 복사입니다.
			if(flag_i == 1) {
				if(access(Target,F_OK) == 0) {
					printf("%s\n",src);
					printf("overwrite %s (y,n)?",Target);
					scanf("%c",&opt_i);
					if(opt_i != 'y')
						exit(0);
				}
			}
			if(flag_p == 1) 
				printinfo(src,file_info);
			cpdir(src,Target);
		}
		if(flag_d == 1) {  //d 옵션을 사용할 때의 복사입니다.
			if(flag_i == 1) {
				if(access(Target,F_OK) == 0) {
					printf("%s\n",src);
					printf("overwrite %s (y,n)?",Target);
					scanf("%c",&opt_i);
					if(opt_i != 'y')
						exit(0);
				}
			}
			if(flag_p == 1)  //p 옵션은 [SOURCE]의 정보를 출력합니다.
				printinfo(src,file_info);
			cpdirps(src,Target,pccount);
		}
	}
	//[SOURCE]가 파일일 경우의 복사입니다.
	else {
		if(access(src,F_OK) < 0) {  //[SOURCE]가 없을 경우 에러 처리합니다.
			fprintf(stderr,"ssu_cp: %s: No such file or directory\n",src);
			printh();
			exit(1);
		}
		if((flag_d == 1) || (flag_r == 1)) {  //d 옵션과 r옵션을 파일 복사에 사용하면 에러 처리합니다.
			if(flag_d == 1)
				printf("ssu_cp: d option use for Directory\n");
			if(flag_r == 1)
				printf("ssu_cp: r option use for Directory\n");
			exit(1);
		}
		if((flag_i ==1) && (flag_n == 1)) {  //i 와 n옵션을 같이 사용하려 하면 에러 처리합니다.
			printf("ssu_cp: Can't use both i option and n option\n");
			printh();
			exit(1);
		}
		if((flag_s == 1) && (optcount > 1)) {  //s 옵션을 다른 옵션과 사용하려 하면 에러 처리합니다.
			printf("ssu_cp: Can't use s option with others\n");
			printh();
			exit(1);
		}
		if(flag_s == 1) {  //s 옵션이 오면 symbolik링크를 만들어줍니다.
			symlink(src,Target);
			exit(0);
		}
		if(flag_p == 1) {
			printinfo(src,file_info);
		}
		if(flag_i == 1) {
			if(access(Target,F_OK) == 0) {
			printf("%s\n",src);
			printf("overwrite %s (y,n)?",Target);
			scanf("%c",&opt_i);
			if(opt_i != 'y')
				exit(0);
			}
		}
		cpfile(src,Target);
	}
	exit(0);
}
