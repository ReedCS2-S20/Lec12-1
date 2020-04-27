#include <pthread.h>
#include <iostream>

typedef void *tmain(void *);

long increment(long *v) {
  long i;
  for (i=0; i<100000; i++) { 
    long tmp = (*v);
    (*v) = tmp + 1;
  }   
  return i;
}

int main(int argc, char **argv) {
  pthread_t id1, id2;
  long r1, r2;
  long count = 0;
  pthread_create(&id1,NULL,(tmain *)increment,(void *)&count);
  pthread_create(&id2,NULL,(tmain *)increment,(void *)&count);
  pthread_join(id1,(void **)&r1);
  pthread_join(id2,(void **)&r2);
  std::cout << "Thread 1 incremented " << r1 << " times." << std::endl;
  std::cout << "Thread 2 incremented " << r2 << " times." << std::endl;
  std::cout << "The final count is " << count << "." << std::endl;
  pthread_exit(NULL);
}

