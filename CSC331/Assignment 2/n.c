#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char *token;
    char *cmd = NULL;
    size_t len = 0;

    while(1){
        printf("grsh> ");
        getline(&cmd, &len, stdin);
        for(token = strtok_r(cmd, " ", &cmd);
            token != NULL;
            token = strtok_r(NULL, " ", &cmd)){
            printf("%s \n", token);
        }
    }



}