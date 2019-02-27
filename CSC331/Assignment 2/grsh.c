#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    
    if(argc < 2){
        char *cmd = NULL;
        size_t len = 0;
        ssize_t nread;
        printf("grsh> ");
        while( (nread = getline(&cmd, &len, stdin)) != -1){
            if (cmd == "exit"){
                exit(0);
            }
        }
    }

}