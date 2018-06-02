#include "ssu_make.h"
bool usedTarget(char useTarget[20][20],char* Target);
void insT(TargetList* Tlist, TargetNode* node);
void insM(MacroList* Mlist, MacroNode* node);
ComNode* creatCom(char* com, int line);
DepNode* creatDep(char* dep);
MacroNode* creatMacro(char* macro, char* value, int mline , char state);
bool isTarget(TargetList* Tlist, char* dep);
bool isMatch(char* str, char* cmp);
TargetNode* findTarget(TargetList* Tlist, char* str);
void makeDep(TargetList* Tlist, TargetNode* Tnode, char* dep,char useTarget[20][20],int magimak,int* flag, int flag_s);
bool isMacro(MacroList* Mlist, char* macro);
MacroNode* findMacro(MacroList* Mlist, char* str);
void freeList(TargetList* Tlist,MacroList* Mlist);
char* trimforcom(char* com);
bool isinclude(char** fileline);
int includeline(char** fileline);
void printTree(TargetList* Tlist);
void printDep(TargetList* Tlist,TargetNode* Tnode, int blank, int flag, char* useTarget[20],int stopflag,int kak);
