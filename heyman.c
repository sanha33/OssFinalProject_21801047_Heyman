#include "hangman_header.h"

int main(int argc, char *argv[]){
	
	UserNode* header = (UserNode*)malloc(sizeof(UserNode));

	Dictionary Dic[MAX_WORD]; 
	
	int wordCount;  


	if(argc != 3){
		printf("You have to input argv correctly");
		exit(0);
	}

	printf("\t\t\t==========================\n");
	printf("   =*=*==*========*====*=======*====*==*\n");
	printf("    *  *  Let's start to Hangman Game . * *  *\n");
	printf("   ===*==*====*==*=========*=====*===*==\n");
	printf("=========================\n");
	
    printf("Enter a registered ID or a new ID [up to 20 characters] :");
	wordCount = LoadDic(Dic, argv);
	
	header = Load_user_from_file(argv);
	
	Control_Menu(header, Dic, wordCount, argv); 
	return 0;
}


void Control_Menu(UserNode* header, Dictionary Dic[MAX_WORD], int wordCount, char *argv[])
{
	UserNode* curUserInformation = (UserNode*)malloc(sizeof(UserNode)); 
	
	UserNode* loadedPlayer; 
	char getMenu;
	
	char rankFlag[1] = {0}; 
	
	if(curUserInformation == NULL){     
		printf("Allocation Error\n");
		exit(0);
	}
	
	Sort(header);
	
	loadedPlayer = Set_User(header, argv, rankFlag);    
	
	Init_Node(curUserInformation);  
	
	strcpy(curUserInformation->name, loadedPlayer->name);
	
	getMenu = Prn_Menu(); 
	
	if(isupper(getMenu))
		getMenu = tolower(getMenu);
	CLEAR
	
	while(1){
		switch(getMenu){
			case 's' : {
			
				Play_game(curUserInformation, Dic);
				break;      
			}
			case 'i' : {
			
				Prn_score_now(curUserInformation);
				break;              
			}
			case 'h' : {
			
				Prn_score_previous(loadedPlayer);
				break;          
			}
			case 'r' : {
			
				if(rankFlag[0] == '1')
					Prn_rank(header->next, rankFlag);
				else
					Prn_rank(header, rankFlag);
				break;			      
			}
			case 'q' : {	
			
				loadedPlayer->looseCount += curUserInformation->looseCount;
				loadedPlayer->victoryCount += curUserInformation->victoryCount;
				loadedPlayer->winRate = ((float)loadedPlayer->victoryCount / ((float)loadedPlayer->victoryCount + 
							(float)loadedPlayer->looseCount)) * 100;
				Save_user_record(header, argv);
				printf("\n\n\t\tSave the exit ^_^\n\n\n");
				Free_node(header);
				Free_dic(Dic, wordCount);
				exit(1);
			}
			case 'z' : {
			
				printf("\nPrint this game result [without saving] ^_^\n\n\n");
				Free_node(header);
				Free_dic(Dic, wordCount);
				exit(1);
			}
		}
		
        
		getMenu = Prn_Menu(); 
		
			getMenu = tolower(getMenu);
		CLEAR
	}
}


void Free_dic(Dictionary Dic[MAX_WORD], int wordCount)
{
	int i;
	i = 0;
	while(i<wordCount)
		free(Dic[i++].means);
}


void Free_node(UserNode* header)
{
	UserNode* temp;
	while(header->next != NULL){
		temp = header;
		header = header->next;
		free(temp);
	}
}


void Key_continue(void)
{
	char temp[MAX_WORD];
	char ch;
	int i=0;


	printf("\n\n\t\tPress the [ ENTER ] key to continue.\n");
	while(ch != '\n'){
		ch = getchar();
		temp[i++] = ch;
	}
}


void Init_Node(UserNode* CurNode)
{
	CurNode->looseCount = 0;
	CurNode->victoryCount = 0;
	CurNode->winRate = 0.00;
}

