#include "hangman_header.h"


void Play_game(UserNode* curUserInformation, Dictionary Dic[MAX_WORD])
{
	char alphabet[NUM_ALPHA], ch;
	char seeWord[MAX_WORD];
	char inputWord[MAX_WORD];
	char comparisonWord[MAX_WORD];
    
	int failCount = 0;
	int num_success=0;
	int tryCount = TRY_COUNT;
	int rand_num, len_word = 0;
    
	int searchAlpha;
	int findFlag = -1;
	int i;
	

    
	while(len_word < USE_WORD_LEN){  
		srand (time(NULL));
		rand_num = rand() % MAX_WORD;
		len_word = strlen(Dic[rand_num].word);
	}
	
	ch = getchar();
	i = 0;
    printf("here !");
	while(i<len_word){
		comparisonWord[i] = tolower(Dic[rand_num].word[i]);
		i++;
	}
	comparisonWord[i] = '\0'; 
	for(i = 0 ; i< NUM_ALPHA ; i++)  
		alphabet[i] = 'A' + i;
	alphabet[i] = '\0';
	
	for(i=0;i<len_word;i++)                 
		seeWord[i] = (char)'-';
	seeWord[i] = '\0';

	while(1){
		if(num_success == len_word || tryCount == 0)
			break;
		
		CLEAR
   		
		printf("Target word  :  ");
		i = 0;
		while(seeWord[i] != '\0')
			printf("%c ", seeWord[i++]);
		printf("\nCharacters Used: ");
		i = 0;
		while(alphabet[i] != '\0')
			printf("%2c", alphabet[i++]);
		printf("\n\nCurrently, %d failed. You can try %d times in the future.", failCount, tryCount);
		printf("\n%d alphabest, %d successes", len_word, num_success);
		printf("\n\nPart of speech: %s", Dic[rand_num].wordClass);
		printf("\nmeaningful interpretataion: [%s]", Dic[rand_num].means);
		printf("\n\n\nType in the alphabet or the whole word.[A-z] : ");
		
	
		for(i=0;(ch = getchar()) != '\n';i++){
			inputWord[i] = ch;
			if(inputWord[i] >= 'A' && inputWord[i] <= 'Z')
				inputWord[i] = tolower(inputWord[i]);
		}
		inputWord[i] = '\0';
		searchAlpha = inputWord[0]-'a';   
    
		if(inputWord[0] == '\n' || !isalpha(inputWord[0])){
			printf("\n\n\t\tAlphabet Correct !.");
			Key_continue();
			continue;
		}
		
		if(strcmp(inputWord, comparisonWord) == 0 && inputWord[1] != '\0'){
			break;
		}
		
		else if(strcmp(inputWord, comparisonWord) != 0 && inputWord[1] != '\0'){
			failCount++;
			tryCount--;
			printf("\n\n\t\tYou are wrong try again : %s\n", inputWord);
			Key_continue();
		}
		
		else{
            //
            char c;
            findFlag = -1;
            c =toupper(inputWord[0]);
			for(i=0;i<len_word;i++){ 
				
				if(comparisonWord[i] == inputWord[0] && isupper(alphabet[searchAlpha])){       
					findFlag = 1;
					num_success++;
					seeWord[i] =inputWord[0];
				}
				
				else if(comparisonWord[i] == inputWord[0] && islower(alphabet[searchAlpha])){
					findFlag = 0;
					printf("\n\n\t\t: %c\n", inputWord[0]);
					break;
				}
				
				else
					continue;
			}
			
			if(findFlag == 1){		   
				alphabet[searchAlpha] = tolower(alphabet[searchAlpha]);
				printf("\n\n\t\t: %c\n", inputWord[0]);
			}
			
			else if(findFlag == -1){    
				if(isupper(alphabet[searchAlpha])){  
					failCount++;  
					tryCount--;   
					alphabet[searchAlpha] = tolower(alphabet[searchAlpha]);
					printf("\n\n\t\t-. : %s\n", inputWord);
				}
				else
					printf("\n\n\t\t--. : %c\n", inputWord[0]);
			}
			Key_continue();
		}
	}
	Message_fail_success(curUserInformation, Dic, tryCount, rand_num);  
}

void Message_fail_success(UserNode* curUserInformation, Dictionary Dic[MAX_WORD], int tryCount, int rand_num)
{
	CLEAR
	if(tryCount == 0){
		curUserInformation->looseCount++;
		printf("\n\n\t\t--------------------------------\n");
		printf("\t\t[Fail] : %s .\n", Dic[rand_num].word);
		printf("\t\t--------------------------------\n");
	}
	
	else {
		curUserInformation->victoryCount++;
		printf("\n\n\t\t--------------------------------\n");
		printf("\t\t[Success] : %s\n", Dic[rand_num].word);
		printf("\t\t--------------------------------\n");
	}
	curUserInformation->winRate = ((float)curUserInformation->victoryCount / 
					((float)curUserInformation->victoryCount + (float)curUserInformation->looseCount)) * 100;
	Key_continue();
	return;
}
