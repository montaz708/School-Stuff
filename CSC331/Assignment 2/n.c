#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

char **PATH;
void update_path(char *cmd);

int main(int argc, char *argv[]){
    PATH = (char**)malloc(15*sizeof(char*));
    PATH[0] = (char*)malloc(strlen("/bin/")*sizeof(char));
    strcpy(PATH[0], "/bin/");
    char *cmd = NULL, *newline = 0;
    char *token, *path;
    char **arguments = (char**)malloc(20*sizeof(char*));
    size_t len = 0;
    size_t count=0;
    int num = 0;
    
    while(1){
        printf("grsh> ");
        getline(&cmd, &len, stdin);
        newline = strchr(cmd, '\n');
        if (newline) *newline = 0;
        if(strstr(cmd, "exit")){
            exit(0);
        }
        if( strstr(cmd, "path")){
            update_path(cmd);
        }
        
        while(PATH[num] != NULL){
            printf("%s \n", PATH[num]);
            num++;
        }
        printf("\n");
        
    }
    return 0;
}


void update_path( char *cmd){
    char **arguments;
    char *token;
    size_t count = 0;
    
    arguments = &PATH;
    strtok_r(cmd, " ", &cmd); //Move the pointer past the "path" command 
    while( (token = strtok_r(cmd, " ", &cmd)) != NULL){
        arguments[count] = (char*)malloc(strlen(token)*sizeof(char));
        strcpy(arguments[count], token);
        count++;
    }
    return;
}