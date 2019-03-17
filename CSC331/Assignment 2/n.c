#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void error();
char* has_access(char** path, char *cmd);
char** update_path(char *cmd);
char** make_array(char *cmd);
int execute_commands(char** path, char** arguments);
void change_directory(char *cmd);


int main(int argc, char *argv[]){
    char *cmd = NULL;
    ssize_t len = 0;
    char **arguments;
    int buffer = 10;
    int indicator;
    char **path = (char**)malloc(buffer*sizeof(char*));
    path[0] = (char*)malloc(strlen("/bin/")*sizeof(char));
    strcpy(path[0], "/bin/");
    path[1] = NULL;
    do{
        printf("grsh> ");
        getline(&cmd, &len, stdin); 
        if(strstr(cmd, "path")){
            path = update_path(cmd);
            continue;
        }
        if(strstr(cmd, "exit")){
            exit(0);
        }
        if(strstr(cmd, "cd")){
            change_directory(cmd);
            continue;
        }
        arguments = make_array(cmd);
        indicator = execute_commands(path, arguments);
        printf("\n");
    }while(indicator);
    return 0;
}

void error(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
}

char* has_access(char **path, char *cmd){
    char *temp;
    int count = 0;
    char *newline = 0;
    while(path[count] != NULL){
        strcpy(temp, path[count]);
        newline = strchr(cmd, '\n');
        if (newline) *newline = 0;
        strcat(temp, cmd);
        if( (access(temp, X_OK)) == 0 ){
            return temp;
        }
        count++;
    }
    error();
    return NULL;
}

char** update_path(char *cmd){
    char **path, **arguments;
    int count = 0, other_count = 1; //Start at index 0 for path and start at index 1 for arguments to omit the first element
    int items = 10;
    arguments = make_array(cmd);
    path = (char**)malloc(items*sizeof(char*));

    while(arguments[other_count] != NULL){
        path[count] = (char*)malloc(strlen(arguments[other_count])*sizeof(char));
        strcpy(path[count], arguments[other_count]);
        count++;
        other_count++;
        if(count > items){ //Resize if the end of the array is reached
            items = items*2;
            path = (char**)realloc(path, items);
        }
    }
    path[count] = NULL;
    return path;
}

char** make_array(char *cmd){
    char delimit [10] = " \t\r\n\a";
    int n = 50;
    char **arr = (char**)malloc(n*sizeof(char*));
    char *token;
    int count = 0;

    token = strtok(cmd, delimit);
    while(token != NULL){
        arr[count] = (char*)malloc(strlen(token)*sizeof(char));
        strcpy(arr[count], token);
        count++;

        if(count > n ){ //If count is bigger than array elements, resize
            n = n * 2;
            arr = realloc(arr, n*sizeof(char*));
        }
        token = strtok(NULL, delimit);
    }
    arr[count] = NULL;
    return arr;
}

int execute_commands(char** path, char** arguments){
    pid_t wait_pid, pid;
    int ind;
    char* exe; //The char* returned from has_access, which is the path where the command is concatenated with the command itself
    if(arguments[0] == NULL){
        return 1;
    }
    if( (exe = has_access(path, arguments[0])) != NULL){
        pid = fork();
        if(pid == 0){
            execv(exe, arguments);
        }
        else if(pid < 0){
            error();
        }
        else{
            do{
                wait_pid = waitpid(pid, &ind, WNOHANG|WUNTRACED);
            }while( !WIFEXITED(ind) && !WIFSIGNALED(ind));
        }
        return 1;
    }
    else{
        error();
        return 1;
    }
}

void change_directory(char *cmd){
    char *firstToken, *secondToken, *newline;
    char delimit [10] = " \t\r\n\a";

    firstToken = strtok_r(cmd, delimit, &cmd);
    secondToken = strtok_r(cmd, delimit, &cmd);
    if( secondToken == NULL){
        error();
        return;
    }
    if( strtok_r(cmd, delimit, &cmd) != NULL){
        error();
        return;
    }
    if( (chdir(secondToken)) != 0 ){
        error();
        return;
    }
    return;
}