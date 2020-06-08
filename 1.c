#include <stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc(),int argv[])
{
	pit_t pid1;
	pid_t pid2;
	pid1=fork();
	if(pid1==0)
	{
		signal(SIGUSR1,fun);
		printf("进程1\n");
		pid2=fork();
		if(pid2==0)
		{
			signal(SIGUSR1,fun);
			printf("进程2\n");
		}
	}
	if((pid1)>0)
	{
		kill(SIGUSR1,pid1);
		printf("父过程\n");
		wait(NULL);
	}
	if((pid2)>0)
	{
		kill(SIGUSR1,pid2);
		printf("父进程\n");
		wait(NULL);
	}
	return 0;
}
