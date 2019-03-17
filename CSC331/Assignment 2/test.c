#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void change_directory(char *cmd);
char* has_access(char *cmd);
void interactive_mode();
void update_path(char *cmd);
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
    char *firstToken, *secondToken, *newline;
    newline = strchr(cmd, '\n');
    if(newline) *newline = 0;
    firstToken = strtok_r(cmd, " ", &cmd);
    secondToken = strtok_r(cmd, " ", &cmd);
    if( strtok_r(cmd, " ", &cmd) != NULL){
        error();
        return;
    }
    if( (chdir(secondToken)) != 0 ){
        error();
        return;
    }
    return;
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

void update_path( char *cmd){
    char **arguments = (char*)malloc(50*sizeof(char*)); //50 elements
    char *token;
    size_t count = 0;

    strtok_r(cmd, " ", &cmd); //Move the pointer past the "path" command 
    while( (token = strtok_r(cmd, " ", &cmd)) != NULL){
        arguments[count++] = (char*)malloc(strlen(token)*sizeof(char));
    }

    PATH = (char**)realloc(PATH, ++count*sizeof(char*));
    for(int a = 0; a < count; a++){
        
    }
    free(arguments);
    return;
}

void error(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
}

void parallel_commands(char *cmd){
    char *token1, *token2;
    return;
}

void execute_command(char *cmd){
    char *token, *path;
    int count = 0;
    pid_t pid;
    int status;
    char **arguments = (char**)malloc(5*sizeof(char*)); //Dimension for 15 elements
    token = strtok_r(cmd, " ", &cmd);
    if( (path = has_access(token)) != NULL){
        arguments[count] = (char*)malloc(strlen(token)*sizeof(char));
        strcpy(arguments[count], token); 
        count++;
    }
    while( (token = strtok_r(cmd, " ", &cmd)) != NULL){
        arguments[count] = (char*)malloc(strlen(token)*sizeof(char));
        strcpy(arguments[count], token);
        count++;
    }
    pid = fork();
    if(pid == 0){
        execv(path, arguments);
    }
    else{
        waitpid(pid, &status ,WNOHANG|WUNTRACED);
    }
    return;
}

void interactive_mode(){
    char *cmd = NULL;
    char *token, *newline;
    size_t len = 0;
    size_t count;
    
    while(1){
        printf("grsh> ");
        getline(&cmd, &len, stdin);
        newline = strchr(cmd, '\n');
        
        if(newline) *newline = 0;
        token = strtok_r(cmd, " ", &cmd);
        
        if(strstr(token, "exit")){
            exit(0);
        }
        if(strstr(token, "cd")){
            change_directory(cmd);
        }
        if(strstr(token, "path")){
            update_path(cmd);
        }
        if(strstr(token, "&")){
            parallel_commands(cmd);
        }
    }
    exit(0);
}