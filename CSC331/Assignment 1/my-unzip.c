#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    int i;
    char *line = NULL;
    size_t len = 0;
    ssize_t  nread;
    char *nums[20];
    int word_count;
   char *tok;

    if(argc < 2){
        printf("my-unzip: file1 [file2 ...] \n");
        return(1);
    }
    int a;
    for(a = 1; a < argc; a++){
        fp = fopen(argv[a], "r");
        if(fp != NULL){
            while( (getline(&line, &len, fp)) != -1){
                for(tok = strtok(line, " "); tok && *tok; tok = strtok(NULL, " ")){
                    for(i = 0; i < strlen(tok); i++){
                        if(isdigit(tok[i])){
                            nums[word_count++] = tok[i];
                        }
                        else{
                            for(int b = 0; b < atoi(nums); b++){
                                printf("%c", tok[i]);
                            }
                            word_count = 0;
                            strcpy(nums, "");
                        }
                    }
                    printf(" ");
                }
            printf("\n");
            }
        }
        else{
            printf("Could not read %s for file decompression!", argv[a]);
        }
        fclose(fp);
    }
    return(0);
}

