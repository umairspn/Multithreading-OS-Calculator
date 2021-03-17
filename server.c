#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h> 
#include<sys/wait.h>
#include <sys/shm.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <fcntl.h>
#define SIZE 100 
#define BUFFSIZE 100 

int main()
 {  
  int num;
  pid_t child,child2;    
  printf("%d    %d\n",getpid(),getppid()); 
  printf("\n ----PARENT----  \n");
  

  int fd;
  int a=152;
  char tt='5';
  int fd1;
  char d[100];
  char buf[BUFFSIZE];
  char buf1[BUFFSIZE];
  //FILE FILE FILE
	fd=open("f1.txt",O_CREAT | O_WRONLY, 0600);
	if(fd<0)
	{
		printf("ERROR!!");
		printf("\n");
		exit(1);
	}

	write(fd,&a,sizeof(a));
	close(fd);
  	printf("\n");

  	
	fd=open("f1.txt", O_RDONLY);
	if(fd<0)
	{
		printf("First File Not Found!!");
		printf("\n");
		exit(1);
	}
	printf("\n");
	read(fd,&a,sizeof(a));
	printf(" \n%d \n",a);	
	close(fd);



	//FILE FILE FILE


  child = fork();

 if(child < 0)
  {   
   printf("Fork failed.\n");
   exit(-1);
  }

 else if(child == 0)
 {
  sleep(1);
  printf("\n\n ----CHILD 1----  \n");
  printf("\nENTER NUMBER 1:  ");

  scanf("%d", &num);
  //printf("\n %d \n",num);
  child2=fork();
if(child2 < 0)
  {   
   printf("Fork failed.\n");
   exit(-1);
  }

 else if(child2 == 0)
 {
  sleep(1);
  printf("\n\n ----CHILD 2----  \n");
  printf("\nENTER NUMBER 2:  ");
  int num2;
  scanf("%d", &num2);
  //printf("\n %d \n",num2);

  int shm_id; 
  key_t key;
  int *shm_ptr, *s;
  //creating
  key = 1234;
  shm_id = shmget(key, SIZE, IPC_CREAT | 0666);  
  if (shm_id < 0)
  {  	 
   perror("shmget error (server)\n");
   exit(1);
  } 
 shm_ptr = shmat(shm_id,NULL,0); 
 if (*shm_ptr ==  -1)
 {   
   perror("shmat error (server)\n");   
   exit(1); 
 }

//use memory
printf("\n---WAITING FOR OTHER PROCESS---\n");

   s = shm_ptr+1; 
  *s = num;  

   s++;
  *s=num2;

  while (*shm_ptr != 155)  	//waiting for other process 	
     sleep(1); 			
	
printf("\nThe result from client came back = %d \n\n",*s); 
shmctl(shm_id, IPC_RMID, NULL);
shmdt(shm_ptr);

//end
 }

else 
{   
wait(NULL);
}

 }

else 
{   
wait(NULL);
}
  return 0; 
} 
