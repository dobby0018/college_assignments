#include <iostream>
using namespace std;

// Structure to represent a process
struct Process
{
    int process_id;   // Process ID
    int arrival_time; // Arrival time of the process
    int burst_time;   // Burst time of the process
};

// Function to calculate waiting time for each process
void findWaitingTime(Process processes[], int n, int waiting_time[])
{
    waiting_time[0] = 0; // The first process doesn't wait.

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++)
    {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
    }
}

// Function to calculate turnaround time for each process
void findTurnaroundTime(Process processes[], int n, int waiting_time[], int turnaround_time[])
{
    // Turnaround time = Burst time + Waiting time
    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
    }
}

// Function to calculate average waiting time and average turnaround time
void findAverageTime(Process processes[], int n)
{
    int waiting_time[n];
    int turnaround_time[n];

    // Calculate waiting time and turnaround time
    findWaitingTime(processes, n, waiting_time);
    findTurnaroundTime(processes, n, waiting_time, turnaround_time);

    // Calculate and display average waiting time
    float total_waiting_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += waiting_time[i];
    }
    float average_waiting_time = total_waiting_time / n;

    // Calculate and display average turnaround time
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_turnaround_time += turnaround_time[i];
    }
    float average_turnaround_time = total_turnaround_time / n;

    // Display the Gantt Chart
    cout << "Gantt Chart:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "  | P" << processes[i].process_id << " ";
    }
    cout << "|" << endl;

    // Display the waiting and turnaround times in a tabular form
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << processes[i].process_id << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }

    cout << "Average Waiting Time: " << average_waiting_time << endl;
    cout << "Average Turnaround Time: " << average_turnaround_time << endl;
}

int main()
{
    int n; // Number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++)
    {
        processes[i].process_id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
    }

    // Sort the processes based on arrival time (FCFS)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                // Swap processes
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }// Calculate and display average waiting time and average turnaround time
    findAverageTime(processes, n);

    return 0;
}
// 4
// 0
// 6
// 1
// 4
// 2
// 8
// 3
// 5
