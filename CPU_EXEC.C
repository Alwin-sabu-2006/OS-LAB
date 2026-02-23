#include<stdio.h>
int main()
{
int n;
int completed=0;
float fcfsavg_wt=0;
float srtfavg_wt=0;


printf("Enter the number of processes:");
scanf("%d",&n);
int pid[n],arr[n],compt[n],burst[n],tat[n],wait[n],rt[n];
for(int i=0;i<n;i++)
{
 pid[i]=i+1;
 printf("Enter the arrival time and burst time:");
 scanf("%d%d",&arr[i],&burst[i]);
 rt[i]=burst[i];
 
}
int time=0;
for(int i=0;i<n;i++)
{
 if(time<arr[i])
 {
 time=arr[i];
 
 }
 
 
 compt[i]=time+burst[i];
 time=compt[i];
 
 tat[i]=compt[i]-arr[i];
 wait[i]=tat[i]-burst[i];
 
}

float total_wt = 0;
printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
for (int i = 0; i < n; i++) {
        total_wt += wait[i]; 
        fcfsavg_wt=total_wt/n;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], arr[i], burst[i], compt[i], tat[i], wait[i]);
    }
printf("The average waiting time is:%f",fcfsavg_wt);    


printf("\n SRTF SCHEDULING:");

while (completed != n) {
        int best = -1;

     
        for (int i = 0; i < n; i++) {
            if (arr[i] <= time && rt[i] > 0) {
                if (best == -1 || rt[i] < rt[best]) {
                    best = i;
                }
            }
        }

        if (best != -1) {
            rt[best]--; 
            if (rt[best] == 0) { 
                completed++;
                compt[best] = time + 1;
                tat[best] = compt[best] - arr[best];
                wait[best] = tat[best] - burst[best];
            }
        }
        time++; 
    }

    float total_wait = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        total_wait += wait[i]; 
        srtfavg_wt=total_wait/n;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], arr[i], burst[i], compt[i], tat[i], wait[i]);
    }

    printf("\nThe average waiting time is: %.2f\n", srtfavg_wt);
 return 0;
 }   
    
