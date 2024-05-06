# Multi-level-queue

# Process Scheduling Simulation

This code simulates a simple process scheduling system with multiple priority queues. The scheduling algorithm supports three different scheduling techniques: Round Robin, Shortest Job First, and First In First Out. The code uses an array of queues to represent different priority levels and simulates the processing of tasks based on their priority and burst times.

## Features

- **Priority Queues**: The code divides processes into four different priority levels (0 to 3), where 0 is the highest priority.
- **Enqueue and Dequeue Operations**: Functions to enqueue and dequeue processes into/from their respective priority queues.
- **Scheduling Techniques**: Implements three common scheduling techniques:
  - **Round Robin**: Used for priority level 0, with a time quantum of 20 units.
  - **Shortest Job First (SJF)**: Applied to priority levels 1 and 2.
  - **First In First Out (FIFO)**: Used for priority level 3.
- **Process Attributes**: Each process has the following attributes:
  - `p_id`: Process ID
  - `priority_lvl`: Priority level
  - `b_time`: Burst time
  - `r_time`: Remaining time (used in Round Robin)
  - `sw_time`: Start waiting time (time at which the process starts waiting)

## Code Structure

- **Initialization**: Initializes four queues for different priority levels and initializes variables to track the current time and queue switching.
- **Process Input**: Prompts the user to input process details, including the number of processes, priority levels, and burst times.
- **Scheduling Algorithm**: Depending on the priority level, the code applies the appropriate scheduling technique.
- **Queue Switching**: The system switches between queues every 20 time units.
- **Output**: After processing, the code outputs the details of each process, including waiting time and turnaround time.

## Usage

To use this code, compile it with a C compiler (e.g., `gcc`) and run the executable. Provide the required input when prompted, including the number of processes, priority levels, and burst times. The output will display the scheduling results with process IDs, priority levels, burst times, waiting times, and turnaround times.

## Notes

- The code uses basic scheduling techniques and does not include complex error handling.
- The system simulates queue switching based on a simple time quantum.
- This is a basic implementation for educational purposes and may require additional optimization for real-world applications.

