#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

int main(){

	char PATH[][10] = {"/bin","/usr/bin"};
	char *cmd = NULL;
	size_t len = 0;

	while(1){
		printf("grsh>");
		getline(&cmd, &len, stdin);
		if(strstr(cmd, "exit")) break;
		printf("%s", cmd);
	}
	return 0;
}
