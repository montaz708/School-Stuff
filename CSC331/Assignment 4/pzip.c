#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <inttypes.h>

char* contents;
int mod_result;
int div_result;
static int offset = 0;

size_t getFilesize(const char* filename){
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

void rle(char *buff){
	uint8_t character, new_character;
	uint8_t count = 1;
	int pos = 0;
	character = buff[pos];
	do{
		pos++;
		new_character = buff[pos];
		if(new_character == 0){
			break;
		}
		if(character == new_character){
			count++;
		}
		else{
			fwrite(&count, 4, 1, stdout);
			fwrite(&character, 1, 1, stdout);
			character = new_character;
			count = 1;
		}
	}while(1);
	return;
}

void *split(){
	char subbuff[div_result + mod_result + 1];
	memcpy(subbuff, &contents[offset], div_result);
	subbuff[div_result + mod_result] = '\0';
	rle(subbuff);
	offset = offset + div_result;
	void * k = 0;
	return k;
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

	mod_result = total_size % num_threads;
	div_result = total_size / num_threads;
	pthread_t *threads = (pthread_t *)malloc((num_threads + 1)*sizeof(pthread_t));
	for(int a = 0; a < num_threads + 1; a++){
		pthread_create(&threads[a], NULL, split, NULL);
		a++;
	}
	for(int b = 0; b < num_threads; b++){
		pthread_join(threads[b], NULL);
	}

    free(contents);
    free(buffer);
    return(0);
}