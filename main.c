/* 
 * File:   Lab9.c
 * Author: Arjun Mittal
 *
 * Created on April 3, 2017, 6:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 1024
#define MAX_LIBRARY_SIZE 100

//Defining Struct
typedef struct song {
    
    char songName[MAX_LENGTH] ;
    char artist[MAX_LENGTH] ;

} Song ;

//PrintStatments
// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}

void songNameDuplicate(char songName[]){
    
    printf("\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n", songName);
    
}

//Getting User Input
void getStringFromUserInput(char s[], int maxStrLength) {
    
    int i = 0;
    char c;

    while (i < maxStrLength && (c = getchar()) != '\n')
      s[i++] = c;

    s[i] = '\0';
}

//Initializing the beginning of songName and artist to 0, indicating
//this portion of the array is empty
void initializeArray(Song library[], int size){
    
    for(int i = 0; i < size; i++){
        
        library[i].songName[0] = 0;
        library[i].artist[0] = 0;  
        
    }
    
}

//Prints the library 
void printList (Song library[], int size) {
    
    bool donePrinting = false; 
    
    for(int i = 0; (i < size) && (!donePrinting); i++) {
                
        if ((i == 0) && (library[i].songName[0] == 0) && (library[i].artist[0] == 0)) {
            
            printMusicLibraryEmpty (); 
            donePrinting = true; 
            
        }
        
        else if ((library[i].songName[0] == 0) && (library[i].artist[0] == 0)){
            
            donePrinting = true; 
            
        }
        
        else {
            
            if(i == 0){
                
                printf("\nMy Personal Music Library: \n");
            
            }
            
            printf("\n"); 
            printf("%s \n", library[i].songName); 
            printf("%s \n", library[i].artist); 

        }
        
    }
    
}

//Inserting user entered element into the end of the list 
void insertElement(Song library[], int size, char input [], int maxStrLength){
    
    bool notInserted = true; 
    char input1[MAX_LENGTH];
    
    printf("Song name: ");
    getStringFromUserInput (input, maxStrLength);
    
    for (int i = 0; (i < size) && (notInserted) ; i++){
        
        //checks for duplicate entry
        int j = 0; 
        while((library[j].songName[0] != 0) && (j < size)) {
            
            if (strcmp(input, library[j].songName) == 0) {
            
                strcpy(input1, input); 
                printf("Artist: ");
                getStringFromUserInput(input, maxStrLength);
                songNameDuplicate(input1); 
                notInserted = false; 
            }
            
            j++; 
        }
                        
        //checks intitial character of array position ensuring section is empty before inserting
        if((library[i].songName[0] == 0) && (library[i].artist[0] == 0) && (notInserted)){
            
            strcpy(library[i].songName, input); 
                        
            printf("Artist: ");
            getStringFromUserInput(input, maxStrLength);
            strcpy(library[i].artist, input); 
            
            notInserted = false; 

        }
        
        
    }
    
    
}

//Counts the number of elements in the array
int numberOfItems(Song library[], int size){
    
    int items = 0; 
    int counter = 0; 
    bool doneCounting = false; 
    
    while((counter < size) && (!doneCounting)) {
        
        if((library[counter].songName[0] == 0) && (library[counter].artist[0] == 0)){
            doneCounting = true; 
        }
        
        else{
            items++; 
            counter++; 
        }
        
    }
    
    return items; 
    
}

//cocktail sorts the array
void cocktailSort( Song library[], int size ){
    
    //Used for swaps
    Song temp [1]; 
    bool swaps = true;
    bool swapForward = true; 
    bool swapBackward = true; 
    int items = 0; 
    int alphaOrder = 0; 
    int front = 0; 
    
    items = numberOfItems(library, size); 
    
    //ensures list is not empty
    if (items != 0){
        
        for(int top = items - 1; (top > front) && (swaps); top--){
            
            swaps = false; 
            swapForward = false; 
            swapBackward = false; 
        
            //First iteration moving artists names to the back in ascending order
            for(int i = front; i < top; i++){
                
                alphaOrder = strcmp(library[i].artist, library[i+1].artist); 
            
                //Second artist name is less than first and needs to be swapped 
                if(alphaOrder > 0) {
                    //copy into temporary position
                    strcpy(temp[0].songName, library[i].songName); 
                    strcpy(temp[0].artist, library[i].artist); 
                    
                    //copy next element into current position
                    strcpy(library[i].songName, library[i+1].songName); 
                    strcpy(library[i].artist, library[i+1].artist); 
                    
                    //copies next element from temp
                    strcpy(library[i+1].songName, temp[0].songName); 
                    strcpy(library[i+1].artist, temp[0].artist); 
                    
                    swapForward = true; 
                    
                }
                
                //sorting based on song name if the artist is the same
                if(alphaOrder == 0) {
                    
                    alphaOrder = strcmp(library[i].songName, library[i+1].songName);
                    
                    if(alphaOrder > 0) {
                    
                        //copy into temporary position
                        strcpy(temp[0].songName, library[i].songName); 
                        strcpy(temp[0].artist, library[i].artist); 
                    
                        //copy next element into current position
                        strcpy(library[i].songName, library[i+1].songName); 
                        strcpy(library[i].artist, library[i+1].artist); 
                    
                        //copies next element from temp
                        strcpy(library[i+1].songName, temp[0].songName); 
                        strcpy(library[i+1].artist, temp[0].artist); 
                    
                        swapForward = true; 
                    
                    }
                    
                }
                
            }
            
            //second iteration moving artists names forward in descending order
            for(int j = top; j > front; j--) {
                
                alphaOrder = strcmp(library[j].artist, library[j-1].artist); 
                
                if(alphaOrder < 0) {
                    
                    //copy into temporary position
                    strcpy(temp[0].songName, library[j-1].songName); 
                    strcpy(temp[0].artist, library[j-1].artist); 
                    
                    //copy next element into current position
                    strcpy(library[j-1].songName, library[j].songName); 
                    strcpy(library[j-1].artist, library[j].artist); 
                    
                    //copies next element from temp
                    strcpy(library[j].songName, temp[0].songName); 
                    strcpy(library[j].artist, temp[0].artist); 
                    
                    swapBackward = true; 
                    
                }
                
                //sorting based on song name if the artist is the same
                if(alphaOrder == 0) {
                    
                    alphaOrder = strcmp(library[j].songName, library[j-1].songName); 
                    
                        if(alphaOrder < 0) {
                    
                        //copy into temporary position
                        strcpy(temp[0].songName, library[j-1].songName); 
                        strcpy(temp[0].artist, library[j-1].artist); 
                    
                        //copy next element into current position
                        strcpy(library[j-1].songName, library[j].songName); 
                        strcpy(library[j-1].artist, library[j].artist); 
                    
                        //copies next element from temp
                        strcpy(library[j].songName, temp[0].songName); 
                        strcpy(library[j].artist, temp[0].artist); 
                    
                        swapBackward = true; 
                    
                    }
                    
                }

                
            }
            
            front++; 
            if (swapForward || swapBackward){
                swaps = true; 
            }
            
        
        }
    
    }
}

//Main function
int main(int argc, char** argv) {

    Song Library [MAX_LIBRARY_SIZE];
    
    initializeArray(Library, MAX_LIBRARY_SIZE); 
    
      // Announce the start of the program
    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), S (sort by artist), P (print), Q (quit).\n");
    
    char response;
    char input[MAX_LENGTH + 1];
    
    do {
        printf("\nCommand?: ");
        getStringFromUserInput(input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        //Inserts element into the end of the list 
        if (response == 'I') {
            
            insertElement (Library, MAX_LIBRARY_SIZE, input, MAX_LENGTH);          
            
            
        }
        else if (response == 'S') {
            
            //Sorts array
            cocktailSort(Library, MAX_LIBRARY_SIZE);
            printList(Library, MAX_LIBRARY_SIZE);


        }
        else if (response == 'P') {
           
            //Print the music library
            printList(Library, MAX_LIBRARY_SIZE);
            

        }
        else if (response == 'Q') {
            ; // do nothing, we'll catch this below
            
        }
        else {
            // do this if no command matched ...
            printf("\nInvalid command.\n");
            
        }
    } while (response != 'Q');
  
    return 0;

    
    return (EXIT_SUCCESS);
}
