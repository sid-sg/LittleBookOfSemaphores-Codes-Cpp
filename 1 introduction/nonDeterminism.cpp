#include <iostream>
#include <pthread.h>

using namespace std;

void* printMessage(void* arg){
  const char* msg = (char*) arg;
  cout<<msg<<endl;
  return nullptr;
}

int main(){
  pthread_t t1,t2;

  const char* msg1 = "yes";
  const char* msg2 = "no";
  
  int n1 = pthread_create(&t1, NULL, printMessage, (void*)msg1);
  int n2 = pthread_create(&t2, NULL, printMessage, (void*)msg2);

  if(n1!=0) cout<<"Error creating t1";
  if(n2!=0) cout<<"Error creating t2";

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);

  

}

