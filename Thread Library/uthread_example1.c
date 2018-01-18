#include <stdio.h>

void funcC(int arg)
{
     printf("New Thread C Created\n ");
}


void funcB(int arg)
{
int tid;
printf("New Thread B Created\n ");
tid = t_fork(funcC,NULL,"C",20);
printf("New Thread D Created\n ");
t_join(tid);
printf("New Thread E Created\n ");

}

void funcA(int arg)
{
int tid;
printf("Main Thread A Created\n ");
tid = t_fork(funcB,NULL,"B", 10); // The new thread is being created
                             

printf("New Thread F Created\n ");
t_join(tid);
printf("New Thread G Created\n");
}


int main()
{

t_start(funcA,NULL,"A",0);

}
