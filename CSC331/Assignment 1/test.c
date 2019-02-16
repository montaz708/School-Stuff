#include <stdio.h>

int main(){
    char *ch=malloc (50);
    scanf("%[^\n]%*c", ch);
    printf("%s \n", ch);
}