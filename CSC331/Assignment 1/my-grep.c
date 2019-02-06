#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

// #define MAXCHAR 1000
// int main(int argc, char* argv[]){
//     char str[MAXCHAR];
//     if(argc == 1)
//         printf("my-grep: searchterm [file ...]");
//         exit(1);
//     if(argc > 2){
//         int counter = 2;
//         FILE *fptr;
//         char* search;
//         do{
//             if((fptr = fopen(argv[counter], "r")) == NULL){
//                 printf("my-grep: cannot open file \n");
//                 exit(1);
//             }
//             while(fgets(str, MAXCHAR, fptr) != NULL){
//                 if(str == search){
//                     printf("%s",str);
//                 }
//             }
//             counter++;
//         }while(counter < argc);
//     }
// }



int main(int argc, char* argv[]){
    char *line = NULL;
    char *word = NULL;
    size_t len = 0;
    ssize_t nread;
    FILE *fptr;

    if(argc == 1){
        printf("my-grep: searchterm [file ...]");
        exit(1);
    }
    else if(argc == 2){
        //do stdin
    }
    else if(argc > 2){
        int counter = 2;
        word = (char *)malloc(sizeof(argv[1]));
        strcpy(*word, argv[1]);
        
        do{
            fptr = fopen(argv[counter], "r");
            while((nread = getline(&line, &len, fptr)) != -1){
                if(strstr(line, word) != NULL){
                    printf("%s", line);
                }
            }
            fclose(fptr);
            counter++;
        }while(counter < argc);
        free(line);
        return 0;
    }
}