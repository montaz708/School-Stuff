#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char* contents;

size_t getFilesize(const char* filename){
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

void *split(char subbuff){
    printf("%s \n", subbuff);
    return;
}

int main(int argc, char** argv){
    int total_size = 0;
    int num_threads = atoi(argv[1]);
    char * buffer = (char *)malloc(2000*sizeof(char));
    FILE *fp;
    int a = 3;
    total_size = total_size + getFilesize(argv[2]);
    contents = (char *)malloc(total_size*sizeof(char));
    fp = fopen(argv[2], "r");
    if(!fp) perror("Nope \n"), exit(1);
    if(1 != fread(contents, getFilesize(argv[2]), 1, fp))
        fclose(fp), free(contents), fputs("Failed to read file \n", stderr), exit(1);
    fclose(fp);
    //argc-1 because the last argument in argv is (null)
    while(a <= argc-1){
        total_size = total_size + getFilesize(argv[a]);
        contents = (char *)realloc(contents, total_size);
        fp = fopen(argv[a], "r");
        if(1 != fread(buffer, getFilesize(argv[a]), 1, fp))
            fclose(fp), free(buffer), fputs("Failed to read file \n", stderr), exit(1);
        strcat(contents, buffer);
        memset(buffer, '\0', 2000*sizeof(char));
        fclose(fp);
        a++;
    }

    free(contents);
    free(buffer);
    return(0);
}