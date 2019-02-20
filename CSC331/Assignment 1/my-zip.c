#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
int main(int argc, char *argv[]){

	FILE *fp;
	uint8_t character, new_character;
	uint8_t count = 1;
	if(argc < 2){
		printf("my-zip: file1 [file2 ...] \n");
		return(1);
	}
	for(int a = 1; a < argc; a++){
		fp = fopen(argv[a], "r");
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
					fputc(count, stdout);
					fputc(character, stdout);
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
	}
	return(0);
}
