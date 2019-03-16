#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <wait.h>

char* has_access(char *cmd);
char path[20] = "/bin/";

int main(int argc, char *argv[]){
    char *cmd = NULL;
    char *token, *path, **arguments[10][256];
    size_t len = 0;
    size_t count;
    pid_t pid;
    
    while(1){
        printf("grsh> ");
        getline(&cmd, &len, stdin);
        token = strtok_r(cmd, " ", &cmd);
        if(strstr(cmd, "exit")){
            exit(0);
        }
        count = 0;
        strcpy(arguments[count++], &token);
        while(token != NULL){
            token = strtok_r(cmd, " \n", &cmd);
            strcpy(arguments[count++], &token);
        }
        strcat(path, arguments[0]);
        strcpy_s(arguments[count++], NULL);
        pid = fork();
        if(pid < 0){
            printf("There was a problem forking. \n");
            exit(0);
        }
        if(pid == 0){
            execv(path, arguments);
        }
    }
    return 0;
}

char* has_access(char *cmd){
    char *temp;
    char *newline = 0;
    for(int i = 0; i < sizeof(PATH)/sizeof(PATH[0]); i++){
        strcpy(temp, PATH);
        newline = strchr(cmd, '\n');
        if (newline) *newline = 0;
        strcat(temp, cmd);
        if( (access(temp, X_OK)) == 0 ){
            return temp;
        }
    }
    return NULL;
}