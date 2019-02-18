#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    FILE *fp;
    int i;
    char *line = NULL;
    size_t len = 0;
    ssize_t = nread;
    char n[15];
    const char s[1000];

    if(argc < 2){
        printf("my-unzip: file1 [file2 ...] \n");
        return(1);
    }
    int a;
    for(a = 1; a < argc; a++){
        fp = fopen(argv[a], "r");
        if(fp != NULL){
            while( (nread = getline(&line, &len, fp)) != -1){
                strcpy(s, line);
                char* token = strtok(s, " ");
                while(token){
                    int a, c, count, i;
                    c = 0;
                    while(isdigit(token[i])){
                        n[c] = token[i];
                        c++;
                        i++;
                    }
                    count = atoi(n);
                    for(a = 1; a <= count; a++){
                        printf("%c", token[i]);
                    }
                    memset(n, 0, sizeof(n));
                    printf(" ");
                    token = strtok(NULL, " ");
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

