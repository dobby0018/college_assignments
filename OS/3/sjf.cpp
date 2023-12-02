#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Structure to represent a process
struct Process
{
    int process_id;   // Process ID
    int arrival_time; // Arrival time of the process
    int burst_time;   // Burst time of the process
};

// Function to calculate waiting time for each process using SJF algorithm
void findWaitingTime(Process processes[], int n, int waiting_time[])
{
    vector<pair<int, int>> remaining_time; // Pair of remaining burst time and process ID

    // Initialize remaining time vector
    for (int i = 0; i < n; i++)
    {
        remaining_time.push_back({processes[i].burst_time, i});
    }

    int completed = 0;    // Number of completed processes
    int current_time = 0; // Current time

    // Sort processes by arrival time for tie-breaking
    sort(remaining_time.begin(), remaining_time.end(), [&processes](pair<int, int> a, pair<int, int> b)
         {
        if (a.first == b.first) {
            return processes[a.second].arrival_time < processes[b.second].arrival_time;
        }
        return a.first < b.first; });

    while (completed < n)
    {
        int shortest_index = -1;
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i].first > 0 && processes[remaining_time[i].second].arrival_time <= current_time)
            {
                if (shortest_index == -1 || remaining_time[i].first < remaining_time[shortest_index].first)
                {
                    shortest_index = i;
                }
            }
        }

        if (shortest_index == -1)
        {
            current_time++;
        }
        else
        {
            int process_id = remaining_time[shortest_index].second;
            waiting_time[process_id] = current_time - processes[process_id].arrival_time;
            current_time += processes[process_id].burst_time;
            remaining_time[shortest_index].first = 0;
            completed++;
        }
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

    // Calculate and display average waiting time and average turnaround time
    findAverageTime(processes, n);

    return 0;
}
// 4 
// 0 
// 6 
// 2 
// 8 
// 3 
// 7 
// 5 
// 3
