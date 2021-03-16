//https://overiq.com/c-programming-101/array-of-strings-in-c/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **create2DArray(); //function prototype

#define WIDTH 20
#define HEIGHT 20

char **myArray; //global array

int main(int argc, char *argv[]) {
	
	srand(time(0));
	
	int i,j,k,l,m,row,column,usedRow,duplicate,match = 0,select,letterPlace,used = 0,fits = 0,wordLen = 22;
	float numOfWords = 10;
	char *theme;
	char letter;
	int dubRow[30];
	
	char celestialObjects[22][22] = {
									"mercury", "venus", "earth", "moon",
									"mars", "deimos", "phobos",
									"asteroidbelt", "ceres", "pallas",
									"juno", "vesta", "jupiter", "europa",
									"ganymede", "callisto", "saturn",
									"uranus", "neptune", "pluto", "sun"
									};
									
	char rockets[13][22] = {
							"saturnv", "n1", "spaceshuttle", "falconheavy",
							"ares1-x", "ariane4", "atlasv", "angaraa5",
							"deltaivheavy", "deltaivmedium", "falcon9", "soyuz",
							"longmarch2f"
							};
							
	char marsRobots[15][22] = {
								"viking1", "viking2", "pathfinder",
								"spirit", "opportunity", "phoenix",
								"curiosity", "insight", "globalsurveyor",
								"odyssey", "express", "reconnaissance",
								"orbitermission", "maven", 
								"exomarstracegas"
								};
 	
 	myArray = create2DArray();
 	
 	printf("\nSelect a category : \n   (1) Celestial objects in our solar system\n   (2) Rockets\n   (3) Robots on or orbiting Mars\n\n");
 	scanf("   %d", &select); getchar();
	
	if (select == 1)
		theme = &celestialObjects[0][0];
	else if (select == 2)
		theme = &rockets[0][0];
	else if (select == 3)
		theme = &marsRobots[0][0];
	else;
	
	// HORIZONTAL WORDS
	for (i=0; i<(numOfWords / 100) * 40; i++){
		
		do{
			duplicate = 0;
			row = rand() % HEIGHT;
			column = rand() % (WIDTH - strlen(theme + i * wordLen));
			
			for(k=0; k<30; k++){
				
				if (dubRow[k] == row)
					duplicate = 1;
			}
		}
		while(duplicate == 1);
		
		dubRow[i] = row;
		
		for(j=0; j<strlen(theme + i * wordLen); j++){
			myArray[row][column + j] = *((theme + i * wordLen) + j);
		}
	}
	
	printf("\ntest1 - (numOfWords / 100) * 40 : %f", (numOfWords / 100) * 40);
	
	// VERTICAL WORDS
	for (i=0; i<(numOfWords / 100) * 40; i++){
		fits = 0;
		
		printf("\ntest2 - if loop");
		select = i + 1 + (numOfWords / 100) * 40;
		while (fits == 0){
			used = 0;
			letter = ' ';
			
			// generate random starting point 
			printf("\ntest3 - while loop");
			row = rand() % (HEIGHT - strlen(theme + select * wordLen));
			column = rand() % WIDTH;
			
			// checks if there are spaces taken
			for(k=0; k<strlen(theme + select * wordLen); k++){
			
				printf("\n%s", theme + select * wordLen);	
				printf("\ntest4 - checks if there are spaces taken\nmyArray[row + j][column] : '%c' - used : '%d' - letter : '%c'", myArray[row + k][column], used, letter);
				if (myArray[row + k][column] != '.'){
					
					printf("\ntest5 ----");
					used++;
					letter = myArray[row + k][column];
					usedRow = row + k;
				}
			}
			
			// if yes
				//break;
			printf("\ntest7");
			if (used == 0){
				
				printf("\ntest8 - used == 0 ");
				fits = 1;
				break;
			}
			// if no
			
			/*
			else{
				continue;
			}
			*/
			
			else if (used){
				match = 0;
				printf("\ntest10 - used == 1");
				// is there a char in common?
				for(l=0; l<strlen(theme + select * wordLen); l++){
					
					printf("\ntest11 - *((theme + select * wordLen) + l : %c - l : '%d' - letter : '%c'", *((theme + select * wordLen) + l), l, letter);
					if (letter == *((theme + select * wordLen) + l)){
						
						letterPlace = l;
						match++;
						row = usedRow - letterPlace; 
						if (row >= 0){
							printf("\ntest12 - letterPlace : %d - match : %d", letterPlace, match);
							break;
						}
						else{
							continue;
						}
					}
					
					printf("\ntest13");
				}
				
				if (match > 0){
					
					printf("\ntest14");
					fits = 1;
					break;		
				}
					// if no
						//continue;
				else{
					
					printf("\ntest16");
					continue;
				}
			}
			
			//are there more than 1 ocupied spaces
			else{
				printf("\ntest17");
				continue;
			}
		}
		
		// add word to board
		printf("\ntest18");
		for(j=0; j<strlen(theme + select * wordLen); j++){
			myArray[row + j][column] = *((theme + select * wordLen) + j);
		}
		
		printf("\ntest19");
		// PRINTS SQUARE
		printf("\n");
	 	for(m=0; m<WIDTH; m++){
		
			for(j=0; j<HEIGHT; j++){
				printf("%c ", myArray[m][j]);
			}
			printf("\n");
		}
	}
	
	
	// Diagonal WORDS top left to bottom right
	for (i=0; i<(numOfWords / 100) * 20; i++){
		select = i + (numOfWords / 100) * 80;
		row = rand() % (HEIGHT - strlen(theme + select * wordLen));
		column = rand() % (WIDTH - strlen(theme + select * wordLen));
		
		for(j=0; j<strlen(theme + select * wordLen); j++){  
			myArray[row + j][column + j] = *((theme + select * wordLen) + j);
		}
	}
	
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
	
	// PRINTS SQUARE
	printf("\n");
 	for(i=0; i<WIDTH; i++){
	
		for(j=0; j<HEIGHT; j++){
			printf("%c ", myArray[i][j]);
		}
		printf("\n");
	}
	
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