void Sort(UserNode* header)
{

	UserNode* temp = (UserNode*)malloc(sizeof(UserNode));	
	UserNode* ptr1;
	UserNode* ptr2;

	for(ptr1 = header->next ; ptr1 != NULL ; ptr1 = ptr1 -> next){
		for(ptr2 = ptr1->next ; ptr2!= NULL ; ptr2 = ptr2->next){
			if(ptr2->winRate > ptr1->winRate){
				strcpy(temp->name, ptr2->name);
				strcpy(ptr2->name, ptr1->name);
				strcpy(ptr1->name, temp->name);
				
				temp->winRate = ptr2->winRate;
				ptr2->winRate = ptr1->winRate;
				ptr1->winRate = temp->winRate;
				
				temp->looseCount = ptr2->looseCount;
				ptr2->looseCount = ptr1->looseCount;
				ptr1->looseCount = temp->looseCount;

				temp->victoryCount = ptr2->victoryCount;
				ptr2->victoryCount = ptr1->victoryCount;
				ptr1->victoryCount = temp->victoryCount;
			}
		}
	}
	free(temp);
}


void Save_user_record(UserNode* header, char *argv[])
{
	UserNode* ptr = (UserNode*)malloc(sizeof(UserNode));

	FILE *FileOut = fopen(argv[2], "wb");
	
	ptr = header->next;
	while(ptr->next != NULL){
		fprintf(FileOut, "[%s] [%d] [%d]", ptr->name, (int)ptr->victoryCount, (int)ptr->looseCount);
		if(ptr->next != NULL)
			fprintf(FileOut, "\n");
		ptr = ptr->next;
	}
	
	free(ptr);
	fclose(FileOut);
}
	

void Prn_score_now(UserNode* curUserInformation)
{
	printf("\n\n\t\t==> [%s]   \n", curUserInformation->name);
	printf("\t\t+---------------------------------------+\n");
	printf("\t\t| %3d     %3d        :   %6.2f\n", curUserInformation->victoryCount,
								curUserInformation->looseCount, curUserInformation->winRate);
	printf("\t\t+---------------------------------------+\n");
	Key_continue();
}


void Prn_score_previous(UserNode* loadedPlayer)
{
	printf("\n\n\t\t==> [%s]         \n", loadedPlayer->name);
	printf("\t\t+---------------------------------------+\n");
	printf("\t\t%3d       %3d                :   %6.2f\n", loadedPlayer->victoryCount, loadedPlayer->looseCount, loadedPlayer->winRate);
	printf("\t\t+---------------------------------------+\n");
	Key_continue();
}

void Prn_rank(UserNode* header, char yesOrNo[] )
{
	UserNode* TempPtrNext;
	UserNode* TempPtrNow;
	int rankCount;
	int temp;

	TempPtrNext = header;
	TempPtrNow = header->next;
	printf("\n\n\t\t==>                                            \n");
	printf("\t\t+----------------------------------------------------------------------+\n");
	rankCount = 1;
	temp = 1;
	while(TempPtrNow->next != NULL){
	    
		if(TempPtrNext->winRate == TempPtrNow->winRate)
			printf("\t\t%3d  : [%s] [%d] [%d [ :%.2f]\n", temp, TempPtrNow->name,
						TempPtrNow->victoryCount+TempPtrNow->looseCount, TempPtrNow->victoryCount, TempPtrNow->winRate);
		
		else{   
			printf("\t\t%3d: [%s] [%d] [%d] [:%.2f]\n", rankCount, TempPtrNow->name,
						TempPtrNow->victoryCount+TempPtrNow->looseCount, TempPtrNow->victoryCount, TempPtrNow->winRate);
			temp = rankCount;
		}
	
		rankCount++;
		TempPtrNext = TempPtrNext->next;
		TempPtrNow = TempPtrNow->next;
	}


	if(yesOrNo[0] == '1')
		printf("\t\t|%3d  : [%s] [%d] [%d] [ : %.2f]\n", temp, header->name, header->victoryCount+header->looseCount, header->victoryCount,
							header->winRate);
	printf("\t\t+----------------------------------------------------------------------+\n");
	Key_continue();
}


