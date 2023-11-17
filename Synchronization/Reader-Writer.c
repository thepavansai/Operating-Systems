#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<semaphore.h>
sem_t mutex,rw_mutex;
int rc=0;
int tkt=0;
void book(){
  tkt++;
}
void cancel(){
  tkt--;
}
void *reader(){
  while(1){
  sem_wait(&mutex);
    rc++;
    if(rc == 1){
      sem_wait(&rw_mutex);
    }
    sem_post(&mutex);
    printf("\nTicket Value : %d \n",tkt);
    sem_wait(&mutex);
    rc--;
    if(rc==0){
      sem_post(&rw_mutex);
    }
    sem_post(&mutex);
    sleep(3);
  } 
}
void *writer(){
  char ip;
  while(1){
    sleep(2);
    sem_wait(&rw_mutex);
    printf("\nEnter b to  Book & c to Cancel : ");
    scanf(" %c",&ip);
    if(ip=='b'){
      book();
    }
    else if(ip=='c') {
      cancel();
    }
    else{
      printf("\nInvalid input \n");
    }
    sem_post(&rw_mutex);
  }
}
int main(void){
  pthread_t rid;
  pthread_t wid;
  sem_init(&mutex,0,1);
  sem_init(&rw_mutex,0,1);
  pthread_create(&rid,NULL,reader,0);
  pthread_create(&wid,NULL,writer,0);
  pthread_join(rid,NULL);
  pthread_join(wid,NULL);
  return 0;
}
