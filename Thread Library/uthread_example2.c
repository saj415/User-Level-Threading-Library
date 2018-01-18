#include <stdio.h>


void funcB(int arg)
{
int i;
     printf("Inside Thread Function B\n");
	 for(i=0;i<5;i++)
	 {
	    printf("Thread B in loop\n");
	 }
printf("Terminating Thread B\n");
}

void funcC(int arg)
{
int i;
     printf("Inside Thread Function C\n");
	 for(i=0;i<5;i++)
	 {
	    printf("Thread C in loop\n");
	 }
printf("Terminating Thread C\n");
}

void funcD(int arg)
{
long i=0;
     printf("Inside Thread Function D\n");
	 for(i=0;i<5;i++)
	 {
	    printf("Thread D in loop\n");
	
	 }
printf("Terminating Thread D\n");
}

void funcE(int arg)
{
int i;
     printf("Inside Thread Function E\n");
	 for(i=0;i<5;i++)
	 {
	    printf("Thread E in loop\n");
	 }
printf("Terminating Thread E\n");
}



void funcA(int arg)
{
int tid;

tid = t_fork(funcB,NULL,"B",20);
tid = t_fork(funcC,NULL,"C",20);
tid = t_fork(funcD,NULL,"D",20);
tid = t_fork(funcE,NULL,"E",20);
printf("Thread A terminating\n");
}




int main()
{
int tid;
tid = t_start(funcA,NULL,"A", 30);

}
