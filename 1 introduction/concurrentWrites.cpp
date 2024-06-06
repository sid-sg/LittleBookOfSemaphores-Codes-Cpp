//sometimes it'll print 5 and sometimes 7, therefore non deterministic

#include <iostream>
#include <pthread.h>

using namespace std;

void* fun1(void* arg){
    int* x=(int *)arg;
    *x=5;
    cout<<"fun output: "<<*x<<endl;
    return NULL;
}
void* fun2(void* arg){
    int* x=(int *)arg;
    *x=7;
    return NULL;
}

using namespace std;

int main(){
    pthread_t t1,t2;
    int x;
    int n1 = pthread_create(&t1, NULL, fun1, (void *)&x);
    int n2 = pthread_create(&t2, NULL, fun2, (void *)&x);

    if(n1!=0) cout<<"Error creating t1";
    if(n2!=0) cout<<"Error creating t2";

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    cout<<"final x: "<<x<<endl;

    return 0;
}

/*
output 5, final value 7:  line 10<11<16
output 5, final value 5:  line 16<10<11
output 7, final value 7:  line 10<16<11
output 7, final value 5:  impossible
*/