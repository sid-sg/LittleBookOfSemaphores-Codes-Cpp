#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void* fun(void* arg){
    int* x=(int *)arg;
    int temp=*x;
    usleep(0); //with this line final output is 1, and without it output is 2: because usleep makes current thread context switch to other thread due to with both read 0 resulting in 1, else t1 execute then t2 resulting in 2
    *x=temp+1;
    return NULL;
}

using namespace std;

int main(){
    pthread_t t1,t2;
    int x=0;
    int n1 = pthread_create(&t1, NULL, fun, (void *)&x);
    int n2 = pthread_create(&t2, NULL, fun, (void *)&x);

    if(n1!=0) cout<<"Error creating t1";
    if(n2!=0) cout<<"Error creating t2";

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    cout<<"final x: "<<x<<endl;

    return 0;
}

/*
void* fun(void* arg){
    int* x=(int *)arg;
    int temp=*x;
    *x=temp+1;
    return NULL;
}
output: 2



void* fun(void* arg){
    int* x=(int *)arg;
    int temp=*x;
    usleep(1);
    *x=temp+1;
    return NULL;
}
output:1
*/