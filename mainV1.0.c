/*
	Aurthor : Murali Wood
	Tytle : WordSearch
	Date : 30/03/2019
	
	This program is a wordsearch game. It generates a board based on what 
	category the user picks. When played the user has three minutes to 
	find all 10 word in on a board 30 by 30.  
	
	I followed the following tutorial 
	//https://overiq.com/c-programming-101/array-of-strings-in-c/ 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char **create2DArray(); //function prototype
void printArray();

#define WIDTH 30
#define HEIGHT 30
#define WORDLEN 15
// numwords must be > 3
#define NUMWORDS 10

char **myArray; //global array

// this struct enables blocking out the words as you find them
struct wordsInBox {
	char word[WORDLEN];
	int sRow;
	int sColumn;
	char direction;
};

struct wordsInBox arrWord[NUMWORDS];

// words that are in the current game							
char workingWords[NUMWORDS][WORDLEN];

// runs the main loop and creates the lists of words
int main(int argc, char *argv[]) {
	
	system("COLOR 0A");
	
	srand(time(0));
	
	int i,j,select,wordsFound = 0,found,struID,timeLeft = 180,minute,pick = 1;;
	float seconds, startSeconds = 180.2;
	char name[10];
	char answer[WORDLEN];
	
	char celestialObjects[22][WORDLEN] = {
								"MERCURY", "VENUS", "EARTH", "MOON", "MARS",
								"DAIMOS", "PHOBOS", "ASTEROIDBELT",
								"CERES", "PALLAS", "JUNO", "VESTA", "JUPITER", 
								"EUROPA", "GANYMEGE", "CALLISTO", "SATURN", 
								"URANUS", "NEPTUNE", "PLUTO", "SUN"
								};
								
	char rockets[13][WORDLEN] = {
							"SATURNV", "DELTAVMEDIUM", "N1", "SPACESHUTTLE", 
							"FALCONHEAVY", "ARES1-X", "ARIANE4", "ATLASV", 
							"ANGARAA5", "DELTAVHEAVY", "FALCON9", "SOYUZ", 
							"LONGMARCH2F"
							};
							
	char marsRobots[15][WORDLEN] = {
								"VIKING1", "RECONNAISSANCE", "ORBITERMISSION",
								"MAVEN", "EXOMARSTRACEGAS", "VIKING2", "PATHFINDER", 
								"SPIRIT", "OPPORTUNITY", "PHOENIX", "CURIOSITY",
								"INSIGHT", "GLOBALSURVEYOR", "ODYSSEY", "EXPRESS"
								};
 	
 	myArray = create2DArray();
 	
 	// ---------- INTRO -------------
 	
 	printf("\n---------------------------------------");
 	printf("\n|                                     |");
 	printf("\n|     Welcome to Word Search 3000     |");
 	printf("\n|                                     |");
 	printf("\n---------------------------------------");
 	
 	printf("\n\nWhat is your name? ");
 	scanf("%s", &name); getchar();
 	
	// ---------- SELECT CATEGORY -----------
 	
	while (pick){
 	
	 	printf("\nHello %s! Please select a category : \n"
	 			"\n   -----------------------------------------"
		 		"\n   (1) Celestial objects in our solar system"
				"\n   (2) Rockets"
				"\n   (3) Robots on or orbiting Mars"
	 			"\n   -----------------------------------------\n"
				 , name);
	 	scanf("   %d", &select); getchar();
		
	
		if (select == 1){
			pick = 0;
			printf("\nCategory: Celestial objects in our solar system");
			for(i=0; i<NUMWORDS; i++){
				for (j=0; j<WORDLEN; j++){
					workingWords[i][j] = celestialObjects[i][j];
				}
			}
		}
		else if (select == 2){
			pick = 0;
			printf("\nCategory: Rockets");
			for(i=0; i<NUMWORDS; i++){
				for (j=0; j<WORDLEN; j++){
					workingWords[i][j] = rockets[i][j];
				}
			}
		}
		else if (select == 3){
			pick = 0;
			printf("\nCategory: Robots on or orbiting Mars");
			for(i=0; i<NUMWORDS; i++){
				for (j=0; j<WORDLEN; j++){
					workingWords[i][j] = marsRobots[i][j];
				}
			}
		}
		else{
			
			system("cls");
			printf("\nEnter the number one, two or three ...\n");
		}
	}
	
	wordsToBoard((char *)workingWords);
	
	// FILL IN RANDOM LETTERS 
	for(i=0; i<WIDTH; i++){
	
		for(j=0; j<HEIGHT; j++){
			
			if (myArray[i][j] == '.'){
				myArray[i][j] = 65 + rand() % 25;
			}
		}
	}
	
		// -------- START OF SEARCH ---------
	
	printf("\n\nOk %s - There are %d words hidden in this grid.", name, NUMWORDS);
	printf("\nCan you find them all?");
	printf("\nYou have 2 minutes!\n"); 
	
	// start clock
	clock_t start = clock();
	
		system("cls");
	
	while (timeLeft > 0){
	
		printf("\n\t---------------------------------------");
	 	printf("\n\t|                                     |");
	 	printf("\n\t|           Word Search 3000          |");
	 	printf("\n\t|                                     |");
	 	printf("\n\t---------------------------------------\n");	
	
		printArray();
		
		// ------------ FIX CLOCK -------------
		
		clock_t end = clock(); 
		seconds = startSeconds - ((float)(end - start) / CLOCKS_PER_SEC);
		timeLeft = startSeconds - ((float)(end - start) / CLOCKS_PER_SEC);
		minute = seconds / 60;
		
		while(seconds > 59){
			seconds = seconds - 60;
		}
		
		// ------------ ASK FOR WORD ------------
		
		printf("\n%d Words left", NUMWORDS - wordsFound);
		
		if (seconds < 1 && minute < 1)
			break;
			
		printf("\nYou have %d minutes and %00.0f seconds left.", minute, seconds);
		
		if (wordsFound == NUMWORDS){
			printf("\nCongratulations! You won :)");
			getchar();
			break;
		}
		printf("\nFind a word and type it here: ");
		scanf("%s", &answer); getchar();
		
		// ---------- COMPARE WORDS TO SEE IF THEY FIT --------
		
		found = 0;
		for (i=0; i<NUMWORDS; i++){
			if (strcmp(answer, workingWords + i ) == 0){
				 found = 1;
				 struID = i;
			}
		} 
		
		// --------- BLOCK OUT WORDS THAT HAVE BEEN FOUND ------

		if (found){
			wordsFound++;
			if (arrWord[struID].direction == 'D'){
				
				for (i=0; i<strlen(arrWord[struID].word);i++){
					myArray[arrWord[struID].sRow + i][arrWord[struID].sColumn + i] = ' ';
				}
			}
			else if (arrWord[struID].direction == 'H'){
				
				for (i=0; i<strlen(arrWord[struID].word);i++){
					myArray[arrWord[struID].sRow][arrWord[struID].sColumn + i] = ' ';
				}
			}
			else if (arrWord[struID].direction == 'V'){
				
				for (i=0; i<strlen(arrWord[struID].word);i++){
					myArray[arrWord[struID].sRow + i][arrWord[struID].sColumn] = ' ';
				}
			}
			else;
			
			for(i=0; i<WORDLEN; i++){
				workingWords[struID][i] = ' ';
			}
		}
		else{
			printf("Word not found!");
		}
		
		sleep(1);
		
		// ------------ CLEAR SCREEN -----------
		
		system("cls");
	}
	
	if (timeLeft < 1)
		printf("\nTimes up!");
		
	return 0;
}

//Creates a 2D array of WIDTH * HEIGHT and returns a pointer to it
char **create2DArray(){
	
	int i,j;
	char **array = (char **) malloc(sizeof(char *) * WIDTH);
	
	for(i=0; i<WIDTH; i++)
		array[i] = (char *) malloc(sizeof(char) * HEIGHT);
	
	for(i=0; i<WIDTH; i++)
	
		for(j=0; j<HEIGHT; j++){
			array[i][j] = '.';
		}
	return array;
}

// prints the board
void printArray(){
	int i,j;
	printf("\n");
	
 	for(i=0; i<WIDTH; i++){
	
		for(j=0; j<HEIGHT; j++){
			printf("%c ", myArray[i][j]);
		}
		printf("\n");
	}
}

/* fills the board with horizontal, vertical and diagonal words for the
selected list.*/
void wordsToBoard(char *theme){
	int i,j,k,l,m,row,column,usedRow,usedCol,
		select,duplicate,match = 0,used = 0;
	float numOfWords = NUMWORDS;
	char letter;
	int dubRow[30];
	
	// ------------- HORIZONTAL WORDS -----------------
	
	for (i=0; i<(numOfWords * 0.4); i++){
		//printf("\ntest1");
		do{
			duplicate = 0;
			row = rand() % HEIGHT;
			column = rand() % (WIDTH - strlen(theme + i * WORDLEN));
			
			for(k=0; k<30; k++){
				
				if (dubRow[k] == row)
					duplicate = 1;
			}
		}
		while(duplicate);
		
		dubRow[i] = row;
		
		for(j=0; j<strlen(theme + i * WORDLEN); j++){
			myArray[row][column + j] = *((theme + i * WORDLEN) + j);			
		}
		strcpy(arrWord[i].word, (theme + i * WORDLEN));
		arrWord[i].sRow = row;
		arrWord[i].sColumn = column;
		arrWord[i].direction = 'H';
	}
	
	// -------------VERTICAL WORDS------------------
	
	for (i=0; i<(numOfWords * 0.4); i++){
		select = i + (numOfWords * 0.4);
		
		while (1){
			used = 0;
			letter = ' ';
			
			// generate random starting point 
			row = rand() % (HEIGHT - strlen(theme + select * WORDLEN));
			column = rand() % WIDTH;
			
			// checks if there are spaces taken
			for(k=0; k<strlen(theme + select * WORDLEN); k++){
				
				if (myArray[row + k][column] != '.'){
					used++;
					letter = myArray[row + k][column];
					usedRow = row + k;
				}
			}
			
			if (used == 0)
				break;
			/*
			// WAS TO COMPLICATED TO REMOVE FROM BROARD	
			else if (used == 1){
				match = 0;
				// is there a char in common?
				for(l=0; l<strlen(theme + select * WORDLEN); l++){
					if (letter == *((theme + select * WORDLEN) + l)){
						match++;
						row = usedRow - l; 
						if (row >= 0){
							break;
						}
						else{
							continue;
						}
					}
				}
				
				if (match == 1)
					break;
				else
					continue;
			}
			*/
			//are there more than 1 occupied spaces
			else
				continue;
		}
		
		// add word to board
		for(j=0; j<strlen(theme + select * WORDLEN); j++){
			myArray[row + j][column] = *((theme + select * WORDLEN) + j);	
		}
		strcpy(arrWord[select].word, theme + select * WORDLEN);
		arrWord[select].sRow = row;
		arrWord[select].sColumn = column;
		arrWord[select].direction = 'V';
	}
	
	//  -------- Diagonal WORDS top left to bottom right -------
	
	
	for (i=0; i<(numOfWords * 0.2); i++){
		select = i + (numOfWords * 0.8);
		
		while (1){
			used = 0;
			letter = ' ';
			
			//generate a random starting point
			row = rand() % (HEIGHT - strlen(theme + select * WORDLEN));
			column = rand() % (WIDTH - strlen(theme + select * WORDLEN));
			
			// checks if there are spaces taken
			for(k=0; k<strlen(theme + select * WORDLEN); k++){
				
				if (myArray[row + k][column + k] != '.'){
					used++;
					letter = myArray[row + k][column + k];
					usedRow = row + k;
					usedCol = column + k;
				}
			}
			
			// if there are no places taken
			if (used == 0)
				break;
			/*
			// if only one place is taken - Too complicated to remove when found
			else if (used == 1){
				match = 0;
						//printf("\n4");
				// is there a char in common?
				for(l=0; l<strlen(theme + select * WORDLEN); l++){
					if (letter == *((theme + select * WORDLEN) + l)){
						match++;
						row = usedRow - l;
						column = usedCol - l;
						// does the word start before the board does
						if (row >= 0 && column >=0){
							break;
						}
						else{
							continue;
						}
					}
							//printf("\n5");
				}
				if (match == 1){
					break;		
				}
				else{
					continue;
				}
						//printf("\n6");
			}
			*/
			// if there are more than 1 spaces taken
			else
			continue;
					//printf("\n7");
		}
		
		// add word to board
		for(j=0; j<strlen(theme + select * WORDLEN); j++){  
			myArray[row + j][column + j] = *((theme + select * WORDLEN) + j);
		}
		
		strcpy( arrWord[select].word, (theme + select * WORDLEN));
		arrWord[select].sRow = row;
		arrWord[select].sColumn = column;
		arrWord[select].direction = 'D';
	}
	
	// --------- PRINT arrWord STRUCT ------------
	/*
	for (j=0; j<NUMWORDS; j++){
		printf("\n----------printout %d -------------\n", j);
		printf("\n%s", arrWord[j].word);
		printf("\n%d", arrWord[j].sRow);
		printf("\n%d", arrWord[j].sColumn);
		printf("\n%c", arrWord[j].direction);
	}
	*/
	
}
