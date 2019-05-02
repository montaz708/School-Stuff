#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char *contents;
int mod_result;
int div_result;
static int offset = 0;

size_t getFilesize(const char* filename){
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

void *split(){
	sleep(1);
	char subbuff[div_result + mod_result + 1];
	memcpy(subbuff, &contents[offset], div_result);
	subbuff[div_result + mod_result] = '\0';
	printf("%s \t %d \n", subbuff, offset);
	offset = offset + div_result;
}

int main(int argc, char* argv[]){
	int num_threads = atoi(argv[1]);
	FILE *fp = fopen(argv[2], "r");
	int total_size = getFilesize(argv[2]);
	contents = (char*)malloc(total_size*sizeof(char));
	fread(contents, total_size, 1, fp);

	mod_result = total_size % num_threads;
	div_result = total_size / num_threads;
	printf("total: %d \t mod: %d \t div: %d \t num: %d \n", total_size, mod_result, div_result, num_threads);
	pthread_t *threads = (pthread_t *)malloc(num_threads*sizeof(pthread_t));
	for(int a = 0; a < num_threads + 1; a++){
		pthread_create(&threads[a], NULL, split, NULL);
		printf("Loop: %d \n", a);
		a++;
	}
	for(int b = 0; b < num_threads; b++){
		pthread_join(threads[b], NULL);
	}

	return(0);
}