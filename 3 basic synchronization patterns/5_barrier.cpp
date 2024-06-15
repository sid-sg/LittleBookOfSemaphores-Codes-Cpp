/*
Puzzle: Generalize the rendezvous solution. Every thread should run code i.e n threads
*/

#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t allArrived;
pthread_mutex_t CSlock;
pthread_mutex_t countLock;

int n;
int count=0;

void* fun(void* arg){
    int threadNo = *((int*)arg);
    
    pthread_mutex_lock(&countLock);
    cout<<"thread "<<threadNo<<" arrived\n";
    count++;
    pthread_mutex_unlock(&countLock);

    if(count==n) sem_post(&allArrived);

    sem_wait(&allArrived);
    sem_post(&allArrived);

    pthread_mutex_lock(&CSlock);
    cout<<"thread "<<threadNo<<" in CS\n";
    pthread_mutex_unlock(&CSlock);

    return NULL;
}

int main(){
    
    cout<<"Enter no of threads: \n";
    cin>>n;
    vector<pthread_t> threads(n);

    if(pthread_mutex_init(&CSlock, NULL)!=0) cout<<"CSlock mutex init has failed\n"; 
    if(pthread_mutex_init(&countLock, NULL)!=0) cout<<"CSlock mutex init has failed\n"; 

    sem_init(&allArrived,0,0);

    for(int i=0;i<n;i++){
        int* threadNo = new int(i);
        if(pthread_create(&threads[i],NULL,fun,(void*)threadNo)!=0){
            cout<<"failed created thread "<<i<<"\n";
        }
    }

    for(int i=0;i<n;i++){
        pthread_join(threads[i],NULL);
    }

    pthread_mutex_destroy(&countLock);
    pthread_mutex_destroy(&CSlock);
    sem_destroy(&allArrived);

    return 0;
}