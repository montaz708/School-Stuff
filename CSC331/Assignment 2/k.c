#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char** update_path(char *cmd);
char** make_array(char *cmd);
void error();

int main(int argc, char *argv[]){
    char *cmd = NULL;
    ssize_t len = 0;
    char **arguments, **new_path;
    int buffer = 10;
    int indicator = 1, size, count;
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
            memset(path, 0, buffer);
            path = update_path(cmd);
        }
        count = 0;
        while(path[count] != NULL){
            printf("%s ", path[count]);
            count++;
        }
        printf("\n");
        
    }while(indicator);
    free(cmd);
    free(arguments);
    return 0;
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

        if(count > n ){
            n = n * 2;
            arr = realloc(arr, n*sizeof(char*));
        }
        token = strtok(NULL, delimit);
    }
    arr[count] = NULL;
    return arr;
}

void error(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
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