#include <iostream>
using namespace std;

class sequencing {
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int status;

public:
    void input(int);
    void round_robin(int, sequencing[]);
    void output(int);
    int minimum(int, sequencing[]);
};

#define max 200
int q[max];
int front = -1;
int rear = -1;

int isempty() {
    if (front == -1)
        return 1;
    else
        return 0;
}

int isfull() {
    if (front == (rear + 1) % max)
        return 1;
    else
        return 0;
}

void ins(int a) {
    if (!isfull()) {
        rear = (rear + 1) % max;
        q[rear] = a;
        if (front == -1)
            front = 0;
    } else {
        cout << "Queue is full...\n";
    }
}

int del() {
    int x = -1;
    if (!isempty()) {
        x = q[front];
        if (front == rear)
            front = rear = -1;
        else
            front = (front + 1) % max;
    }
    return x;
}

void sequencing::input(int i) {
    cout << "\nP[" << i + 1 << "] >>\nBURST TIME : ";
    cin >> burst_time;
    cout << "ARRIVAL TIME : ";
    cin >> arrival_time;
    status = 0;
    remaining_time = burst_time;
}

void sequencing::output(int i) {
    cout << "P[" << i + 1 << "] \t" << burst_time << "\t\t" << arrival_time << "\t " << waiting_time << "\t\t " << turnaround_time << endl;
}

void sequencing::round_robin(int n, sequencing p[]) {
    int time_lapse;
    cout << "Enter the time lapse: ";
    cin >> time_lapse;

    int total_time = minimum(n, p);
    int quantum = time_lapse;

    int *temp = new int[n];

    for (int i = 0; i < n; i++) {
        temp[i] = p[i].burst_time;
    }

    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (temp[i] > 0) {
                done = false;

                if (temp[i] > quantum) {
                    total_time += quantum;
                    temp[i] -= quantum;
                } else {
                    total_time += temp[i];
                    p[i].waiting_time = total_time - p[i].burst_time - p[i].arrival_time;
                    temp[i] = 0;
                }
            }
        }

        if (done)
            break;
    }

    cout << "\nProcess BURST_Time Arrival_Time Waiting_Time Turnaround_Time :\n";
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
        p[i].output(i);
    }

    delete[] temp;
}

int sequencing::minimum(int n, sequencing p[]) {
    int min = 9999;
    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time < min)
            min = p[i].arrival_time;
    }
    return min;
}

int main() {
    int n;
    cout << "ENTER THE NUMBER OF JOBS: ";
    cin >> n;

    sequencing *p;
    p = new sequencing[n];

    for (int i = 0; i < n; i++)
        p[i].input(i);

    sequencing x;
    x.round_robin(n, p);

    delete[] p;
    return 0;
}
// 4
// 6
// 0
// 4
// 1
// 3
// 2
// 8
// 3
// 5
