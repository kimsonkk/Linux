#include <ctype.h>
#include <regex.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "myfun.h"
#include "ssu_make.h"

bool usedTarget(char useTarget[20][20], char* Target)
{
	/*인자로 받은 useTarget배열에 Target이 있는지 없는지 
	검사하여 bool형태로 반환해주는 함수입니*/
	bool res = false;
	for(int i = 0; i < 20; i++)
	{
		if(strcmp(Target, useTarget[i]) ==0) {
			res = true;
			return res;
		}
	}
	return res;
}
ComNode* creatCom(char* com, int line)
{
	/*인자로 받은 com과 line을 이용해서 ComNode구조체에 저장하여
	  만든 구조체를 반환해주는 함수입니다.*/
	ComNode* res = (ComNode*)malloc(sizeof(ComNode));
	res->Command = com;
	res->cline = line;
	res->next = NULL;
	return res;
}

DepNode* creatDep(char* dep)
{
	/*인자로 받은 dep을 이용해서 DepNode구조체에 저장하여
	  만든 구조체를 반환해주는 함수입니다.*/
	DepNode* res = (DepNode*)malloc(sizeof(DepNode));
	res->Dependency = dep;
	res->next = NULL;
	return res;
}

MacroNode* creatMacro(char* macro, char* value, int mline , char state)
{
	/*인자로 받은 macro와 value, 그 매크로가 있는 line, macro의 상태를
	  MacroNode에 저장하여 그 구조체를 반환해주는 함수입니다.*/
	MacroNode* res = (MacroNode*)malloc(sizeof(MacroNode));
	res->Macro = macro;
	res->Value = value;
	res->mline = mline;
	res->state = state;
	res->next = NULL;
	return res;
}

void insT(TargetList* Tlist, TargetNode* node)
{
	/*인자로 TargetList와 TargetNode를 받아서 TargetList에 
	  TargetNode를 제일 뒤에 추가해주는 함수입니다. */
	if(Tlist->head == NULL) {
		Tlist->head = node;
		Tlist->cur = node;
	}

	else {
		Tlist->cur->next = node;
		Tlist->cur = node;
	}
}

void insM(MacroList* Mlist, MacroNode* node)
{
	/*인자로 MacroList와 MacroNode를 받아서 MacroList에
	  MacroNode를 제일 뒤에 추가해주는 함수입니다. */
	if(Mlist->head == NULL) {
		Mlist->head = node;
		Mlist->cur = node;
	}
	else {
		Mlist->cur->next = node;
		Mlist->cur = node;
	}
}

bool isTarget(TargetList* Tlist, char* dep) {
	/*TargetList 에서 인자로 받은 dep과 같은 이름의 Target이 있는지를 검색해서
	  있다면 true 없다면 false를 반환해주는 함수입니다*/
	bool res = false;
	if(Tlist->head == NULL) {
		return res;
	}

	while(Tlist->cur != NULL) {
		if(strcmp(Tlist->cur->Target, dep) == 0) {
			res = true;
			return res;
		}
		Tlist->cur = Tlist->cur->next;
	}
	Tlist->cur = Tlist->head;
	return res;
}

bool isMatch(char* str, char* cmp)
{  
	/*정규 표현식을 처리해서 str이 cmp에
	  포함되어 있을 경우 true를 반환하고
	  그렇지 않을 경우 false를 반환하는 함수*/

	int error_code;
	regex_t preg;
	char buf[BUFSIZ];

	if(( error_code = regcomp(&preg, str, 0)) != 0)
	{
		regerror(error_code, &preg, buf, BUFSIZ);
		return false;
	}

	if((error_code = regexec(&preg, cmp, (size_t)0, NULL, 0)) != 0)
	{
		regerror(error_code, &preg, buf, BUFSIZ);
		return false;
	}

	else
		return true;
}

TargetNode* findTarget(TargetList* Tlist, char* str)
	/*str이름을 가진 Target을 찾아서 반환해주는 함수*/
{
	int cmp;
	TargetNode* res = (TargetNode*)malloc(sizeof(TargetNode));
	while(Tlist->cur != NULL) {
		cmp = strcmp(Tlist->cur->Target,str);
		if(cmp == 0)
		{
			res = Tlist->cur;
			Tlist->cur = Tlist->head;
			return res;
		}
		else
			Tlist->cur = Tlist->cur->next;
	}
	Tlist->cur = Tlist->head;
}

