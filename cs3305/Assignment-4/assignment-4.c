#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
    char id[5];
    int burst_time;
    int arrival;
    int fcfs_turnaround;
    int fcfs_wait_t;
    int sjf_turnaround;
    int sjf_wait;
    int sjf_burst_left;
    bool sjf_status;            //true  = complete, false = not complete
    int rr_turnaround;
    int rr_wait;
    int rr_burst_left;
    bool rr_status;            //true  = complete, false = not complete
} Process;


void fcfs(Process *arr, int count);
void sjf(Process *arr, int count);
void rr(Process *arr, int count, int quantum);
int compareArrivalTime(const void *a, const void *b);


int main(int argc, char const *argv[])
{
    FILE *file = fopen(argv[argc - 1], "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    int count = 0;
    char line[50];

    // First pass: Count number of processes
    while (fgets(line, sizeof(line), file)) {
        count++;
    }

    // Allocate memory
    Process *processes = (Process *)malloc(count * sizeof(Process));
    if (!processes) {
        printf("Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    // Reset file pointer so we can store this time
    rewind(file);  

    // Second pass: Read data into array
    //https://stackoverflow.com/questions/61078280/how-to-read-a-csv-file-in-c

    for (int i = 0; i < count; i++) {
        if (fgets(line, sizeof(line), file)) 
        {
            char *token = strtok(line, ",");
            if (token) 
            {
                strncpy(processes[i].id, token, sizeof(processes[i].id) - 1);
                processes[i].id[sizeof(processes[i].id) - 1] = '\0';  
                //store arrival times
                processes[i].arrival = atoi(processes[i].id+1);
            }

            token = strtok(NULL, ",");
            if (token) 
            {
                processes[i].burst_time = atoi(token);
            }
        }
    }

    //Incase the processes arent in order sort them  based on arrival time
    qsort(processes, count, sizeof(Process), compareArrivalTime);
    

    //execute based of the input
    if (strcmp(argv[1], "-f") == 0)
    {
        fcfs(processes, count);
    }
    else if(strcmp(argv[1], "-s") == 0) 
    {
        sjf(processes, count);
    }
    else
    {
        // store quantum argument to an integer
        int quantum = atoi(argv[2]); 
        rr(processes, count, quantum);
    }

    free(processes); 
    return 0;


}

void fcfs(Process *arr, int count)
{
    int current_time = 0; 
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    int wait_time;

    printf("First Come First Served\n");

    for (int i = 0; i < count; i++)
    {
        //check if the next process has arrvied
        if (current_time < arr[i].arrival)
        {
            //increment time if it hasnt
            current_time = arr[i].arrival; 
        }

        // Compute wait time
        if (current_time > i)
        {
            wait_time = current_time - i;
        }
        else
        {
            wait_time = 0;
        }

        // Compute turnaroind time
        int turnaround_time = wait_time + arr[i].burst_time; 

        // Print each line at T
        for (int j = 0; j < arr[i].burst_time; j++)
        {
            printf("T%d : %s - Burst left %d, Wait time %d, Turnaround time %d \n", current_time, arr[i].id, arr[i].burst_time - j, wait_time, (current_time) - i);
            current_time++;
        }

        //update the turn aroung and wait times in struct and locally
        arr[i].fcfs_turnaround = turnaround_time;
        arr[i].fcfs_wait_t = wait_time;
        total_wait_time += wait_time;
        total_turnaround_time += turnaround_time;
    }

    printf("\n\n");
    
    //Print out the other process information needed at the end
    for(int i = 0; i < count; i++)
    {
        printf("\n%s\n\tWaiting time: %d\n\tTurnaround time: %d\n\n", arr[i].id,  arr[i].fcfs_wait_t, arr[i].fcfs_turnaround);
    }

    printf("\n");

    // Print averages
    printf("Total average waiting time: %.1f\n", (float)total_wait_time / count);
    printf("Total average turnaround time: %.1f\n", (float)total_turnaround_time / count);
}

void sjf(Process *arr, int count) 
{
    int curr_time = -1; 
    int completed = 0; 
    int total_wait_time = 0;
    int total_turnaround_time = 0;

    // Current job
    int shortest_job_index = -1;  

    //Initialize the sjf values
    for (int i = 0; i < count; i++) 
    {
        arr[i].sjf_burst_left = arr[i].burst_time;
        arr[i].sjf_turnaround = 0;
        arr[i].sjf_wait = 0;
        arr[i].sjf_status = false;
    }

    printf("Shortest Job First\n");

    //untill all jobs are completed
    while (completed < count)
    {
        //set the current job to an invalid index 
        shortest_job_index = -1;

        //the shortest burst time avaliable 
        //this just needs to be a big number then we will change it
        int min_burst = 2147483647;

        //loop through all processes
        for (int i = 0; i < count; i++) 
        {
            // Find the shortest job that has arrived and is not yet completed
            if (arr[i].arrival <= curr_time && !arr[i].sjf_status && arr[i].sjf_burst_left < min_burst) 
            {
                min_burst = arr[i].sjf_burst_left;
                shortest_job_index = i;
            }
        }

        // If no process is available, CPU is it idle but time increments 
        if (shortest_job_index == -1) 
        {
            curr_time++;
            continue;
        }

        //print the required line
        printf("T%d : %s - Burst left %d, Wait time %d, Turnaround time %d\n", curr_time, arr[shortest_job_index].id, arr[shortest_job_index].sjf_burst_left, arr[shortest_job_index].sjf_wait, arr[shortest_job_index].sjf_turnaround);
        
        // Execute the shortest process for one time tick
        arr[shortest_job_index].sjf_burst_left--;
        curr_time++;

        // Update wait time and turnaround time for all processes
        for (int i = 0; i < count; i++) 
        {
            if (arr[i].arrival < curr_time && !arr[i].sjf_status) 
            {
                arr[i].sjf_turnaround++; 
                // Wait time increments only if it's not the currently running process
                if (i != shortest_job_index) 
                {
                    arr[i].sjf_wait++; 
                }
            }
        }

        // Mark process as completed if burst time reaches zero
        if (arr[shortest_job_index].sjf_burst_left == 0) 
        {
            arr[shortest_job_index].sjf_status = true;
            completed++;
        }
    }
    printf("\n\n");

    //Print individual processes stats

    for(int i = 0; i < count; i++)
    {
        printf("\n%s\n\tWaiting time: %d\n\tTurnaround time: %d\n\n", arr[i].id,  arr[i].sjf_wait, arr[i].sjf_turnaround);
        //add each process to the total weight times
        total_turnaround_time += arr[i].sjf_turnaround;
        total_wait_time += arr[i].sjf_wait;
    }

    printf("\n");

    // Print averages
    printf("Total average waiting time: %.1f\n", (float)total_wait_time / count);
    printf("Total average turnaround time: %.1f\n", (float)total_turnaround_time/count);
}

void rr(Process *arr, int count, int quantum) 
{
    // Initialize variables
    for (int i = 0; i < count; i++) 
    {
        arr[i].rr_burst_left = arr[i].burst_time;
        arr[i].rr_status = false;
        arr[i].rr_wait = 0;
        arr[i].rr_turnaround = 0;
    }

    int completed = 0; 
    int current_time = 0; 
    int total_wait_time = 0;
    int total_turnaround_time = 1;

    // Current index process 
    int i = 0; 

    printf("Round Robin (Quantum = %d)\n", quantum);

    while (completed < count) 
    {
        //check if processes ran
        int executed = 0; 

        for (int j = 0; j < count; j++) 
        {
            if (arr[j].rr_burst_left > 0) 
            {
                executed = 1; // A process was executed
                int execute_time;

                //calc execute time 
                if (arr[j].rr_burst_left > quantum)
                {
                    //if we have more burst then quantum set it to quantum
                    execute_time = quantum;
                }
                else
                {
                    //if not we set the execuction time to the number of bursts left
                    execute_time = arr[j].rr_burst_left;
                }

                
                for (int t = 0; t < execute_time; t++) 
                {
                    // Update wait time and turnaround time for all processes
                    for (int k = 0; k < count; k++) 
                    {
                        if (arr[k].arrival <= current_time && !arr[k].rr_status) 
                        {
                            arr[k].rr_turnaround++; 
                            // Wait time increments only if it's not the currently running process
                            if (k != j) 
                            {
                                arr[k].rr_wait++; 
                            }
                        }
                    }

                    // Print required line
                    printf("T%d : %s - Burst left %d, Wait time %d, Turnaround time %d\n", current_time, arr[j].id, arr[j].rr_burst_left, arr[j].rr_wait, arr[j].rr_turnaround-1);

                    //Exectute the processes and increment time
                    arr[j].rr_burst_left--;
                    current_time++;

                    // If process is finished, mark it as completed
                    if (arr[j].rr_burst_left == 0) 
                    {
                        arr[j].rr_status = true;
                        completed++;
                        break; // Exit the loop early when a process completes
                    }
                }
            }
        }

        // If no process was executed, move time forward
        if (executed == 0) 
        {
            current_time++;
        }
    }

    printf("\n\n");

    // Print final stats
    for (int j = 0; j < count; j++)
    {
        printf("\n%s\n\tWaiting time: %d\n\tTurnaround time: %d\n", arr[j].id, arr[j].rr_wait, arr[j].rr_turnaround);
        //store averages from each process
        total_wait_time += arr[j].rr_wait;
        total_turnaround_time += arr[j].rr_turnaround;
    }

    printf("\n");

    //print avaerages
    printf("Total average waiting time: %.1f\n", (float)total_wait_time / count);
    printf("Total average turnaround time: %.1f\n", (float)total_turnaround_time / count);
}

//Compare function for the qsort in main
//https://stackoverflow.com/questions/3489139/how-to-qsort-an-array-of-pointers-to-char-in-c
int compareArrivalTime(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->arrival - p2->arrival;
}






    