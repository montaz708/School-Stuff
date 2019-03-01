#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    
    if(argc < 2){
        interactive_mode();
    }
    batch_mode();
    return 0;
}

bool has_access(char *cmd){
    char PATH[][10] = {"/bin","/usr/bin"};
    char *temp;
    for(int i = 0; i < sizeof(PATH)/sizeof(PATH[0]); i++){
        strcpy(temp, PATH[i]);
        strcat(temp, cmd);
        if( (access(temp, X_OK)) == 0 ){
            return true;
        }
    }
    return false;
}

void interactive_mode(){
    char *cmd = NULL;
    char *token;
    size_t len = 0;
    size_t count;
    ssize_t nread;
    
    while(1){
        printf("grsh> ");
        getline(&cmd, &len, stdin);
        if(strstr(cmd, "exit")) break;
        count = 0;
        while( (token = strtok_r(cmd, " ", &cmd))){
            if(count == 0){
                if( has_access(token)){
                //do the thing
                }
                else{
                    printf("Either %s doesn't exist or this program doesn't have permission to access to it.", token);
                    exit(1);
                }
            }
            token = strtok_r(NULL, cmd);
            count++;
        }
    }
    exit(0);
}

void batch_mode(){

}