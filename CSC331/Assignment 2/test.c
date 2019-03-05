#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

char* has_access(char *cmd){
    static char PATH[][10] = {"/bin/"};
    char *temp;
    for(int i = 0; i < sizeof(PATH)/sizeof(PATH[0]); i++){
        strcpy(temp, PATH[i]);
        strcat(temp, cmd);
        if( (access(temp, X_OK)) == 0 ){
            return PATH[i];
        }
    }
    return NULL;
}


void interactive_mode(){
    char *cmd = NULL;
    char *token, *path;
    size_t len = 0;
    size_t count;
    
    while(1){
        printf("grsh> ");
        getline(&cmd, &len, stdin);
        count = 0;
        while( (token = strtok_r(cmd, " ", &cmd))){
			token = strtok_r(NULL, " ", &cmd);
            if(count == 0){
                if( (strstr(token, "exit") != NULL)) exit(0);
                if( (path = has_access(cmd)) != NULL ){
                    execv(path, &cmd);
                }
                else{
                    char error_message[30] = "An error has occurred\n";
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    break;
                }
            }
            count++;
        }
    }
    exit(0);
}


int main(int argc, char* argv[]){
    
    if(argc < 2){
        interactive_mode();
    }
    return 0;
}