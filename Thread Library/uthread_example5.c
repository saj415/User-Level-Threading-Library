#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "threads.h"


int num_threads = 0;
typedef enum id
{
    open = 1,
    
}id;

void Depart(any_ptr val);


id cur_id = open;
Lock my_lock; // This must be created in some main or other function
Condition cond; // This must be created in some main or other function
char idName[10];

char* getID(id d)
{

    if(d==1)
        strcpy(idName,"open");
    else if(d==2)
        strcpy(idName,"121A");
    else if(d==3)
        strcpy(idName,"122B");
    else if(d==4)
        strcpy(idName,"123C");
    else if(d==5)
        strcpy(idName,"124D");
    else if(d==6)
        strcpy(idName,"125E");
    else if(d==7)
        strcpy(idName,"126F");
    else if(d==8)
        strcpy(idName,"127G");
    else if(d==9)
        strcpy(idName,"128H");
    else if(d==10)
        strcpy(idName,"129I");

     return idName;
}


void Arrive (any_ptr val)
{
      
    id my_id = (id)val;
	  lock_acquire(my_lock);
      while (cur_id != my_id && cur_id != open)
	  {   
         t_wait(cond,my_lock);
	  }
      num_threads++;
      cur_id = my_id;
      printf("\n%s",getThreadName());
      printf(" Thread Created with ID %s", getID(my_id));
      lock_release(my_lock);
      t_fork(Depart,(any_ptr)my_id,getThreadName(),10);
}


void Depart (any_ptr val)
{
   id my_id = (id)val;
   lock_acquire(my_lock);
   num_threads--;
   if (num_threads == 0)
   {
        cur_id = open;
        int i;
        for(i=0;i<30;i++)   // perform a broadcast waking all blocked cars / threads.
          t_sig(cond,NULL,my_lock);
	  }
   printf("\n%s",getThreadName());
   printf(" Terminating Thread with ID  %s",getID(my_id));   
   lock_release(my_lock);

}


void funcA(any_ptr arg)
{
 int tid;
 int i;
 char name[30];
 id id1;
 
 for(i=0;i<5; i++)
 {
     sprintf(name,"Thread %d",i);
     id1 = 2;
     printf("\nThread %d",i);
     printf(" Creating Thread with ID %s",getID(id1));     
     tid = t_fork(Arrive,(any_ptr)id1,name,10);
 }
     
 for(i=5;i<10; i++)
 {
     sprintf(name,"Thread %d",i);
     id1 = 3;
     printf("\nThread %d",i);
     printf(" Creating Thread with ID %s",getID(id1));
     tid = t_fork(Arrive,(any_ptr)id1,name,10);
 }
     
/*
 for(i=0;i<5; i++)
     {
     sprintf(name,"Thread %d",i);
     id1 = 2+rand()%2;
     tid = t_fork(Arrive,(any_ptr)id1,name,10);
     }
*/

}


int main()
{
    
    my_lock = lock_create();
    cond = cond_create(my_lock);

    t_start(funcA,NULL,"A",10);// first thread

}
