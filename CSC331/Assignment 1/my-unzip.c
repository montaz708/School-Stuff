#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    FILE *fp;
    uint8_t character;
    uint8_t count;

    if(argc < 2){
        printf("my-unzip: file1 [file2 ...] \n");
        return(1);
    }
    for(int a = 1; a < argc; a++){
        fp = fopen(argv[a], "r");
        if(fp != NULL){
            do{
                count = fgetc(fp);
                character = fgetc(fp);
                if( feof(fp)){
                    break;
                }
                for(int b = 0; b <= count; b++){
                    fputc(character, stdout);
                }

            }while(1);
        }
        else{
            printf("Could not read %s for file decompression!", argv[a]);
        }
        fclose(fp);
    }
    return(0);
}

