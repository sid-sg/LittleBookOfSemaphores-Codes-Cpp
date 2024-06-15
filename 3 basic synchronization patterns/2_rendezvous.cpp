/*
we want to guarantee that a1 happens before b2 and b1 happens before a2. In
 writing your solution. Your solution should not enforce too many constraints. For example, we
 don’t care about the order of a1 and b1.
 The idea is that two threads rendezvous at a point of execution, and neither is allowed to
 proceed until both have arrived.
*/

#include <iostream>
#include <pthread.h>
#include <semaphore.h>


using namespace std;

sem_t aArrived,bArrived;

void* fun1(void* arg){
    cout<<"a1 \n";
    sem_post(&bArrived);
    sem_wait(&aArrived);
    cout<<"a2 \n";
    return NULL;
}

void* fun2(void* arg){
    cout<<"b1 \n";
    sem_post(&aArrived);
    sem_wait(&bArrived);
    cout<<"b2 \n";
    return NULL;
}

int main(){
    pthread_t t1,t2;

    sem_init(&aArrived,0,0);
    sem_init(&bArrived,0,0);

    int n1 = pthread_create(&t1,NULL,fun1,NULL);
    int n2 = pthread_create(&t2,NULL,fun2,NULL);

    if(n1!=0) cout<<"failed created thread 1 \n";
    if(n2!=0) cout<<"failed created thread 2 \n";

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);


    return 0;
}