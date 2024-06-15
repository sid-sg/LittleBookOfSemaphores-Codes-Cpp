/*
Serialization using signaling
using counting semaphores in this case 
ensures fun1 always runs before fun2
*/

#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t countingSemaphore;

void* fun1(void* arg){
    cout<<"a1 \n";
    sem_post(&countingSemaphore);;
    return NULL;
}

void* fun2(void* arg){
    sem_wait(&countingSemaphore);
    cout<<"b1 \n";
    return NULL;
}

int main(){
    pthread_t t1,t2;

    sem_init(&countingSemaphore,0,0);

    int n1 = pthread_create(&t1,NULL,fun1,NULL);
    int n2 = pthread_create(&t2,NULL,fun2,NULL);

    if(n1!=0) cout<<"failed created thread 1 \n";
    if(n2!=0) cout<<"failed created thread 2 \n";

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);


    return 0;
}