void makeDep(TargetList* Tlist, TargetNode* Tnode, char* dep, char useTarget[20][20],int magimak,int* flag,int flag_s)
{ 
	/*Target의 Dependency를 확인하여 그 Dependency가 Target이라면 그 Target을 만들고
	  아니라면 현재 디렉토리에 Dependency가 있는지 확인해 없다면 에러 메세지를 출력하고
	  종료합니다.*/
	if(*flag != 1)  //순환하지 않을 경우입니다.
	{
		Tlist->cur = Tlist->head;
		if(isTarget(Tlist, dep)) {  // 만약 Dependency가 Target이고 순환하지 않을 경우입니다.
			TargetNode* newTnode = findTarget(Tlist,dep);
			if(access(newTnode->Target,F_OK) != 0){  //Dependency가 디렉토리에 존재하는 확인합니다.
				DepNode* compare = Tnode->Dep;
				DepNode* Dlist = newTnode->Dep;
				if(Dlist == NULL) {  //Depency의 Dependency가 없을 경우 Command를 실행합니다.
					ComNode* Clist = newTnode->Com;
					while(Clist != NULL) {
						if(flag_s != 1)
							printf("%s\n",Clist->Command);
						system(Clist->Command);
						Clist = Clist->next;
					}
				}
				else {  //Dependency의 Dependency가 있다면 순환하는지를 확인합니다.
					while(compare != NULL){
						if(usedTarget(useTarget,compare->Dependency))
							*flag = 1;
						compare = compare->next;
					}
					strcpy(useTarget[magimak+1],newTnode->Target);
					compare = Tnode->Dep;
					if(*flag == 1){
						while(compare != NULL) {
							if(usedTarget(useTarget,compare->Dependency)) {
								printf("make: Circular %s <- %s dependency dropped.\n",Tnode->Target,compare->Dependency);
							}
							compare = compare->next;
						}
					}
					else{  //순환하지 않는다면 그 Dependency의 Dependency를 재귀적으로 만들어줍니다.
						while(Dlist != NULL) 
						{
							makeDep(Tlist,newTnode,newTnode->Dep->Dependency,useTarget,magimak+1,flag,flag_s);
							Dlist = Dlist->next;
						}
						ComNode* C = newTnode->Com;
						while(C != NULL) {  //Dependency의 Command를 실행합니다.
							if(flag_s != 1)
								printf("%s\n",C->Command);
							system(C->Command);
							C = C->next;
						}
					}
				}
			}
			else  //Dependency가 디렉토리에 있다면 수정 시간을 비교하고 실행합니다
			{
				DepNode* compare = Tnode->Dep;
				DepNode* Dlist = newTnode->Dep;
				struct stat Tst;
				stat(newTnode->Target,&Tst);
				struct stat Dst;
				int T_flag = 0;
				while(Dlist != NULL) {  /*모든 Dependency의 수정 시간을 비교하여 Target보다
										  최근에 변경된 적이 있다면 Target을 실행합니다*/ 
					if(access(Dlist->Dependency,F_OK) ==0)
						stat(Dlist->Dependency,&Dst);
					else {
						T_flag = 1;
						break;
					}
					if(difftime(Tst.st_mtime,Dst.st_mtime) < 0){
						T_flag = 1;
					}
					Dlist = Dlist->next;
				}
				Dlist = newTnode->Dep;

				if(T_flag == 1) {  
					if(Dlist == NULL) {
						ComNode* Clist = newTnode->Com;
						while(Clist != NULL) {
							if(flag_s != 1)
								printf("%s\n",Clist->Command);
							system(Clist->Command);
							Clist = Clist->next;
						}
					}
					else {
						while(compare != NULL) {
							if(usedTarget(useTarget, compare->Dependency))
								*flag = 1;
							compare = compare->next;
						}
						strcpy(useTarget[magimak+1],newTnode->Target);
						compare = Tnode->Dep;
						if(*flag == 1) {  //만약 순환되다면 순환 메세지를 출력하고 Command를 실행합니다.
							while(compare != NULL) {
								if(usedTarget(useTarget,compare->Dependency))
									printf("make: Circular %s <- %s dependency dropped.\n",Tnode->Target,compare->Dependency);
								compare = compare->next;
							}
						}
						else{
							while(Dlist != NULL)
							{
								makeDep(Tlist,newTnode,newTnode->Dep->Dependency,useTarget,magimak+1,flag,flag_s);
								Dlist = Dlist->next;
							}
							ComNode* C = newTnode->Com;
							while(C != NULL) {
								if(flag_s != 1)
									printf("%s\n", C->Command);
								system(C->Command);
								C = C->next;
							}
						}
					}
				}
				else
					printf("'%s' is up to date\n",newTnode->Target);
			}
		}
		else if(access(dep,F_OK) == 0) {
		}
		else {  //Target도 아니고 디렉토리에도 없다면 에러 메세지를 출력하고 종료합니다.
			fprintf(stderr,"maek: *** No rule to make target '%s', nedded by '%s'.  Stop.\n",dep,Tnode->Target);
			exit(1);
		}
	}
}

bool isMacro(MacroList* Mlist, char* macro) {
	/*인자로 받은 MacroList에서 macro라는 이름의 Macro가 있다면 true를
	  없다면 false를 반환하는 함수입니다.*/
	bool res = false;
	if(Mlist->head == NULL)
		return res;
	Mlist->cur = Mlist->head;
	while(Mlist->cur != NULL)
	{
		if(strcmp(Mlist->cur->Macro,macro) == 0) {
			res = true;
			return res;
		}
		Mlist->cur = Mlist->cur->next;
	}
	Mlist->cur = Mlist->head;
	return res;
}

