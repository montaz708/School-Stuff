#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 1000
int main(int argc, char* argv[]){
    char str[MAXCHAR];
    if(argc == 1)
        printf("my-grep: searchterm [file ...]");
        exit(1);
    if(argc >= 2){
        int counter = 2;
        FILE *fptr;
        char* search;
        strcpy(search, (char*)argv[1]);
        do{
            if((fptr = fopen(argv[counter], "r")) == NULL){
                printf("my-grep: cannot open file \n");
                exit(1);
            }
            while(fgets(str, MAXCHAR, fptr) != NULL){
                if(str == search){
                    printf("%s",str);
                }
            }
            counter++;
        }while(counter < argc);
    }
}