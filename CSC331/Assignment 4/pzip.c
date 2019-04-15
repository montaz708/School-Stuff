#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
int main(int argc, char *argv[]){

	FILE *fp;
	uint8_t character, new_character;
	uint8_t count = 1;
	if(argc < 2){
		printf("pzip: file1 [file2 ...] \n");
		return(1);
	}
	for(int a = 1; a < argc; a++){
		
	}
	return(0);
}

void rle(char *file_path){
	FILE *fp;
	int count;
	uint8_t character, new_character;

	fp = fopen(file_path, "r");
	if (fp != NULL){
		character = fgetc(fp);
		count = 0;
		do{
			new_character = fgetc(fp);
			if( feof(fp) ){
				break;
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
		printf("Count not open file for compression");
		return;
	}
	fclose(fp);
	return;
}
