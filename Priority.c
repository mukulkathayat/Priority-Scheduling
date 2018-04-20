#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int n;
struct Process
{
	char process[6];
	int arr;
	double estRun_t;
	double priority;
	int wait_t;
	double turnAround_t;
};
struct Process *o1;
int i,min_arrtime=65537;
int cur_time=0,j=0,p=0;
char cur_process[5];
double avgTurnAround_t=0,avgWait_t=0;
double runTime=100000000.0;
int findMinTime()
{
	min_arrtime=65537;
	
	for(i=0;i<n;i++)
	{
		if(o1[i].priority==-1)
			continue;
		if(min_arrtime==o1[i].arr)
		{
			if(o1[i].estRun_t<runTime)
			{
				strcpy(cur_process,o1[i].process);
				runTime=o1[i].estRun_t;
				min_arrtime=o1[i].arr;		
			}
		}
		else if(min_arrtime>o1[i].arr)
		{
			strcpy(cur_process,o1[i].process);
			runTime=o1[i].estRun_t;
			min_arrtime=o1[i].arr;
		}
	
	}
	cur_time=min_arrtime;
	return 0;
}
void findMaxPriority()									
{
	double max_priority=-10000000.0;
	for(i=0;i<n;i++)
	{
		if(o1[i].priority==-1)
		{
			continue;
		}
		else
		{
			if(max_priority<o1[i].priority)
			{
				max_priority=o1[i].priority;
				strcpy(cur_process,o1[i].process);
			}
		}
	}
	return;
}
int main()
{

	printf("Enter the number of processes: ");
	scanf("%d",&n);
	printf("\n\t\tEnter the details of  processes\n\n");
	o1=(struct Process*)malloc(sizeof( struct Process)*n);
	for(i=0;i<n;i++)
	{
		printf("Enter the %d Process Name: ",i+1);
		scanf("%s",o1[i].process);
		printf("Enter its Arrival Time: ");
		scanf("%d",&(o1[i].arr));
		if(o1[i].arr<0)
		{
			printf("\n\t\t\tTime in negative error");
			exit(0);
		}
		printf("Enter its Burst Time  : ");
		scanf("%lf",&(o1[i].estRun_t));
		if(o1[i].estRun_t<0)
		{
			printf("\n\t\t\tEstimated run time in negative error");
			exit(0);
		}
		printf("*******************************************************************************************************************\n\n");
		if(min_arrtime==o1[i].arr)
		{
			if(o1[i].estRun_t<runTime)
			{
				strcpy(cur_process,o1[i].process);
				runTime=o1[i].estRun_t;
				min_arrtime=o1[i].arr;		
			}
		}
		else if(min_arrtime>o1[i].arr)
		{
			strcpy(cur_process,o1[i].process);
			runTime=o1[i].estRun_t;
			min_arrtime=o1[i].arr;
		}
	}
	cur_time=min_arrtime;
	min_arrtime=65537;
	for(j=0;j<n;j++)
	{
		for(i=0;i<n;i++)
		{
			if(o1[i].priority!=-1 && strcmp(o1[i].process,cur_process)==0)
			{
				o1[i].priority=-1;
				o1[i].wait_t=cur_time-o1[i].arr;
				cur_time=cur_time+(int)o1[i].estRun_t;
				o1[i].turnAround_t=cur_time-o1[i].arr;
			}
		}
		for(i=0;i<n;i++)
		{
			if(o1[i].priority==-1)
				continue;
			else if(cur_time<o1[i].arr)
			{
				p=1;
				continue;
			}
			else
			{
				p=-1;
				break;
			}
		}
		if(p==1)
		{
			findMinTime();
		}
		else
		{
			for(i=0;i<n;i++)
			{
				if(o1[i].priority!=-1 && cur_time>o1[i].arr)
				{
					o1[i].wait_t=cur_time-o1[i].arr;
					o1[i].priority=1+(o1[i].wait_t/o1[i].estRun_t);
				}
			}
			findMaxPriority();
		}
		
	}	
	printf("\n\t\t\t\t\n\n");
	printf("\n       Process  Arrival time    Estimated RunTime    Waiting Time     Turn Around Time      Start Time\n\n");
	for(i=0;i<n;i++)
	{
		printf("\n          %s        %3d           %3.0lf        %6d 	         %4.0lf		    %3d  ",o1[i].process,o1[i].arr,o1[i].estRun_t,o1[i].wait_t,o1[i].turnAround_t,o1[i].arr+o1[i].wait_t);
		avgTurnAround_t=avgTurnAround_t+o1[i].turnAround_t;
		avgWait_t=avgWait_t+o1[i].wait_t;
	}
	printf("\n\t\tAverage Waiting Time of all the processes is %.2lf units",avgWait_t/n);
	printf("\n\t\tAverage Turn Around Time of all the processes is %.2lf units\n",avgTurnAround_t/n);
	
}
