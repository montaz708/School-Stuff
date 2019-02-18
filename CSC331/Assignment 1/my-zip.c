#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

	FILE *fp;
	int i;
	int word_count;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	fp = fopen(argv[1], "r");
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
		}
	}

}
