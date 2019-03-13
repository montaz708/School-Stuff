#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

void change_directory(char *cmd);
char* has_access(char *cmd);
void interactive_mode();
void update_path(char *new_path);
void error();
char **PATH;

int main(int argc, char* argv[]){
    PATH = (char**)malloc(sizeof(char*));
    PATH[0] = (char*)malloc(sizeof("/bin/"));
    strcpy(PATH[0], "/bin/");

    if(argc < 2){
        interactive_mode();
    }
    free(PATH);
}

void change_directory(char *cmd){
    char *token, cwd[256];
    strtok_r(cmd, " ", &cmd);
    token = strtok_r(cmd, " \n", &cmd);
    if( (chdir(token)) != 0 ){
        printf("Couldn't change directory: %s \n", token);
    }
}

char* has_access(char *cmd){
    char *temp;
    char *newline = 0;
    for(int i = 0; i < sizeof(PATH)/sizeof(PATH[0]); i++){
        strcpy(temp, PATH[i]);
        newline = strchr(cmd, '\n');
        if (newline) *newline = 0;
        strcat(temp, cmd);
        if( (access(temp, X_OK)) == 0 ){
            return temp;
        }
    }
    error();
    return NULL;
}

void update_path(int num_args, char **new_path){
    size_t size;

    PATH = (char**)realloc(num_args*sizeof(char*));
    for(int a = 0; a < num_args; a++){
        PATH[a] = (char*)realloc(PATH[a], sizeof(new_path[a]));
        strcpy(PATH[a], new_path[a]);
    }
}

void error(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
}

void interactive_mode(){
    char *cmd = NULL;
    char *token, *path, **arguments;
    size_t len = 0;
    size_t count;
    
    while(1){
        printf("grsh> ");
        getline(&cmd, &len, stdin);
        token = strtok_r(cmd, " ", &cmd);
        if(strstr(token, "exit")){
            exit(0);
        }
        if(strstr(token, "cd")){
            change_directory(cmd);
        }
        if( (path = has_access(token)) != NULL){
            count = 0;
            arguments[count] = (char *)calloc(strlen(token) + 1, sizeof(char));
            strcpy(arguments[count], token);
            while(token != NULL){
                token = strtok_r(NULL, " ", &cmd);
                count++;
                arguments[count] = (char *)calloc(strlen(token), sizeof(char));
                strcpy(arguments[count], token);
            }
            arguments[++count] = NULL;
            execv(path, arguments);
        }
        free(arguments);
    }
    exit(0);
}