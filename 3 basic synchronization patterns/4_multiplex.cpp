/*
Puzzle: Add semaphores to the following example to enforce mutual exclusion to the shared variable count.
 Thread A: count = count + 1
 Thread B: count = count + 1
 Generalize the solution so that it allows multiple threads to run in the critical section at the same time, but it enforces an upper limit on the number of concurrent threads. In other words, no more than n threads can run in the critical section at the same time.
*/

#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t countingSemaphore;

void* fun(void* arg){
    sem_wait(&countingSemaphore);
    int* count = (int*) arg;
    int temp = *count;
    *count = temp+1;
    sem_post(&countingSemaphore);
    return NULL;
}

int main(){
    int total,upperlimit;
    cout<<"enter total threads \n";
    cin>>total;
    cout<<"enter an upper limit on the number of concurrent threads \n";
    cin>>upperlimit; 

    vector<pthread_t>vec(total);

    if(sem_init(&countingSemaphore,0,upperlimit)!=0){
        cout<<"semaphore init failed \n";
        return 1;
    }

    int count=0;
    
    vector<int>n(total);
    for(int i=0;i<total;i++){
        n[i]=pthread_create(&vec[i],NULL,fun,(void*)&count);
        if(n[i]!=0) cout<<"failed creating thread "<<i+1<<"\n";
    }

    for(int i=0;i<total;i++){
        pthread_join(vec[i],NULL);
    }

    cout<<"Result: "<<count<<"\n";
    sem_destroy(&countingSemaphore);


    return 0;
}