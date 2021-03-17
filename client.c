#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <pthread.h> 
#include<semaphore.h>

#define SIZE 100
void *func(void*);
 int main() 
{ 
 //sem=mutex;

 int shm_id;
 key_t key; 
 int *shm_ptr, *s; 
 //creating  
 key = 1234; 
 shm_id = shmget(key, SIZE, 0666);
 if (shm_id < 0) 
{   
perror("shmget error (client)\n");  
 exit(1); 
 } 
 //attaching 
 
shm_ptr = shmat(shm_id,NULL,0); 
 if (*shm_ptr == -1) 
{ 
  perror("shmat error (client)\n"); 
  exit(1); 
}   

//using memory
int n1, n2;
s=shm_ptr+1;
printf("number 1: %d\n",*s);
n1=*s;
s++;
printf("number 2: %d\n",*s);
n2=*s;

//thread start

sleep(1);
printf("\n---TABLE CREATION---\n");
sleep(1);
int nn;
printf("Enter 1 to make table for OPR 1 || 2 for OPR 2   ");
scanf("%d",&nn);


pthread_t t1, t2;
int ret1, ret2;
if(nn==1)
{
unsigned long ms2=n1;
//sem_wait(1,0,0);
ret1= pthread_create(&t1,NULL,func,(void*)ms2);
pthread_join(t1,NULL);
//sem_post(1,0,0);
printf("---MAIN AFTER THREAD CREATION---\n");
}   
else if(nn==2)
{
unsigned long ms2=n2;
//sem_wait(1,0,0);
ret1= pthread_create(&t1,NULL,func,(void*)ms2);
pthread_join(t1,NULL);
//sem_post(1,0,0);
printf("---MAIN AFTER THREAD CREATION---\n");
}
else
{
printf("\n---WRONG INPUT---\n");
}


//thread end

sleep(2);
printf("\n---ENTER OPERATOR:  1(+) 2(-) 3(*) 4(/)   ");
//printf("HERE 1");
//char opr;
int opr;
scanf("%d", &opr);

if(opr==1)
{
 *s=n1+n2;
}
else if (opr==2)
{
 *s=n1-n2;
}
else if (opr==3)
{
 *s=n1*n2;
}
else if (opr==4)
{ 
*s=n1/n2;
}
//else
//printf("\n---INVALID OPERATOR\n");

printf("\n---YOU CAN VIEW THE RESULT ON SERVER NOW---\n");
*shm_ptr = 155;    
shmdt(shm_ptr);

//end

return 0; 
}



void *func(void *str)
{
unsigned long id = (unsigned long)str; 

printf("%lu \n",id);

for(int j=1; j<=10; j++)
{
printf("%lu  *  %d   =   %lu \n",id,j,id*j);
sleep(1);
}

//for(int i = 0; i < id; i++)
//{
//printf(" HELLO\n");
//sleep(1);
//}
pthread_exit(0);
}
