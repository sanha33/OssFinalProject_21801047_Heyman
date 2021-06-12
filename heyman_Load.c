#include "hangman_header.h"

UserNode* Load_user_from_file(char *argv[])
{
	char temp[MAX_BUFFER];
	UserNode* header = (UserNode*)malloc(sizeof(UserNode));
	UserNode* curNode;
	UserNode* newUser;
	FILE *FILEIN = fopen(argv[2], "rb");

	
	if(FILEIN == NULL){
		printf("User File Open Error\n");
		exit(1);
	}
	header->next = NULL;
	curNode = header;
	while(!feof(FILEIN)){
		newUser = (UserNode*)malloc(sizeof(UserNode));
		fscanf(FILEIN, "[%[^]]", newUser->name);
		fseek(FILEIN, 3, 1);
		fscanf(FILEIN, "%d", &newUser->victoryCount);
		fseek(FILEIN, 3, 1);
		fscanf(FILEIN, "%d", &newUser->looseCount);
		fgets(temp, MAX_BUFFER, FILEIN);
		newUser->winRate = ((float)newUser->victoryCount / ((float)newUser->victoryCount + (float)newUser->looseCount)) * 100;
		
		if(newUser->victoryCount == 0)
			newUser->winRate = 0.00;
		
		newUser -> next = NULL;
		curNode -> next = newUser;
		curNode = newUser;
	}	
	fclose(FILEIN);
	return header;
}


int LoadDic(Dictionary Dic[MAX_WORD], char *argv[])
{
	int dic_count = 0;
	int i,j,k;
	int wordLen;
	char buff[MAX_BUFFER];
    char temp[MAX_BUFFER];
	FILE *FILEIN = fopen(argv[1], "rb");

	
	if(FILEIN == NULL){
		printf("Dictionary File Open Error\n");
		exit(1);
	}
	
	i=0;
	while(!feof(FILEIN)){
		fgets(buff, MAX_BUFFER, FILEIN);
		dic_count++;
		wordLen = strlen(buff);
		for(j=6;j<wordLen;){
			k=0;
			while(buff[j] != ']'){
				Dic[i].word[k] = buff[j];
				k++;j++;
			}
			Dic[i].word[k] = '\0';
			j=j+3;
			k = 0;
			while(buff[j] != ']'){
				Dic[i].wordClass[k] = buff[j];
				k++;j++;
			}
			Dic[i].wordClass[k] = '\0';
			j= j+3;
			k = 0;
			while(buff[j] != '\n'){
				temp[k] = buff[j];
				k++;j++;
			}
			temp[k-1] = '\0';
		       
			k = strlen(temp);           
			Dic[i].means = (char *)malloc((sizeof(Dic[i].means) * k));
			strcpy(Dic[i].means, temp);
			
			j = wordLen;
			i++;
		}
		if(dic_count == MAX_WORD)
			break;
	}
	
	fclose(FILEIN);
	return dic_count;
}
