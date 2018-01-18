#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "threads.h"


int num_threads = 0;
typedef enum id
{
    open = 1,
    pqr,
    xyz 
    
}id;

void Depart(any_ptr val);

int num_threads_pqr = 0,num_threads_xyz = 0;
id cur_id = open;
Lock my_lock; // This must be created in some main or other function
Condition cond; // This must be created in some main or other function
char idName[5];
int inFlight=0, toggleDir=0;
int firstTime = 0;

char* getID(id d)
{
        
    if(d==1)
        strcpy(idName,"open");
    else if(d==2)
        strcpy(idName,"pqr");
    else if(d==3)
        strcpy(idName,"xyz");

     return idName;        
}


void Arrive (any_ptr val)
{
      
    id my_id = (id)val;
	  lock_acquire(my_lock);

    if(firstTime == 0)
     {    firstTime++;
     cur_id = my_id; }

   if(my_id == pqr)
        num_threads = ++num_threads_pqr; 
   else if(my_id == xyz)
        num_threads = ++num_threads_xyz; 

 
    while(num_threads%2==0 || cur_id!=my_id || inFlight >= 3 || toggleDir==1) 
    {   
        t_sig(cond,NULL,my_lock);
        t_wait(cond,my_lock);

       if(my_id == pqr)
          num_threads = num_threads_pqr;  
       else if(my_id == xyz)
          num_threads = num_threads_xyz;  

       if( cur_id==my_id && toggleDir!=1)
                  break;
                  
       if(num_threads_pqr == 0 || num_threads_xyz == 0)
       {
              if(cur_id == pqr) cur_id = xyz;
              else if (cur_id == xyz) cur_id = pqr;

              break;
       }
    }
      cur_id = my_id;
      inFlight++;
      if(inFlight==3 )
          toggleDir=1;      
      printf("\n%s",getThreadName());
      printf(" Thread Created with ID  %s ", getID(my_id));
      lock_release(my_lock);

      t_fork(Depart,(any_ptr)my_id,getThreadName(),10);
}

void Depart (any_ptr val)
{
   lock_acquire(my_lock);
   id my_id = (id)val;

   inFlight--;
        if(inFlight==0)
         {      
            if(cur_id==pqr)
              {  cur_id = xyz; toggleDir = 0;  }
            else if(cur_id==xyz)
              {  cur_id = pqr; toggleDir = 0; } 
         }

   t_sig(cond,NULL,my_lock);
        
   if(my_id == pqr)
        num_threads = --num_threads_pqr; 
   else if(my_id == xyz)
        num_threads = --num_threads_xyz; 

      
   printf("\n%s",getThreadName());
   printf(" Thread Terminated with ID %s ", getID(my_id));
   lock_release(my_lock);

}


void funcA(any_ptr arg)
{
 int tid;
 int i;
 char name[30];
 id id1;

 firstTime = 0;
  
 for(i=0;i<3; i++)
     {
     sprintf(name,"Thread %d",i);
     id1 = 2;
     printf("\nThread %d",i);
     printf(" Thread Creating with ID %s",getID(id1));
     tid = t_fork(Arrive,(any_ptr)id1,name,10);
     }

 for(i=3;i<6; i++)
     {
     sprintf(name,"Thread %d",i);
     id1 = 3;
     printf("\nThread %d",i);
     printf(" Thread Creating with ID %s",getID(id1));     
     tid = t_fork(Arrive,(any_ptr)id1,name,10);
     }
     
 for(i=6;i<15; i++)
 {
     sprintf(name,"Thread %d",i);
     id1 = 2;
     printf("\nThread %d",i);
     printf(" Thread Creating with ID %s",getID(id1));
     tid = t_fork(Arrive,(any_ptr)id1,name,10);
 }

 for(i=15;i<18; i++)
     {
     sprintf(name,"Thread %d",i);
     id1 = 3;
     printf("\nThread %d",i);
     printf(" Thread Creating with ID %s",getID(id1));
     tid = t_fork(Arrive,(any_ptr)id1,name,10);
     }
 

}


int main()
{
    my_lock = lock_create();
    cond = cond_create(my_lock);

    t_start(funcA,NULL,"A",10);// first thread

}
