#include <stdio.h>
#include <stdlib.h>

#define max 100
#define Time_quantom 20

typedef struct Process {
    int p_id; // Process id
    int priority_lvl; // Priority level
    int b_time; // Burst time
    int r_time; // Remaining time
    int sw_time; // Start waiting time
} Process;

typedef struct Queue {
    Process queue[max];
    int front, rear;
} Queue;

Queue queues[4]; // Queues

// Enqueue
void enqueue(int priority_lvl, Process process) {
    queues[priority_lvl].queue[queues[priority_lvl].rear++] = process;
}

// Dequeue
Process dequeue(int priority_lvl) {
    return queues[priority_lvl].queue[queues[priority_lvl].front++];
}

// Round Robin
void roundRobin(int priority_lvl, int num_processes) {
    int time_left[max];
    for (int i = 0; i < num_processes; i++) {
        time_left[i] = queues[priority_lvl].queue[i].r_time;
    }

    int current_time = 0;
    while (1) {
        int tag = 1;

        for (int i = 0; i < num_processes; i++) {
            if (time_left[i] > 0) {
                tag = 0;

                if (time_left[i] > Time_quantom) {
                    current_time += Time_quantom;
                    time_left[i] -= Time_quantom;

                    if (queues[priority_lvl].queue[i].sw_time == -1) {
                        queues[priority_lvl].queue[i].sw_time = current_time - Time_quantom;
                    }
                } else {
                    current_time += time_left[i];
                    time_left[i] = 0;

                    if (queues[priority_lvl].queue[i].sw_time == -1) {
                        queues[priority_lvl].queue[i].sw_time = current_time - queues[priority_lvl].queue[i].b_time;
                    }
                }
                queues[priority_lvl].queue[i].r_time = current_time;
            }
        }

        if (tag == 1) {
            break;
        }
    }
}

// Shortest Job First
void shortestJobFirst(int priority_lvl, int num_processes) {
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (queues[priority_lvl].queue[j].b_time > queues[priority_lvl].queue[j + 1].b_time) {
                Process temp = queues[priority_lvl].queue[j];
                queues[priority_lvl].queue[j] = queues[priority_lvl].queue[j + 1];
                queues[priority_lvl].queue[j + 1] = temp;
            }
        }
    }
    int current_time = 0;
    for (int i = 0; i < num_processes; i++) {
        queues[priority_lvl].queue[i].r_time = current_time; // Calculating remaining time
        current_time += queues[priority_lvl].queue[i].b_time;
        queues[priority_lvl].queue[i].sw_time = current_time - queues[priority_lvl].queue[i].b_time;
    }
}

// First In First Out
void fifo(int priority_lvl, int num_processes) {
    int current_time = 0;
    for (int i = 0; i < num_processes; i++) {
        queues[priority_lvl].queue[i].r_time = current_time; // Calculating remaining time
        current_time += queues[priority_lvl].queue[i].b_time;
        queues[priority_lvl].queue[i].sw_time = current_time - queues[priority_lvl].queue[i].b_time;
    }
}

int main() {
    int num_processes;
    printf("How many Processes do you want to Enter : ");
    scanf("%d", &num_processes);
    printf("\n");

    for (int i = 0; i < 4; i++) {
        queues[i].front = 0;
        queues[i].rear = 0;
    }
    //Getting details
    printf("<<<-----------------------Enter Details------------------------>>>\n\n");
    for (int i = 0; i < num_processes; i++) {
        Process p;
        printf("Enter details for process %d --->> \n\n", i + 1);
        p.p_id = i + 1;
        printf("+ Priority Level (0 to 3): ");
        scanf("%d", &p.priority_lvl);
        printf("\n");
        printf("+ Burst Time: ");
        scanf("%d", &p.b_time);
        printf("\n");

        p.r_time = p.b_time;
        p.sw_time = -1; 
        enqueue(p.priority_lvl, p);
    }

    int current_time = 0;
    int switch_time = 0;

    for (int priority_lvl = 0; priority_lvl < 4; priority_lvl++) {
        int num_processes_in_queue = queues[priority_lvl].rear - queues[priority_lvl].front;

        switch (priority_lvl) {
            case 0:
                roundRobin(priority_lvl, num_processes_in_queue);
                break;
            case 1:
            case 2:
                shortestJobFirst(priority_lvl, num_processes_in_queue);
                break;
            case 3:
                fifo(priority_lvl, num_processes_in_queue);
                break;
            default:
                break;
        }
        //Switching Queues After every 20 Seconds
        current_time += Time_quantom;

        if (priority_lvl < 3 && current_time >= switch_time + Time_quantom) {
            switch_time = current_time;
            current_time = 0;
            priority_lvl = -1; 
        }
    }
    //The printing part
    printf("----------------------------------------------------------------------------------------\n");
    printf("\n| Process ID\t| Priority level\t| Burst Time\t| Waiting Time\t| Turnaround Time |\n");
    printf("----------------------------------------------------------------------------------------\n");

    int waiting_time;
    for (int priority_lvl = 0; priority_lvl < 4; priority_lvl++) {
        for (int i = 0; i < queues[priority_lvl].rear; i++) {
            if (queues[priority_lvl].queue[i].priority_lvl == priority_lvl) {
                if (queues[priority_lvl].queue[i].sw_time == -1) {
                    queues[priority_lvl].queue[i].sw_time = current_time;
                }

                waiting_time = current_time - queues[priority_lvl].queue[i].sw_time;
                if (priority_lvl > 0) {
                    for (int j = 0; j < priority_lvl; j++) {
                        waiting_time += (queues[j].rear - queues[j].front) * Time_quantom;
                    }
                }
                int turnaround_time = waiting_time + queues[priority_lvl].queue[i].b_time;

                printf("| %d\t|\t\t%d\t\t| %d\t\t| %d\t\t| %d\t\t|\n", queues[priority_lvl].queue[i].p_id,
                queues[priority_lvl].queue[i].priority_lvl, queues[priority_lvl].queue[i].b_time, waiting_time, turnaround_time);
                printf("----------------------------------------------------------------------------------------\n");

            }   
        }
    }

    return 0;
}

/*  • Name :- R.K.Janith Prabash Kahmira
    • Registration Number :- 2022/CS/086
    • Index Number :- 22000862*/