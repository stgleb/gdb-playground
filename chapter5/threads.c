#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

#define MAX_N 100000000
#define MAX_THREADS 100

int nthreads;
int n;
int prime[MAX_N + 1];
int nextbase;
int work[MAX_THREADS];

pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;
pthread_t id[MAX_THREADS];

void crossout(int k){
    int i;

    for(i = k;i*k <= n;i++){
        prime[i*k] = 0;
    }
}

int my_sqrt(int n) {
    int i;
    for(i = 1;(i + 1)*(i + 1) <= n;i++);
    return i;
}

void* worker(int tn) {
    int lim;
    int base;

    lim = my_sqrt(n);

    do {
        work[tn]++;
        pthread_mutex_lock(&nextbaselock);
        base = nextbase += 2;
        pthread_mutex_unlock(&nextbaselock);

        if(base <= lim) {
            work[tn]++;

            if(prime[base])
                crossout(base);
        } else {
            return;
        }
    }while(1);

    return;
}

int main(int argc,char **argv){
    int nprimes;
    int totwork;
    int i;
    void *p;

    n = atoi(argv[1]);
    nthreads = atoi(argv[2]);


    for(i = 2;i <= n; i++)
        prime[i] = 1;

    crossout(2);
    nextbase = 1;


    for(i = 0;i < n;i++) {
        pthread_create(&id[i], NULL,(void*)worker,(void*)i);
    }

    totwork = 0;
    for(i = 0;i < nthreads; i++) {
        pthread_join(id[i], &p);
        printf("%d values if base done\n", work[i]);
        totwork += work[i];
    }
    printf("%d total values of base done\n", totwork);

    nprimes = 0;
    for(i = 2;i <= n; i++) {
        if(prime[i]) nprimes++;
    }
    printf("the number of primes found was %d\n", nprimes);
}