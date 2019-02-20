#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 1000
int main(int argc, char* argv[]){
    char str[MAXCHAR];
    if(argc == 1){ //Handles the case where no arguments were passed
        return 0;
    }
    if(argc > 1){
        int counter = 1;
        FILE *fptr;
        do{
            if((fptr = fopen(argv[counter], "r")) == NULL){ //Handles the case where an invalid file name was passed.
                printf("my-cat: cannot open file \n");
                exit(1);
            }
            while (fgets(str, MAXCHAR, fptr) != NULL){  //Loop through the strings of the file until a null pointer is returned. Print to stdout the string
                printf("%s", str);
            }
            fclose(fptr);
            counter++;
        }while(counter < argc); //Loop established to print out multiple file contents
    }
    return 0;
}