char Prn_Menu(void)
{
	char getMenu;
	char temp;

	CLEAR;
	while(1){
		printf("\n\n\t\t+---M--E--N--U---*-----*------------------+\n");
		printf("\t\t| S = Game start    *   *      *              |\n");
		printf("\t\t| I = Print your score for this game   *   *  |\n");
		printf("\t\t| H = Print your previous   *                 |\n");
		printf("\t\t| R = Save and exit this game result      *   |\n");
		printf("\t\t| Q = Save the exit   *             *         |\n");
		printf("\t\t| Z = Print this game result [without saving]*|\n");
		printf("\t\t+---M--E--N--U---*-----*---------------------+\n");
		printf("\n\n\t\t Input Menu [S/I/H/R/Q/Z] -> ");
		scanf("%c", &getMenu);
		temp = getchar();
		if(getMenu == 's' || getMenu == 'S' || getMenu == 'i' || getMenu == 'I' || 
			getMenu == 'h' || getMenu == 'H' || getMenu == 'r' || getMenu == 'R' || 
			getMenu == 'q' || getMenu == 'Q' || getMenu == 'z' || getMenu == 'Z')
			return getMenu;   
		
		else{               
			printf("\n\n\n\t\t\t--Warning--*--**-----\n");
			printf("\t\t\t *   Menu Input Error      \n");
			printf("\t\t\t           *             * \n");
			printf("\t\t\t--*----*--*-Warning---*--*-\n");
		}
	}
}
		

UserNode* Set_User(UserNode* header, char *argv[], char yesOrNo[])
{
	
	UserNode* cur = (UserNode*)malloc(sizeof(UserNode));
	UserNode* ptr = (UserNode*)malloc(sizeof(UserNode));
	
	UserNode* indexPlayUser;

	char userName[LEN_NAME], ch;
	char newOrLoad;
	char temp;
	int findSw;
	int i;

	while(1){
		
		indexPlayUser = (UserNode*)malloc(sizeof(UserNode));	
		
		if(indexPlayUser == NULL){
			printf("Allocation Error\n");
			exit(1);
		}
	
		
		i = 0;
		while((ch = getchar()) != '\n'){
			userName[i] = ch;
			i++;
		}
		userName[i] = '\0';
	
		strcpy(indexPlayUser->name, userName);
		strcpy(cur->name, indexPlayUser->name);

		
		ptr = header->next;
		findSw = 0;
		while(ptr->next != NULL){
			if(strcmp(ptr->name, indexPlayUser->name) == 0){
				indexPlayUser = ptr;
				findSw = 1;
				break;
			}
			else
				ptr = ptr->next;
		}
		
		
		if(findSw){  
			printf("\n Duplicate name. Are you sure you want to load it? Would you like to make a new one?       \n");
			printf("|==================> [Load / New] : ");
			scanf("%c", &newOrLoad);
			temp = getchar();
		}
		
		else{
			Init_Node(indexPlayUser);
			strcpy(indexPlayUser->name, cur->name);
			cur = header -> next;
			header->next = indexPlayUser;
			indexPlayUser -> next = cur;             
			Save_user_record(header, argv);
			yesOrNo[0] ='1';
			printf("\n\n\t\t[%s]", indexPlayUser->name);
			Key_continue();               
			break;
		}
		
		if(newOrLoad == 'l'|| newOrLoad == 'L'){
			printf("[%s]", indexPlayUser->name);
			Key_continue();
			break;
		}
		
		else if(newOrLoad == 'n' || newOrLoad == 'N'){
			continue;
		}

		else{
            printf("\n\n\n\t\t\t--Warning--*--**-----\n");
            printf("\t\t\t *   Menu Input Error      \n");
            printf("\t\t\t           *             * \n");
            printf("\t\t\t--*----*--*-Warning---*--*-\n");
        }
        
    }
	
	return indexPlayUser;
}
