//https://overiq.com/c-programming-101/array-of-strings-in-c/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **create2DArray(); //function prototype
void printArray();

#define WIDTH 20
#define HEIGHT 20
#define WORDLEN 22
#define NUMWORDS 10

char **myArray; //global array

int main(int argc, char *argv[]) {
	
	srand(time(0));
	
	int i,j,k,select,wordsFound = 0;
	char *theme;
	char name[10];
	char answer[WORDLEN];
	
	char celestialObjects[22][WORDLEN] = {
									"MERCURY", "VENUS", "EARTH", "MOON", "MARS",
									"DAIMOS", "PHOBOS", "ASTEROIDBELT",
									"CERES", "PALLAS", "JUNO",
									"VESTA", "JUPITER", "EUROPA", "GANYMEGE",
									"CALLISTO", "SATURN", "URANUS",
									"NEPTUNE", "PLUTO", "SUN"
									};
									
	char rockets[13][WORDLEN] = {
							"SATURNV", "N1", "SPACESHUTTLE", "FALCONHEAVY", 
							"ARES1-X", "ARIANE4", "ATLASV", "ANGARAA5", 
							"DELTAVHEAVY", "DELTAVMEDIUM", "FALCON9", "SOYUZ", 
							"LONGMARCH2F"
							};
							
	char marsRobots[15][WORDLEN] = {
								"VIKING1", "VIKING2", "PATHFINDER", "SPIRIT",
								"OPPORTUNITY", "PHOENIX", "CURIOSITY",
								"INSIGHT", "GLOBALSURVEYOR", "ODYSSEY",
								"EXPRESS", "RECONNAISSANCE", "ORBITERMISSION",
								"MAVEN", "EXOMARSTRACEGAS"
								};
 	
 	myArray = create2DArray();
 	
 	printf("\n---------------------------------------");
 	printf("\n|                                     |");
 	printf("\n|     Welcome to Word Search 3000     |");
 	printf("\n|                                     |");
 	printf("\n---------------------------------------");
 	
 	printf("\n\nWhat is your name? ");
 	scanf("%s", &name); getchar();
 	
 	printf("\nHello %s! Please select a category : \n\n   (1) Celestial objects in our solar system\n   (2) Rockets\n   (3) Robots on or orbiting Mars\n\n", name);
 	scanf("   %d", &select); getchar();
	
	if (select == 1){
		//theme = &celestialObjects[0][0];
		wordsToBoard((char *)celestialObjects);
		printf("\nCategory: Celestial objects in our solar system");
	}
	else if (select == 2){
		//theme = &rockets[0][0];
		wordsToBoard((char *)rockets);
		printf("\nCategory: Rockets");
		}
	else if (select == 3){
		//theme = &marsRobots[0][0];
		wordsToBoard((char *)marsRobots);
		printf("\nCategory: Robots on or orbiting Mars");
	}
	else;
	
	// FILL IN RANDOM LETTERS 
	/*
	for(i=0; i<WIDTH; i++){
	
		for(j=0; j<HEIGHT; j++){
			
			if (myArray[i][j] == '.'){
				// printf("test --- i: %d j : %d", i, j);   // DEBUG
				myArray[i][j] = 65 + rand() % 25;
			}
		}
	}
	*/
	
	printf("\n\nOk %s - There are %d words hidden in this grid.", name, NUMWORDS);
	printf("\nCan you find them all?");
	printf("\nYou have 2 minutes!"); 
	
	printArray();
	
	printf("\n%d Words left", NUMWORDS - wordsFound);
	printf("\nYou have %0.2f (COMPLETE) seconds", 1.596857);
	printf("\nWord : ");
	scanf("%s", &answer); getchar();
	
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
			
			//array[i][j] = 65 + rand() % 25;
			array[i][j] = '.';
		}
	return array;
}

void printArray(){
	int i,j;
	printf("\n\n");
 	for(i=0; i<WIDTH; i++){
	
		for(j=0; j<HEIGHT; j++){
			printf("%c ", myArray[i][j]);
		}
		
		printf("\n");
	}
}

void wordsToBoard(char *theme){
	
	int i,j,k,l,m,row,column,usedRow,usedCol,select,duplicate,match = 0,used = 0;
	float numOfWords = NUMWORDS;
	char letter;
	int dubRow[30];
	
	
	struct wordsInBox {
		char word[WORDLEN];
		int sRow;
		int sColumn;
		char direction;
	};
	
	struct wordsInBox arrWord[NUMWORDS];
	/*
	strcpy( arrWord[0].word, theme);
	 
	printf("\n\n\n------- %s -------", arrWord[0].word);
	*/
	
	// ------------- HORIZONTAL WORDS -----------------
	
	for (i=0; i<(numOfWords * 0.4); i++){
		printf("\ntest1");
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
			
			printf("\ntest strcpy");
			strcpy(arrWord[i].word, (theme + i));
			arrWord[i].sRow = row;
			arrWord[i].sColumn = column;
			arrWord[i].direction = 'H';
			
		}
		
		for (k=0;k<4;k++){
			printf("\n%s", arrWord[k + i * WORDLEN].word);
			printf("\n%d", arrWord[k].sRow);
			printf("\n%d", arrWord[k].sColumn);
			printf("\n%c", arrWord[k].direction);
		}
	}
	
	// -------------VERTICAL WORDS------------------
	
	for (i=0; i<(numOfWords * 0.4); i++){
		printf("test2");
		select = i + 1 + (numOfWords * 0.4);
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
			
			//are there more than 1 occupied spaces
			else
				continue;
		}
		
		// add word to board
		for(j=0; j<strlen(theme + select * WORDLEN); j++){
			myArray[row + j][column] = *((theme + select * WORDLEN) + j);
			printf("\ntest strcpy");
			strcpy(arrWord[select].word, (theme + select));
			arrWord[select].sRow = row;
			arrWord[select].sColumn = column;
			arrWord[select].direction = 'H';	
		}
		
		for (k=0;k<4;k++){
			printf("\n%s", arrWord[select].word);
			printf("\n%d", arrWord[select].sRow);
			printf("\n%d", arrWord[select].sColumn);
			printf("\n%c", arrWord[select].direction);
		}
	}
	
	// Diagonal WORDS top left to bottom right
	for (i=0; i<(numOfWords * 0.2); i++){
		select = i + 1 + (numOfWords * 0.8);
		printf("test3");
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
			// if only one place is taken
			else if (used == 1){
				match = 0;
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
				}
				if (match == 1){
					break;		
				}
				else{
					continue;
				}
			}
			// if there are more than 1 spaces taken
			else
			continue;
		}
		
		// add word to board
		for(j=0; j<strlen(theme + select * WORDLEN); j++){  
			myArray[row + j][column + j] = *((theme + select * WORDLEN) + j);
			/*
			strcpy( arrWord[select].word, (theme + select));
			strcpy( arrWord[select].sRow, row);
			strcpy( arrWord[select].sColumn, column);
			strcpy( arrWord[select].direction, 'D');
			*/
		}
	}
	
	for (i=0;i<10;i++){
		printf("\n----------printout -------------\n");
		printf("\n%s", arrWord[i + i * WORDLEN].word);
		printf("\n%d", arrWord[i].sRow);
		printf("\n%d", arrWord[i].sColumn);
		printf("\n%c", arrWord[i].direction);
	}
}
