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
    char nums[20];
    char temp[20];
    int word_count, loops;
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
                tok = strtok(line, " ");
                while(tok){
                    word_count = 0;
                    for(i = 0; i < strlen(tok); i++){
                        while(isdigit(tok[i])){
                            nums[word_count++] = tok[i++];
                        }
                        loops = atoi(nums);
                        for(int d = 0; d < loops; d++){
                            printf("%c", tok[i]);
                        }
                    }
                tok = strtok(NULL, " ");
                memset(nums, 0,sizeof(nums));
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

