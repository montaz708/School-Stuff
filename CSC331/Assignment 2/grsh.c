#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

void error();
char* has_access(char** path, char *cmd);
char** update_path(char *cmd);
char** make_array(char *cmd);
int execute_commands(char** path, char** arguments);
void change_directory(char *cmd);
int parallel_commands(char** path, char* cmd);
int execute_to_file(char **path, char *cmd);
void interactive_mode();
void batch_mode();


int main(int argc, char *argv[]){
    if(argc > 1){
        int count = 1;
        while(count < argc){
            batch_mode(argv[count]);
            count++;
        }
    }
    else{
        interactive_mode();
    }
    return 0;
}

void interactive_mode(){
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
        if(strstr(cmd, "exit")){
            exit(0);
        }
        if(strstr(cmd, "path")){
            path = update_path(cmd);
            continue;
        }
        if(strstr(cmd, "cd")){
            change_directory(cmd);
            continue;
        }
        if(strstr(cmd, "&")){
            indicator = parallel_commands(path, cmd);
            continue;
        }
        if(strstr(cmd, ">")){
            execute_to_file(path, cmd);
            continue;
        }
        arguments = make_array(cmd);
        indicator = execute_commands(path, arguments);
    }while(indicator);
}

void batch_mode(char* file){
    FILE *fp;

    fp = fopen(file, "r");

    char *cmd = NULL;
    ssize_t len = 0, nread;
    char **arguments;
    int buffer = 10;
    int indicator;
    char **path = (char**)malloc(buffer*sizeof(char*));
    path[0] = (char*)malloc(strlen("/bin/")*sizeof(char));
    strcpy(path[0], "/bin/");
    path[1] = NULL;
    do{
        nread = getline(&cmd, &len, fp); 
        if(strstr(cmd, "exit")){
            exit(0);
        }
        if(nread == -1){
            break;
        }
        if(strstr(cmd, "path")){
            path = update_path(cmd);
            continue;
        }
        if(strstr(cmd, "cd")){
            change_directory(cmd);
            continue;
        }
        if(strstr(cmd, "&")){
            indicator = parallel_commands(path, cmd);
            continue;
        }
        if(strstr(cmd, ">")){
            execute_to_file(path, cmd);
            continue;
        }
        arguments = make_array(cmd);
        indicator = execute_commands(path, arguments);
    }while(indicator);
    fclose(fp);
    return;
}

void error(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
}

char* has_access(char **path, char *cmd){
    char *temp = (char*)malloc(256*sizeof(char));
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
                wait_pid = waitpid(-1, &ind, WUNTRACED);
            }while( !WIFEXITED(ind) && !WIFSIGNALED(ind));
        }
        return 1;
    }
    else{
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

int parallel_commands(char** path, char *cmd){
    char *token, *exe;
    char** arguments;
    int ind;
    pid_t wait_pid, pid;

    token = strtok(cmd, "&");
    while(token != NULL){
        arguments = make_array(token);
        if( (exe = has_access(path, arguments[0])) != NULL){
            pid = fork();
            if(pid == 0){
                execv(exe, arguments);
            }
            else if(pid < 0){ //Failed fork, return and stop processing
                error();
                return 1;
            }
        }
        else{
            return 1;
        }
        token = strtok(NULL, "&");
    }
    do{
        wait_pid = waitpid(-1, &ind, WUNTRACED);
    }while( !WIFEXITED(ind) && !WIFSIGNALED(ind));
    return 1;
}

int execute_to_file(char **path, char *cmd){
    char *file_path, *token, *exe;
    char **arguments;
    pid_t wait_pid, pid;
    int ind;
    token = strtok(cmd, " >\n");
    file_path = strtok(NULL, " >\n");
    int fp = open(file_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    arguments = make_array(token);
    if( (exe = has_access(path, arguments[0])) != NULL ){
        pid = fork();
        if(pid == 0){
            dup2(fp, 1);
            dup2(fp, 2);
            execv(exe, arguments);

        }
        else if(pid < 0){
            error();
            return 1;
        }
        else{
            do{
                wait_pid = waitpid(-1, &ind, WUNTRACED);
            }while( !WIFEXITED(ind) && !WIFSIGNALED(ind));
        }
        return 1;
    }
}