#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], arr[n], burst[n], priority[n];
    int compt[n], tat[n], wait[n], is_done[n];
    float total_wt = 0;
    float avg_wts[4];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for P%d: ", pid[i]);
        scanf("%d %d %d", &arr[i], &burst[i], &priority[i]);
    }

   
    int time = 0;
    total_wt = 0;
    printf("\n--- FCFS SCHEDULING ---\n");
    for (int i = 0; i < n; i++) {
        if (time < arr[i]) time = arr[i];
        compt[i] = time + burst[i];
        time = compt[i];
        tat[i] =  compt[i] - arr[i];
        wait[i] = tat[i] - burst[i];
        total_wt += wait[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], arr[i], burst[i], compt[i], tat[i], wait[i]);
    }
    printf("Average Waiting Time (FCFS): %.2f\n", total_wt / n);
    avg_wts[0]=total_wt /n;

   
    for (int i = 0; i < n; i++) is_done[i] = 0;
    time = 0;
    int completed = 0;
    total_wt = 0;

    printf("\nSJF SCHEDULING ---\n");
    while (completed < n) {
        int best = -1;
        int min_burst = 1e9;

        for (int i = 0; i < n; i++) {
            if (arr[i] <= time && !is_done[i]) {
                if (burst[i] < min_burst) {
                    min_burst = burst[i];
                    best = i;
                }
            }
        }

        if (best != -1) {
            time += burst[best];
            compt[best] = time;
            tat[best] = compt[best] - arr[best];
            wait[best] = tat[best] - burst[best];
            total_wt += wait[best];
            is_done[best] = 1;
            completed++;
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[best], arr[best], burst[best], compt[best], tat[best], wait[best]);
        } else {
            time++; 
        }
    }
    printf("Average Waiting Time (SJF): %.2f\n", total_wt / n);
    avg_wts[1]=total_wt/n;

       for (int i = 0; i < n; i++) is_done[i] = 0;
    time = 0;
    completed = 0;
    total_wt = 0;

    #include <limits.h>



printf("\n PRIORITY SCHEDULING\n");
while (completed < n) {
    int best = -1;
    int highest_priority = INT_MAX;

    for (int i = 0; i < n; i++) {
       
        if (arr[i] <= time && !is_done[i]) {
            
            if (priority[i] < highest_priority) {
                highest_priority = priority[i];
                best = i;
            }
       
            else if (priority[i] == highest_priority) {
                if (arr[i] < arr[best]) {
                    best = i;
                }
            }
        }
    }

    if (best != -1) {
        time =time + burst[best];
        compt[best] = time;
        tat[best] = compt[best] - arr[best];
        wait[best] = tat[best] - burst[best];
        total_wt += wait[best];
        is_done[best] = 1;
        completed++;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[best], arr[best], burst[best], compt[best], tat[best], wait[best]);
    } else {
        time++; 
    }
}
avg_wts[2]=total_wt/n;
printf("Average Waiting Time (Priority): %.2f\n", total_wt / n);


    int quantum = 3; 
    int rem_bt[n];
    for (int i = 0; i < n; i++) {
        rem_bt[i] = burst[i]; 
    }

    time = 0;
    completed = 0;
    total_wt = 0;

    printf("\nROUND ROBIN \n");

    while (completed < n) {
        int done_anything = 0;

        for (int i = 0; i < n; i++) {
            
            if (arr[i] <= time && rem_bt[i] > 0) {
                done_anything = 1;

                if (rem_bt[i] > quantum) {
                    
                    time += quantum;
                    rem_bt[i] -= quantum;
                } else {
                  
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    completed++;

                   
                    compt[i] = time;
                    tat[i] = compt[i] - arr[i];
                    wait[i] = tat[i] - burst[i];
                    total_wt += wait[i];

                    printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
                           pid[i], arr[i], burst[i], compt[i], tat[i], wait[i]);
                }
            }
        }

        
        if (done_anything == 0) {
            time++;
        }
    }
    avg_wts[3]=total_wt/n;
    printf("Average Waiting Time (Round Robin): %.2f\n", total_wt / n);
    
   // 0:FCFS, 1:SRTF, 2:Priority, 3:RR
    char *names[] = {"FCFS", "SRTF", "Priority", "Round Robin"};

 

    printf("\n--- FINAL COMPARISON ---\n");
    for (int i = 0; i < 4; i++) {
        printf("%s Average Waiting Time: %.2f\n", names[i], avg_wts[i]);
    }

    float min_avg = avg_wts[0];
    int best_pr = 0;

    for (int i = 1; i < 4; i++) {
        if (avg_wts[i] < min_avg) {
            min_avg = avg_wts[i];
            best_pr= i;
        }
    }

    printf("\nConclusion: %s is the most efficient algorithm for this process mix (Avg WT: %.2f).\n", 
           names[best_pr], min_avg);
    

    return 0;
}
 
 
 
   
