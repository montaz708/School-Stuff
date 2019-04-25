#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myThreadFun(void *vargp){
    sleep(1);
    printf('Printing \n');
    return NULL;
}

int main(){
    pthread_t* threads;
    threads = (pthread_t *)malloc(3*sizeof(pthread_t));
    int i = 0;

    while(i < 3){
        pthread_create(&threads[i], NULL, myThreadFun, NULL);
        i++;
    }
    pthread_join(threads, NULL);
}