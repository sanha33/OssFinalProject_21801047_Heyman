#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_BUFFER 2048
#define MAX_WORD 10000
#define LEN_NAME 200
#define LEN_WORD_CLASS 20

#define USE_WORD_LEN 4
#define TRY_COUNT 12
#define NUM_ALPHA 26

#define CLEAR system("clear");

typedef struct{
	char word[LEN_NAME];
	char wordClass[LEN_WORD_CLASS];
	char *means;
}Dictionary;

typedef struct UserNode{
	char name[LEN_NAME];			   
	int victoryCount;
	int looseCount;
	float winRate;
	struct UserNode* next;
}UserNode;


UserNode* Load_user_from_file(char *argv[]);
      
UserNode* Set_User(UserNode* header, char *argv[], char yesOrNo[]);

void Control_Menu(UserNode* header, Dictionary Dic[MAX_WORD], int wordCount, char *argv[]); 

void Init_Node(UserNode* CurNode); 

int LoadDic(Dictionary Dic[MAX_WORD], char *argv[]); 

char Prn_Menu();     

void Play_game(UserNode* curUserInformation, Dictionary Dic[MAX_WORD]);

void Prn_score_now(UserNode* curUserInformation);            

void Prn_score_previous(UserNode* loadedPlayer);             

void Prn_rank(UserNode* header, char yesOrNo[]);	               	  

void Message_fail_success(UserNode* curUserInformation, Dictionary Dic[MAX_WORD], int tryCount, int rand_num);

void Save_user_record(UserNode* header, char *argv[]);

void Key_continue(void);

void Sort(UserNode* header);

void Free_node(UserNode* header);

void Free_dic(Dictionary Dic[MAX_WORD], int wordCount);
