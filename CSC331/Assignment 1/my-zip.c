#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

	FILE *fp;
	int i;
	int word_count;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int a;
	if(argc < 2){
		printf("my-zip: file1 [file2 ...] \n");
		return(1);
	}
	for(a = 1; a < argc; a++){
		fp = fopen(argv[a], "r");
		if(fp != NULL){
			while( (nread = getline(&line, &len, fp)) != -1){
				i = 0;
				while(i < strlen(line)){
					if(i > 0){
						if(line[i-1] == line[i]){
							word_count++;
						}
						else{
							printf("%d%c", ++word_count, line[i - 1]);
							word_count = 0;
						}
					}
					i++;
					printf("\n");
				}
			}
			fclose(fp);
			free(line);
		}
		else{
			printf("Could not open %s for compressing!", argv[a]);
			return(1);
		}
	}
	return(0);
}