MacroNode* findMacro(MacroList* Mlist, char* str)
{
	/*인자로 받은 MacroList에서 str이라는 Macro를 가지는 Macro 구조체를
	  찾아서 반환해주는 함수입니다.*/
	int cmp;
	MacroNode* res = (MacroNode*)malloc(sizeof(MacroNode));
	while(Mlist->cur != NULL)
	{
		cmp = strcmp(Mlist->cur->Macro,str);
		if(cmp == 0)
		{
			res = Mlist->cur;
			Mlist->cur = Mlist->head;
			return res;
		}
		else
			Mlist->cur = Mlist->cur->next;
	}
	Mlist->cur = Mlist->head;
}

void freeList(TargetList* Tlist, MacroList* Mlist)
{
	/*TargetList와 MacroList를 받아서 두 구조체의 메모리를
	  전부 헤제해주는 함수입니다.*/
	TargetNode* d;
	while(Tlist->cur != NULL)
	{
		d = Tlist->cur;
		Tlist->cur = Tlist->cur->next;
		free(d);
	}
	MacroNode* d2;
	while(Mlist->cur != NULL)
	{
		d2 = Mlist->cur;
		Mlist->cur = Mlist->cur->next;
		free(d2);
	}
}

char* trimforcom(char* com)
{ 
	//문장을 인자로 받아 그 문자의 왼쪽 여백을 모두 제거해 주는 함수입니다.
	char* cut = com;

	while(*cut != '\0')
	{
		if(isspace(*cut))
			cut++;
		else
		{
			cut--;
			com = cut;
			break;
		}
	}
	return com;
}

bool isinclude(char** fileline)
{
	/*2중 포인터를 받아서 그 안에 include라는 단어가 있다면 true를 
	  없다면 false를 반환해주는 함수입니다.*/
	bool res = false;
	int start = 0;
	while(fileline[start] != NULL)
	{
		if(isMatch("include",fileline[start])) {
			res = true;
		}
		start++;
	}
	return res;
}

int includeline(char** fileline)
{
	/*2중 포인터를 받아서 그 안에 include라는 단어를 찾아 그 줄을
	  반환해주는 함수입니다.*/
	int line = 0;
	int start = 0;
	while(fileline[start] != NULL)
	{
		if(isMatch("include",fileline[start]))
			line = start;
		start++;
	}
	return line;
}

void printDep(TargetList* Tlist,TargetNode* Tnode,int blank,int flag, char* useTarget[20], int stopflag,int kak)
{
	//Dependency를 받아서 그 dependeny를 tree형태로재귀적으로 출력해주는 함수입니다.
	if(Tnode->Dep == NULL) {
		printf("%s\n",Tnode->Target);
	}
	else {
		if(flag>1) {
			for(int index = 0; index < blank;index++)
				printf(" ");
		printf("\t");
		}
		DepNode* hoNode = Tnode->Dep;
		while(hoNode != NULL) {
			if(flag < 2)
			printf("%s	",Tnode->Target);
			printf("%s	",hoNode->Dependency);
			if(stopflag ==1){
				if(isTarget(Tlist, hoNode->Dependency)) {
					TargetNode* jNode = findTarget(Tlist,hoNode->Dependency);
					printDep(Tlist,jNode,blank,flag,useTarget,stopflag,kak+1);
				}
			}
			hoNode = hoNode->next;
		}
	}
}

void printTree(TargetList* Tlist)
{ 
	//TargetList를 인자로 받아서 tree형태로 출력해주는 함수입니다.
	int kak = 0;
	char* useTarget[20];
	if(Tlist->head != NULL) {
		TargetNode* printT = Tlist->head;
		useTarget[kak] = (char*)malloc(sizeof(char)*20);
		useTarget[kak] = Tlist->head->Target;
		while(printT != NULL) {
			int stopflag = 0;
			int blank = 0;
			blank += strlen(printT->Target);
			if(printT->Dep == NULL)
				printf("%s\n",printT->Target);
			else 
			{
				printf("%s	",printT->Target);
				DepNode* printD = printT->Dep;
				int flag = 0;
				while(printD != NULL) {
					flag++;
					if(isTarget(Tlist,printD->Dependency))
					{
						TargetNode* hNode = findTarget(Tlist,printD->Dependency);
						if(hNode->Dep != NULL) {
							printDep(Tlist,hNode,blank,flag,useTarget,stopflag,kak+1);
							printf("\n");
						}
						else {
							for(int index = 0; index < blank; index++)
								printf(" ");
							printf("\t");
							printf("%s\n",hNode->Target);
						}
					}
					else
					{
						printf("%s\n",printD->Dependency);
					}
					printD = printD->next;
				}
			}
			printT = printT->next;
		}
	}
	else {
		fprintf(stderr,"Target이 없습니다.\n");
		exit(1);
	}
}
