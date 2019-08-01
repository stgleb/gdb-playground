#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


#define MAX_THREADS 100

pthread_t id[MAX_THREADS];
pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;

void* worker(int tn) {
    printf("hello from thread %d\n", tn);
}

int main(int argc,char **argv){
    void *p;
    int n;
    n = atoi(argv[1]);

    for(int i = 0;i < n;i++) {
        pthread_create(&id[i], NULL,(void*)worker,(void*)i);
    }

    for(int i = 0;i < n; i++) {
        pthread_join(id[i], &p);
        printf("%d done\n", i);
    }
}