#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 1000
int main(int argc, char* argv[]){
    char str[MAXCHAR];
    if(argc == 1)
        return 0;
    if(argc > 1){
        int counter = 1;
        FILE *fptr;
        do{
            if((fptr = fopen(argv[counter], "r")) == NULL){
                printf("my-cat: cannot open file \n");
                exit(1);
            }
            while (fgets(str, MAXCHAR, fptr) != NULL){
                printf("%s", str);
            }
            fclose(fptr);
            counter++;
        }while(counter < argc);
    }
    return 0;
}
