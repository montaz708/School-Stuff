#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
<<<<<<< HEAD
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntrl.h>
#include <sys/stat.h>
#include <assert.h>

void rle();
size_t getFilesize(const char* filename);
void *map(char* argv, int argc);

int main(int argc, char *argv[]){

	pthread_t *threads;
	int i;
	int file_count = 0;
	int file_offset;
	int num_threads = atoi(argv[1]);
	if(argc < 2){
		printf("pzip: num_threads file1 [file2 ...] \n");
		return(1);
	}
	map();
	threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
	for(i = 0; i < num_threads; i++){
		if(pthread_create(&threads[i], NULL, rle, ) != 0){
			perror("Can't create thread \n");
			free(threads);
			exit(-1);
		}
	}
	free(threads);
	return(0);
}


size_t getFilesize(const char* filename){
	struct stat st;
	stat(filename, &st);
	return st.st_size;
}

void *map(char *argv, int argc){
	int file_offset;
	size_t filesize;
	void *mappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, FD, 0);
	for(file_offset = 2; file_offset <= argc; file_offset++){
		filesize = getFilesize(argv[file_offset]);
		int fd = open(argv[file_offset], O_RDONLY, 0);
		assert(fd != -1);
	}
}

void rle(){
	int fd = open(file, "r");
		if(fp != NULL){
			character = fgetc(fp); 
			count = 0;
			do{
				new_character = fgetc(fp);
				if( feof(fp) ){ 
					break;
				}
				if(character == new_character){
					count++;
				}
				else{
					fwrite(&count, 4, 1, stdout);
					fwrite(&character, 1, 1, stdout);
					character = new_character;
					count = 0;
				}
			}while(1);
		}
		else{
			printf("Could not open %s for compressing!", argv[a]);
			return(1);
		}
		fclose(fp);
>>>>>>> 36b198a2cd7268c0f6c6cafd93cd6f20450cc43c
}
