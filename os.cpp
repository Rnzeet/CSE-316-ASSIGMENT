#include<stdio.h>
#include<stdlib.h>
typedef struct
{
    int arrival_time,burst_time,queue;
    int process_id;
}process;
int main()
{
	 int s,time_quantum,done =0;
    int count = 0;
    int time,smallest,waiting_time[30],turnaround_time[30],completion[30],temp_burst[30];
    double average_wait_time, average_turnaround_time;
   printf("\nEnter the number of processes:");
    scanf("%d",&s);
    process no[s];
    for(int i = 0; i <s; i++)
	{
		printf("\nProcess ID:\t");
		scanf("%d", &no[i].process_id);
		printf("Arrival Time:\t");
		scanf("%d", &no[i].arrival_time);
		printf("Burst Time:\t");
		scanf("%d", &no[i].burst_time);
		printf("Queue1/Queue2(1/2):\t");
		scanf("%d", &no[i].queue);
	}
	printf("\nEnter the time quantum for Round Robin:");
	scanf("%d",&time_quantum);
    for(int i=0;i<s;i++)
    {
        temp_burst[i] = no[i].burst_time;
    }
    no[s+1].burst_time = 999;
    for(time=0;count!=s;time++) 
    {
         smallest = s+1;
         for(int i=0;i<s;i++)
         {
            if(no[i].arrival_time<=time && no[i].burst_time<no[smallest].burst_time && no[i].burst_time>0 && no[i].queue == 1)
            {
                smallest=i;
            }
         }
         if(count >= s/2) 
          {
            while(1)
            {
              for(int j=0;j<s;j++)
              {
                  if(no[j].arrival_time<=time && no[j].burst_time > time_quantum && no[j].queue == 2 )
                  {
                      no[j].burst_time -= time_quantum;
                      smallest = j;
                  }
                  else if(no[j].arrival_time<=time && no[j].burst_time < time_quantum && no[j].queue == 2)
                  {
                      no[j].burst_time = 0;
                      smallest = j;
                      goto a;
                  }
              }
            }
          }
           no[smallest].burst_time--; 
        a: if(no[smallest].burst_time == 0)
         {
            count++;
            completion[smallest] = time+1;
            turnaround_time[smallest] = completion[smallest] - no[smallest].arrival_time;
            waiting_time[smallest] = turnaround_time[smallest] - temp_burst[smallest];
         }
    }
     printf("\n\nProcess Id\tArrival Time\t Burst Time\t Waiting Time\tTurnaround Time");
    for(int i=0;i<s;i++)
    {
        printf("\n   P%d   \t\t%d\t\t%d  \t\t%d\t\t%d",no[i].process_id,no[i].arrival_time,temp_burst[i],waiting_time[i],turnaround_time[i]);
        average_wait_time += waiting_time[i];
        average_turnaround_time += turnaround_time[i];
    }
    printf("\n\nAverage waiting time = %lf\n",average_wait_time/s);
    printf("Average Turnaround time = %lf",average_turnaround_time/s);
}
