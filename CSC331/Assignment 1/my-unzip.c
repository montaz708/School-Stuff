#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    FILE *fp;
    uint8_t character;
    uint8_t count;

    if(argc < 2){
        printf("my-unzip: file1 [file2 ...] \n");
        return(1);
    }
    for(int a = 1; a < argc; a++){ //Iterate for all files passed from stdin
        fp = fopen(argv[a], "r"); //Open file for reading
        if(fp != NULL){
            do{
                fread(&count, 4, 1, fp); //Read from open file the first integer, and the character
                fread(&character, 1, 1, fp);
                if( feof(fp)){ // If EOF, break from infinite loop
                    break;
                }
                for(int b = 0; b <= count; b++){ //For duration of count, print inline the character that was read.
                    fputc(character, stdout);
                }

            }while(1);
        }
        else{
            printf("Could not read %s for file decompression!", argv[a]); //Handles the case that a file cannot be opened.
        }
        fclose(fp);
    }
    return(0);
}

