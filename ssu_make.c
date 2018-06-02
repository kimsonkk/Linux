#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <regex.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ssu_make.h"
#include "myfun.h"

#define BuffMax 1024

int main(int argc,char* argv[]) 
{
	int flag_f = 0, flag_c = 0, flag_s = 0 , flag_h = 0,flag_m = 0, flag_t = 0;  //옵션 flag를 저장할 변수입니다.
	int option_t, chdirResult, fd, slash = 0,inputT = 0,inputM = 0, includenum = 0;
	int argccount = 1;  //옵션의 갯수를 저장할 변수입니다.
	char *filename = "Makefile";  //file 이름을 저장하는 변수입니다.
	char *dirname;  //경로를 저장하는 변수입니다.
	char filein;  //open한 file에서 char단위로 읽을때 쓰는 변수입니다.
	char **fileline;  //file의 모든 내용을 담고있는 변수입니다.
	TargetList* Tlist = (TargetList*)malloc(sizeof(TargetList));  //Target의 시작과 현재 위치를 가리키는 변수
	MacroList* Mlist = (MacroList*)malloc(sizeof(MacroList));  //Macro의 시작과 현재 위치를  가리키는 변수
	dirname = getcwd(NULL,BuffMax);  //디렉초리를 저장하는 변수입니다. 초기에는 현재 작업 디렉토리를 저장합니다.
	char** Targetarr = (char**)malloc(sizeof(char*)*5);  //표준 입력으로 받은 Target을 저장하는 변수입니다
	char** Macroarr = (char**)malloc(sizeof(char*)*5);  //표준 입력으로 받은 Macro를 저장하는 변수입니다.
	char** Include = (char**)malloc(sizeof(char*)*20);  //Makefile안의 include한 파일들을 저장하는 변수입니다.
	int includecount = 0;  //include한 파일의 개수를 저장하는 변수입니다.
	char useTarget[20][20];


	/*option을 처리하기 위한 과정입니다. 인자로 받은 옵션들을
	  한가지 씩 읽어서 그에 해당하는 변수들을 1로 저장합니다.*/
	while((option_t = getopt(argc, argv, "f:c:shmt"))!= -1 )
	{
		switch(option_t)
		{
			case 'f':
				flag_f =1;
				filename = optarg;  //인자로 받은 file의 이름을 저장합니다.
				argccount += 2;
				break;
			case 'c':
				flag_c = 1;
				dirname = optarg;  //인자로 받은 디렉토리를 저장합니다.
				if((chdirResult = chdir(dirname)) < 0){
					fprintf(stderr,"make: %s: No such file or directory.\n",dirname);
					exit(1);
				}
				argccount+= 2;
				break;
			case 's':
				flag_s = 1;
				argccount++;
				break;
			case 'h':
				flag_h = 1;
				argccount++;
				break;
			case 'm':
				flag_m = 1;
				argccount++;
				break;
			case 't':
				argccount++;
				flag_t = 1;
				break;
			case '?':
				exit(1);
		}
	}

		if(0 < (fd = open(filename,O_RDONLY))) //파일 open이 성공했을 경우 문서의 내용을 읽어옵니다.
		{
			off_t filesize = lseek(fd,(off_t)0,SEEK_END);  //file의 size를 구합니다.
			lseek(fd,(off_t)0,SEEK_SET);  //file pointer를 첫부분으로 보냅니다.

			int line=0, index = 0;
			fileline = (char**)malloc(sizeof(char*)*100);
			fileline[line] = (char*)malloc(sizeof(char)*filesize);

			//file의 내용을 2차원 포인터에 저장합니다.
			while(read(fd,&filein,(size_t)1) != 0)	//file의 끝부분까지 한 글자씩 읽어옵니다.
			{

					if(filein != '\n') //file의 한 줄의 끝인지 아닌지 판단합니다.
					{
						if(filein != '#') {  //주석문을 만나면 뒤의 내용을 저장하지 않습니다.
						fileline[line][index] = filein;
						index++;
						}
						
						else {
							while(filein != '\n')
								read(fd,&filein,(size_t)1);
							lseek(fd,(off_t)-1,SEEK_CUR);
						}
					}
					else  //한 줄을 읽고 다음 줄을 저장하기 위해 동적할당을 해줍니다.
					{
						line++;
						fileline[line] = (char*)malloc(sizeof(char)*filesize);
						index = 0;
					}
			}

			//내용중에 \가 있으면 그 다음줄의 내용을 이어주어 긴 글을 처리해줍니다
			while(fileline[slash+1] != NULL)
			{
				if(isMatch("\\\\",fileline[slash]))
				{
					if(fileline[slash][strlen(fileline[slash])-1] == ' ') {  // \뒤에 공백이 오면 예외 처리를 합니다.
						fprintf(stderr,"%s:%d: *** missing separator.  Stop.\n",filename,slash+1);
						exit(1);
					}
					/* 읽은 문자에 \가 들어있다면 \를 지우고 그 다음 문장을 이전 문장 뒤에 이어주고
					   이어준 원래 문장을 없애 한 문장으로 만들어줍니다.*/
					strcat(fileline[slash], fileline[slash+1]);
					strcpy(fileline[slash+1],fileline[slash]);
					fileline[slash][0] = 0;
					for(int delete = 0; fileline[slash+1][delete] != '\0';delete++){  // \가 있던 자리는 공백으로 만듭니다.
						if(fileline[slash+1][delete] == '\\')
							fileline[slash+1][delete] = ' ';
					}
				}
				slash++;
			}

			/*읽어 들인 makefile에 include라는 단어가 없어질때까지 반복하여
			  include한 makefile들을 2차원 포인터에 계속해서 저장합니다.*/
			while(isinclude(fileline))
			{
				int incline = includeline(fileline);  //include가 포함된 줄을 저장합니다.
				char* makefile;  //include한 파일의 이름을 저장할 변수입니다.
				int startin = includecount;  //몇개의 파일을 include했는지 저장하는 변수입니다.
				strtok(fileline[incline]," ");
				while(makefile = strtok(NULL," "))  //include한 파일의 이름을 배열에 저장합니다.
				{
					Include[includecount] = (char*)malloc(sizeof(char)*10);
					Include[includecount++] = makefile;
				}
				fileline[incline][0] = '\0';  //include가 포함된 줄의 내용을 지웁니다.
				int endin = includecount;  //저장한 파일을 세아리기 위한 변수입니다.

				/*저장한 makefile을 하나씩 open해서 저장한 2차원 배열뒤에 파일 하나씩 읽어 들여
				 저장합니다.*/
				for(int inindex = startin; inindex < (endin-startin);inindex++)
				{
					if((fd = open(Include[inindex],O_RDONLY)) >0)
					{
						int lastindex = 0;
						fileline[line] = (char*)malloc(sizeof(char)*40);
						while(read(fd,&filein,(size_t)1) != 0)
						{
							if(filein != '\n')
							{
								if(filein != '#') {
									fileline[line][lastindex] = filein;
									lastindex++;
								}
								else {
									while(filein != '\n')
										read(fd,&filein,(size_t)1);
									lseek(fd,(off_t)-1,SEEK_CUR);
								}
							}
							else
							{
								fileline[line][lastindex] = '\0';
								line++;
								fileline[line] =(char*)malloc(sizeof(char)*40);
								lastindex = 0;
							}
						}
					}
					else
					{
						fprintf(stderr,"make: %s: No such file or directory.\n",Include[inindex]);
						exit(1);
					}
				}
			}

			/*입력받은 Target과 Macro를 배열에 저장하고 만약 인자로 받은 
			  Target이나 Macro의 개수가 5개를 넘으면 에러 메세지를 출력하고
			  종료합니다.*/
			for(int aindex = argccount; aindex < argc ; aindex++)
			{
				if(inputM >= 5)
				{
					fprintf(stderr,"입력한 Macro가 너무 많습니다\n");
					exit(1);
				}
				if(inputT >= 5)
				{
					fprintf(stderr,"입력한 Target이 너무 많습니다\n");
				}
				if(isMatch("=",argv[aindex])) {
					Macroarr[inputM] = (char*)malloc(sizeof(char)*40);
					Macroarr[inputM] = argv[aindex];
					inputM++;
				}
				else {
					Targetarr[inputT] = (char*)malloc(sizeof(char)*40);
					Targetarr[inputT] = argv[aindex];
					inputT++;
				}
			}


			/*include를 포함하여 읽어들인 모든 파일에 대해서 만든 
			  링크드 리스트 구조체에 저장하는 과정입니다.*/
			for(int fline = 0;fline < line;) 
			{
				if(fileline[fline][0] == ' '){  //첫 글자가 공백으로 시작하면 프로그램을 종료합니다
					fprintf(stderr,"%s:%d: *** missing separator.  Stop.",filename, fline+1);
					exit(1);
				}

				int findex = 0;
				if(isMatch(":",fileline[fline]))  //Target과 Dependency와 Command를 저장합니다.
				{
					TargetNode* Tnode = (TargetNode*)malloc(sizeof(TargetNode));
					Tnode->Dep = NULL;
					Tnode->Com = NULL;
					DepNode* Dcur = (DepNode*)malloc(sizeof(DepNode));  //Target구조체 안에 Dependnecy를 저장하기 위한 cursor입니다.
					ComNode* Ccur = (ComNode*)malloc(sizeof(ComNode));  //Target구조체 안에 Command를 저장하기 위한 cursor입니다.
					insT(Tlist,Tnode);  //Target을 관리하기 위한 구조체에 저장합니다.
							
					Tlist->cur->Target = (char*)malloc(sizeof(char)*20);
					char* jamggan = strtok(fileline[fline]," :");  //Macro를 처리하기 위해 잠시 저장하는 변수입니다.
					if(isMatch("\\$",jamggan))  //Target에 Macro가 사용됬으면 처리해줍니다.
					{
						/*$(Macro)로 저장된 Target을 Macro구조체 링크드 리스트를 조회해서
						  만약 Macro가 아니라면 예외처리를 하고 아니라면 Value의 값으로 치환해서
						  저장해줍니다.*/
						strcpy(jamggan,jamggan+2);
						int i = 0;
						while(jamggan[i])
							i++;
						jamggan[i-1] = '\0';
						Mlist->cur = Mlist->head;
						if(isMacro(Mlist,jamggan) == false) {
							fprintf(stderr,"make: %d Macro error\n",fline+1);
							exit(1);
						}
					
						MacroNode* inom =  findMacro(Mlist,jamggan);
						Tlist->cur->Target = inom->Value;
					}
					else  //Macro가 없다면 Target으로 바로 저장합니다.
						Tlist->cur->Target = jamggan;
					Tlist->cur->line = fline+1;
					char* dep;
					
					/*Target을 저장하고 만일 : 뒤가 비어있지 않다면 모든 문장들을 Target구조체 안에
					  Dep이라는 링크드 리스트에 하나씩 저장해줍니다.*/
					while((dep = strtok(NULL," :\t")) )  // Dependency가 NULL일때까지 반복합니다.
					{
						if(isMatch("\\$",dep))  //만일 Macro가 사용되었다면 그 매크로를 처리하고 저장하기 위한 과정입니다.
						{
							strcpy(dep,dep+2);
							int i = 0;
							while(dep[i])
								i++;
							dep[i-1] = '\0';
							Mlist->cur = Mlist->head;
							if(isMacro(Mlist,dep) == false) {
								fprintf(stderr,"3make: %d: Macro error.\n",fline+1);
								exit(1);
							}
							MacroNode* inom = findMacro(Mlist,dep);
							dep = inom->Value;
						}
						DepNode* Dnode = creatDep(dep);
						if(Tlist->cur->Dep == NULL) {  //현재의 Target의 Dep이 없다면 처음에 넣어줍니다.
							Tlist->cur->Dep = Dnode;
							Dcur = Tlist->cur->Dep;
						}
						else {  //만일 Target구조체 안에 이미 Dependency가 하나 이상있다면 가장 뒤에 저장합니다.
							Dcur->next = Dnode;
							Dcur = Dcur->next;
						}
					}
					fline++;
					if(fileline[fline][0] == ' ') {  //첫 문장이 공백이라면 에러 메세지를 출력하고 종료합니다.
						fprintf(stderr,"%s:%d: *** missing separator.  Stop.\n",filename,fline+1);
						exit(1);
					}
					/*Target을 저장하고 그 다음 문장이 TAB으로 시작하면 그 문장을 Command로 인식하여
					  Target구조체의 Com링크드 리스트에 저장합니다.*/
					while(isMatch("\t",fileline[fline]) && fline<line ) {
						ComNode* Cnode;
						char* iamcom = strtok(fileline[fline],"\t");
						//Command에 Macro가 사용되었다면 그 Macro를 처리하고 저장합니다.
						if(isMatch("\\$",iamcom))
						{
							if(isMatch("@",iamcom))  //내부 매크로로 $@를 현재 Target으로 치환합니다.
							{
								char* nohwak = (char*)malloc(sizeof(char)*filesize);
								char* left = (char*)malloc(sizeof(char)*filesize);
								int hu = 0;
								while(iamcom[hu] != '@')
									hu++;
								if(hu == 1)
									left[0] = '\0';
								else {
									strncpy(left,iamcom,hu-1);
									left[hu-1] = '\0';
								}
								strcpy(iamcom,iamcom+hu+1);
								nohwak = Tlist->cur->Target;
								strcat(left,nohwak);
								strcat(left,iamcom);
								strcpy(iamcom,left);
								left[strlen(left)] = '\0';
								Cnode = creatCom(left,fline);
								//free(left);
							}
							if(isMatch("\\*",iamcom))  //내부 매크로로 $*을 확장자가 없는 현재 Target으로 치환합니다.
							{
								char* yeshwak = (char*)malloc(sizeof(char)*filesize);
								char* left = (char*)malloc(sizeof(char)*filesize);
								int hu = 0;
								while(iamcom[hu] != '*')
									hu++;
								if(hu == 1)
									left[0] = '\0';
								else {
									strncpy(left,iamcom,hu -1);
									left[hu-1] = '\0';
								}
								strcpy(iamcom,iamcom+hu+1);
								strcpy(yeshwak,Tlist->cur->Target);
								int dot = 0;
								if(isMatch(".",yeshwak)) {  //현재 Target에 .이 있다면 확장자를 제거해줍니다
									while(yeshwak[dot] != '.')  
										dot++;
									yeshwak[dot] = '\0';
								}
								strcat(left,yeshwak);
								strcat(left,iamcom);
								strcpy(iamcom,left);
								left[strlen(left)] = '\0';
								Cnode = creatCom(left,fline);
							}

							if(isMatch("\\$",iamcom))  //내부 매크로가 아닌 Macro구조체에서 찾아서 매크로를 처리해줍니다.
							{
								char* last = (char*)malloc(sizeof(char)*filesize);
								int w = 0;
								while(iamcom[w] != '\0') { 
									/*Command 문장에서 $(macro)가 있는 부분을 찾아서 Macro가 사용되기
									  이전 문장과 매크로 그 이후 문장으로 나누고 Macro를 Value로 치환하고
									  이전 문장과 Value, 이후 문장을 다시 하나의 문장을 합쳐서 저장합니다.
									 */
									int hu = 0;
									if(isMatch("\\$",iamcom)) {
										char* left = (char*)malloc(sizeof(char)*filesize);
										char* right = (char*)malloc(sizeof(char)*filesize);
										while(iamcom[hu] != '$')
											hu++;
										if(hu == 0)
											left[0] = '\0';
										else {
											strncpy(left,iamcom,hu);
											left[hu] = '\0';
										}
										strcpy(iamcom+hu,iamcom+hu+2);
										int i = 0;
										while(iamcom[i] != ')')
											i++;
										iamcom[i] = ' ';
										char* fortok = (char*)malloc(sizeof(char)*filesize);
										strcpy(fortok,iamcom);
										char* jjom = strtok(fortok+hu," ");
										i = hu;
										while(iamcom[i] != ' '){
											iamcom[i] = ' ';
											i++;
										}
										strcpy(right,iamcom+i);
										Mlist->cur = Mlist->head;
										if(isMacro(Mlist,jjom) == false) {
											fprintf(stderr,"%d: Macro error.\n",fline+1);
											exit(1);
										}
										MacroNode* inom = findMacro(Mlist,jjom);
										jjom = inom->Value;
										iamcom = trimforcom(iamcom);
										strcat(left,jjom);
										strcat(left,right);
										strcpy(iamcom,left);
										strcpy(last,iamcom);
										last[strlen(last)] = '\0';
									}
									w++;
								}
								Cnode = creatCom(last,fline);
							}
						}
						else {
							iamcom[strlen(iamcom)] = '\0';
							Cnode = creatCom(iamcom, fline);
						}

						if(Tlist->cur->Com == NULL) {
							Tlist->cur->Com = Cnode;
							Ccur = Tlist->cur->Com;
						}
						else {
							Ccur->next = Cnode;
							Ccur = Ccur->next;
						}
						fline++;
						if(fileline[fline][0] == ' ') {
							fprintf(stderr,"%s:%d: *** missing separator.  Stop.\n",filename, fline+1);
							exit(1);
						}
					}
				}

				//읽은 문장에 =이 포함되어 있다면 그 문장은 Macro구조체에 저장합니다
				else if(isMatch("=",fileline[fline]))
				{
					MacroNode* Mnode;
					if(isMatch("?=",fileline[fline])) {  //Macro가 ?=로 저장되면 그 Macro의 Value가 바뀔수 있다고 저장합니다.
						char* m = strtok(fileline[fline], " ?=");
						char* v = strtok(NULL," ?=\\\t");
						char state = 'c';  //변환 가능하다는 의미입니다.
						char* ifadd;
						if(isMatch("\"",v)) {  //Value가 ""안에 있으면 그 안에 공백이 있더라도 하나의 value로 저장합니다.
							while(ifadd = strtok(NULL," ?=\t")) {
							char* add = (char*)malloc(sizeof(char)*40);
							add = v;
							add[strlen(add)] = ' ';
							Mnode = creatMacro(m , add, fline+1 ,state);
							for(int insertM = 0; insertM < inputM; insertM++)
							{
								if(isMatch(Mnode->Macro,Macroarr[insertM])) { //만약 표준 입력에서 받은 Macro가 있다면 그 Value로 바꿔 저장합니다.
									strtok(Macroarr[insertM],"=");
									char* nv = strtok(NULL,"=");
									Mnode->Value = nv;
									state = 'n';
									Mnode->state = state;
									int mblank = 0;
									Macroarr[insertM][0] = '\0';
								}
							}
							}
						}
						else {  //Value가 ""가 아니라면 공백없이 받은 값으로 저장합니다
							Mnode = creatMacro(m, v, fline+1 ,state);
							for(int insertM = 0; insertM < inputM;insertM++)
							{
								if(isMatch(Mnode->Macro,Macroarr[insertM])) {
									strtok(Macroarr[insertM],"=");
									char* nv = strtok(NULL, " ");
									Mnode->Value = nv;
									state = 'n';
									Mnode->state = state;
									int mblank = 0;
									Macroarr[insertM][0] = '\0';
								}
							}
						}
					}
					else {  //Macro의 Value가 재정의 할수 없는 값으로 저장합니다.
						char* m = strtok(fileline[fline]," =?");
						char* v = strtok(NULL, " ?=\t");
						char* ifadd;
						if(isMatch("\"",v)) {  //Macro의 Value가 ""안에 있으면 공백을 포함하여 저장합니다.
							while(ifadd = strtok(NULL, " ?=\\\t")) {
								char* add = (char*)malloc(sizeof(char)*40);
								add = v;
								add[strlen(add)] = ' ';
								Mnode = creatMacro(m,add, fline+1 ,'n');
								for(int exitM = 0; exitM< inputM; exitM++)
								{
									if(isMatch(Mnode->Macro,Macroarr[exitM]))
									{
										fprintf(stderr,"%s Macro를 재정의할 수 없습니다. line : %d\n",Mnode->Macro,fline+1);
										exit(1);
									}
								}
							}
						}
						else{  //Macro의 Value가 ""이 없다면 공백 없이 저장합니다.
							Mnode = creatMacro(m,v,fline+1 ,'n');
							for(int exitM = 0; exitM< inputM; exitM++)
							{
								if(isMatch(Mnode->Macro, Macroarr[exitM]))
								{
									fprintf(stderr,"%s Macro를 재정의할 수 없습니다. line : %d\n",Mnode->Macro,fline+1);
									exit(1);
								}
							}
						}
					}
					insM(Mlist, Mnode);
					fline++;
					if(fileline[fline][0] == ' ') {
						fprintf(stderr,"%s:%d: *** missing separator.  Stop.\n",filename,fline+1);
						exit(1);
					}
				}
				else
					fline++;
				if(fileline[fline][0] == ' ') {
					fprintf(stderr,"%s:%d: *** missing separator.  Stop.n",filename, fline+1);
					exit(1);
				}
			}

			Tlist->cur = Tlist->head;

			if(Tlist->head == NULL) {
				fprintf(stderr,"make: *** No targets. Stop.\n");
				exit(1);
			}

			close(fd);  //open한 파일을 닫습니다.
		}  

		else
		{  //검색하는 file이 없을 때 오류 메세지를 출력합니다.
			printf("make: %s: No such file or directory\n",filename);
			exit(1);
		}



		//표준 입력으로 입력받은 Macro를 저장합니다.
		int inputMindex = 0;
		if(Macroarr[0] != NULL)
		{
			Mlist->cur = Mlist->head;
			while(Macroarr[inputMindex] != NULL)  /*표준 입력을 받은 Macro 중에서 존재하던  
													Macro를 처리하고 남은 Macro를 저장합니다.*/
			{
				char* findmacro = strtok(Macroarr[inputMindex],"=");
				char* findvalue = strtok(NULL,"=");
				if(findmacro == NULL) {
					inputMindex++;
					continue;
				}
				if(isMatch(" ",findvalue)){  //Value에 ""가 있으면 공백을 포함해 처리해줍니다.
					char* chvalue = (char*)malloc(sizeof(char)*40);
					chvalue[0] = '\"';
					strcpy(chvalue+1,findvalue);
					chvalue[strlen(findvalue)+1] = '\"';
					findvalue = chvalue;
				}
				bool temp = isMacro(Mlist,findmacro);
				if(temp)
				{
					MacroNode* M = findMacro(Mlist,findmacro);  //=으로 저장된 Macro를 재정의 하려하면 에러메세지를 출력하고 종료합니다.
					if(M->state == 'n') {
						fprintf(stderr,"'%s' Macro를 지정할수 없습니다 \n",M->Macro);
						exit(1);
					}
					else {
						M->Value = findvalue;
					}
				}
				else
				{
					MacroNode* M = creatMacro(findmacro,findvalue, 0,'n');
					while(Mlist->cur != NULL)
						Mlist->cur = Mlist->cur->next;
					Mlist->cur = (MacroNode*)malloc(sizeof(MacroNode));
					insM(Mlist,M);
				}

				inputMindex++;
			}
			Mlist->cur = Mlist->head;
		}

		//Makefile에서 같은 이름의 Target이 두 개 이상 존재할 경우 에러 메세지를 출력하고 종료합니다.
		Tlist->cur = Tlist->head;
		if(Tlist->head ==NULL) {
			fprintf(stderr,"make: *** No targets  Stop.\n");
			exit(1);
		}
		while(Tlist->cur != NULL)  /*Target 링크드 리스트를 관리하기 위한 구조체를 처음부터
									 끝까지 순환하며 같은 이름을 가진 Target이 2개 이상인지 확인합니다.*/
		{
			int doubletarget = 0;
			char* errorT = Tlist->cur->Target;
			TargetNode* tag = Tlist->cur;
			while(tag != NULL)
			{
				if(strcmp(tag->Target,errorT) == 0)
					doubletarget++;
				if(doubletarget > 1) {
					fprintf(stderr,"%s Target이 중복되었습니다\n",errorT);
					exit(1);
				}
				tag = tag->next;
			}
			Tlist->cur = Tlist->cur->next;
		}
		Tlist->cur = Tlist->head;

		//표준 입력에서 Target을 지정해주지 않으면 제일 상위의 Target을 실행합니다.
		if((flag_h != 1) && (flag_m != 1) && (flag_t != 1)) {  //option으로 h, m과 t를 받지 않은 경우 실행합니다.
		if(Targetarr[0] == NULL)  //Target을 지정해주지 않은 경우
		{
			/*배열을 하나 만들고 그 배열에 Target의 Dependency가 만약 다른 Target일 경우
			  그 Dependency를 저장하고 순환 검사에 사용한다.*/
			int magimak = 0,flag = 0;
			if(Tlist->head != NULL) 
			{
				if(access(Tlist->head->Target,F_OK) !=0) {  //Target이 디렉토리에 없는 경우입니다.
					strcpy(useTarget[magimak],Tlist->head->Target);  //순환검사를 위해 Dependency를 저장합니다.
					DepNode* Dlist = Tlist->head->Dep;
					while(Dlist != NULL)  //Target의 Dependency를 모두 확인합니다.
					{
						makeDep(Tlist,Tlist->cur,Dlist->Dependency,useTarget,magimak,&flag,flag_s);
						Dlist = Dlist->next;
					}
					if(Tlist->head->Com != NULL)  //Target의 Command를 모두 실행합니다.
					{
						ComNode* Clist = Tlist->head->Com;
						while(Clist != NULL) {
							if(flag_s != 1)
								printf("%s\n",Clist->Command);
							system(Clist->Command);
							Clist = Clist->next;
						}
					}
					else
					{
						fprintf(stderr,"make: *** No rule to  make target '%s'.  Stop.\n", Tlist->head->Target);
						exit(1);
					}
				}
				else  //Target이 디렉토리에 있는 경우 Dependency와 시간을 비교합니다.
				{
					strcpy(useTarget[magimak],Tlist->head->Target);
					DepNode* Dlist = Tlist->head->Dep;
					struct stat Tst;
					stat(Tlist->head->Target,&Tst);
					struct stat Dst;
					int T_flag = 0;
					while(Dlist != NULL) {
						if(access(Dlist->Dependency,F_OK) == 0)
							stat(Dlist->Dependency,&Dst);
						else {
							T_flag = 1;
							break;
						}
						if(difftime(Tst.st_mtime,Dst.st_mtime) < 0)  /*Trget과 각각의 Dependency의 시간을 비교해서
																	   하나의 Dependency라도 Target보다 수정 시간이 
																	   늦다면 Target을 새로 만듭니다*/
							T_flag = 1;
						Dlist = Dlist->next;
					}
					Dlist = Tlist->head->Dep;
					if(T_flag == 1)
					{
						while(Dlist != NULL)
						{
							makeDep(Tlist,Tlist->cur,Dlist->Dependency, useTarget,magimak,&flag,flag_s);
							Dlist = Dlist->next;
						}
						if(Tlist->head->Com != NULL)
						{
							ComNode* Clist = Tlist->head->Com;
							while(Clist != NULL) {
								if(flag_s != 1)
									printf("%s\n",Clist->Command);
								system(Clist->Command);
								Clist = Clist->next;
							}
						}
					}
					else if(T_flag == 0)   //그게 아니라면 Command를 수행하지 않습니다.
					{

						printf("make: '%s' is up to date.\n",Tlist->head->Target);
					}
				}
			}
			else
			{
				printf("make: No Target.  Stop\n");
				exit(1);
			}
		}
		else  /*표준 입력에서 입력받은 Target들을 실행합니다.
			    입력 받은 Target들만 실행 시키고 그 과정은 위의
			   최상위 Target을 실행시키는 과정과 동일합니다.*/
		{
			int makeindex = 0,flag = 0;
			while(Targetarr[makeindex] != NULL)
			{
				if(access(Targetarr[makeindex],F_OK) != 0) {
					int magimak = 0;
					TargetNode* makeTnode;
					if(isTarget(Tlist,Targetarr[makeindex]))
						makeTnode = findTarget(Tlist,Targetarr[makeindex]);
					if(isTarget(Tlist,Targetarr[makeindex]))
					{
						strcpy(useTarget[magimak],makeTnode->Target);
						DepNode* Dlist = makeTnode->Dep;
						while(Dlist != NULL)
						{
							makeDep(Tlist,makeTnode,Dlist->Dependency,useTarget,magimak,&flag,flag_s);
							Dlist = Dlist->next;
						}
						if(makeTnode->Com != NULL)
						{
							ComNode* Clist = makeTnode->Com;
							while(Clist != NULL)
							{
								if(flag_s != 1)
									printf("%s\n",Clist->Command);
								system(Clist->Command);
								Clist = Clist->next;
							}
						}
					}
					else
					{
						fprintf(stderr,"make: *** No rule to  make target '%s'. Stop\n",Targetarr[makeindex]);
						exit(1);
					}
					makeindex++;
				}
				else
				{
					int magimak = 0;
					TargetNode* makeTnode;
					if(isTarget(Tlist,Targetarr[makeindex]))
						makeTnode = findTarget(Tlist,Targetarr[makeindex]);
					if(isTarget(Tlist,Targetarr[makeindex]))
					{
						strcpy(useTarget[magimak],makeTnode->Target);
						DepNode* Dlist = makeTnode->Dep;
						struct stat Tst;
						stat(makeTnode->Target,&Tst);
						struct stat Dst;
						int T_flag = 0;
						while(Dlist != NULL) {
							if(access(Dlist->Dependency,F_OK) == 0)
								stat(Dlist->Dependency,&Dst);
							else{
								T_flag =1;
								break;
							}
							if(difftime(Tst.st_mtime,Dst.st_mtime) < 0)
								T_flag = 1;
							Dlist = Dlist->next;
						}
						Dlist = makeTnode->Dep;
						if(T_flag == 1)
						{
							while(Dlist != NULL)
							{
								makeDep(Tlist,makeTnode,Dlist->Dependency,useTarget,magimak,&flag,flag_s);
								Dlist = Dlist->next;
							}
							if(makeTnode->Com != NULL)
							{
								ComNode* Clist = makeTnode->Com;
								while(Clist != NULL) {
									if(flag_s != 1)
										printf("%s\n", Clist->Command);
									system(Clist->Command);
									Clist = Clist->next;
								}
							}
						}
						else if(T_flag ==0)
						{
							printf("make: '%s' is up to date.\n",makeTnode->Target);
						}
					}
					makeindex++;
				}
			}
		}
		}
		else
		{
			if(flag_h == 1)  //option으로 h가 들어오면 사용법을 출력합니다.
			{
				printf("Usage : ssu_make [Target] [Option] [Macro]\n");
				printf("Option:\n");
				printf("-f <file>		Use <file> as a makefile.\n");
				printf("-c <directory>  Change to directory <directory> before reading the makefiles.\n");
				printf("-s				Do not print the commands as they are excuted.\n");
				printf("-h				Print usager\n");
				printf("-m 				Print macro list\n");
				printf("-t				print tree\n");
				exit(0);
			}
			if(flag_m == 1)  //option으로 m이 들어오면 macro를 출력합니다.
			{
				printf("--------------------macro list-------------------\n");
				MacroNode* pMacro = Mlist->head;
				while(pMacro != NULL)
				{
					printf("%s -> %s\n",pMacro->Macro,pMacro->Value);
					pMacro = pMacro->next;
				}
			}
			if(flag_t == 1)  //option으로 t가 들어오면 Target과 Dependency구조를 출력합니다.
			{
				printTree(Tlist);
			}
		}

		exit(0);
}

