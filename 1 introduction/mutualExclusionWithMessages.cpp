/*
Thread 1
    call Thread 2 and request for permission
    wait for permission
    eat lunch while Thread 2 monitoring
    call Thread 2 and say my lunch is over

Thread 2
    call Thread 1 and request for permission
    wait for permission
    eat lunch while Thread 1 monitoring
    call Thread 1 and say my lunch is over
*/
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t lock;

void* fun1(void* arg){
    pthread_mutex_lock(&lock);
    cout<<"thread 1 having lunch , thread 2 monitoring"<<endl;
    sleep(1);
    cout<<"thread 1 finished lunch , thread 2 monitoring"<<endl;
    pthread_mutex_unlock(&lock);
    
    return NULL;
}

void* fun2(void* arg){
    pthread_mutex_lock(&lock);
    cout<<"thread 2 having lunch , thread 1 monitoring"<<endl;
    sleep(1); 
    cout<<"thread 2 finished lunch , thread 1 monitoring"<<endl;
    pthread_mutex_unlock(&lock);
    return NULL;
}

using namespace std;

int main(){
    pthread_t t1,t2;

    if(pthread_mutex_init(&lock, NULL)!=0) cout<<"mutex init has failed"<<endl; 

    int n1 = pthread_create(&t1, NULL, fun1, NULL);
    int n2 = pthread_create(&t2, NULL, fun2, NULL);

    if(n1!=0) cout<<"Error creating t1";
    if(n2!=0) cout<<"Error creating t2";

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    return 0;
}
