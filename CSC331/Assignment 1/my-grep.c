#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char* argv[]){
    char *line = NULL;
    char *word = NULL;
    size_t len = 0;
    ssize_t nread;
    FILE *fptr;

    if(argc == 1){
        printf("my-grep: searchterm [file ...] \n");
        exit(1);
    }
    else if(argc == 2){
        word = (char *)calloc(strlen(argv[1]), sizeof(char*));
        strcpy(word, argv[1]);
        printf("Type a line to search: ");
        line = (char *)calloc(9999, sizeof(char*));
        scanf("%[^\n]%*c", line);
        if(strstr(line, word) != NULL){
            printf("\n %s \n", line);
            return 0;
        }

        free(word);
        free(line);
    }
    else if(argc > 2){
        int counter = 2;
        word = (char *)calloc(strlen(argv[1]), sizeof(char*));
        strcpy(word, argv[1]);
        if(word == " "){
            return 0;
        }
        if(word == ""){
            return 0;
        }
        do{
            fptr = fopen(argv[counter], "r");
            while((nread = getline(&line, &len, fptr)) != -1){
                if(strstr(line, word) != NULL){
                    printf("%s", line);
                }
            }
            fclose(fptr);
            counter++;
        }while(counter < argc);
        free(line);
        free(word);
        return 0;
    }
}
