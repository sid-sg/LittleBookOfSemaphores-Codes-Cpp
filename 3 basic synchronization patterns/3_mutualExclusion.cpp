/*
Puzzle: Add semaphores to the following example to enforce mutual exclusion to the shared variable count.
 Thread A: count = count + 1
 Thread B: count = count + 1
*/

#include <iostream>
#include <pthread.h>

using namespace std;

pthread_mutex_t lock;

void* fun(void* arg){
    pthread_mutex_lock(&lock);
    int* count = (int*) arg;
    int temp = *count;
    *count = temp+1;
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(){
    pthread_t t1,t2;

    if(pthread_mutex_init(&lock,NULL)!=0) cout<<"mutex init failed \n";

    int count=0;

    int n1 = pthread_create(&t1,NULL,fun,(void*)&count);
    int n2 = pthread_create(&t2,NULL,fun,(void*)&count);

    if(n1!=0) cout<<"failed created thread 1 \n";
    if(n2!=0) cout<<"failed created thread 2 \n";

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    cout<<count<<"\n";


    return 0;
}