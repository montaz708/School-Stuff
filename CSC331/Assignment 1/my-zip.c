#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
int main(int argc, char *argv[]){

	FILE *fp;
	uint8_t character, new_character;
	uint8_t count = 1;
	if(argc < 2){
		printf("my-zip: file1 [file2 ...] \n");
		return(1);
	}
	/*Since one of the requirements was storing the character in it's ASCII value
	I read online that storing the character in a uint8_t variable would store it that way,
	which is why I use getc and that data type to store the character.*/
	for(int a = 1; a < argc; a++){
		fp = fopen(argv[a], "r");
		if(fp != NULL){
			character = fgetc(fp); //Read in the first character to do a comparison on the next
			count = 0;
			do{
				new_character = fgetc(fp); //Read in the next character from specified file
				if( feof(fp) ){ // Conditional statement for breaking out of infinite loop (if end of file{break})
					break;
				}
				if(character == new_character){ //If they're equal, increment a counter to keep track of how many there are
					count++;
				}
				else{ // When the comparison is no longer equal between two characters, write to stdout
					fwrite(&count, 4, 1, stdout); // Write the value at count, allocating four bytes, written only once, to stdout
					fwrite(&character, 1, 1, stdout);
					character = new_character; // Read in the next character, reset count and continue looping
					count = 0;
				}
			}while(1); // Loop for interating over all characters of a file
		}
		else{
			printf("Could not open %s for compressing!", argv[a]); //Handles the case where an invalid file path was passed
			return(1);
		}
		fclose(fp);
	}
	return(0);
}
