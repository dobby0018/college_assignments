#include <iostream>
using namespace std;

class sequencing {
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int status;
    int priority;
    int remaining_time;

public:
    void input(int);
    void PRIPRE(int, sequencing[]);
    void output(int);
    int minimum(int, sequencing[]);
};

#define pending 1
#define finished 2

void sequencing::input(int i) {
    cout << "\nP[" << i + 1 << "] >>\nBURST TIME : ";
    cin >> burst_time;
    cout << "ARRIVAL TIME : ";
    cin >> arrival_time;
    cout << "PRIORITY : ";
    cin >> priority;
    status = pending;
    remaining_time = burst_time;
}

void sequencing::output(int i) {
    cout << "P[" << i + 1 << "] \t" << burst_time << "\t\t" << arrival_time << "\t " << waiting_time << "\t\t " << turnaround_time << "\t\t" << priority << endl;
}

void sequencing::PRIPRE(int n, sequencing p[]) {
    int total_time = 0;
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;

    cout << "\nGantt Chart:" << endl;
    cout << endl;
    cout << "0|";

    while (true) {
        int pt = 9999;
        int k = -1;

        for (int j = 0; j < n; j++) {
            if (p[j].status == pending && p[j].arrival_time <= total_time) {
                if (p[j].priority < pt) {
                    k = j;
                    pt = p[j].priority;
                }
                else if (p[j].priority == pt && p[j].remaining_time < p[k].remaining_time) {
                    k = j;
                }
            }
        }

        if (k == -1) {
            int min_arrival = 9999;
            for (int i = 0; i < n; i++) {
                if (p[i].status == pending && p[i].arrival_time < min_arrival) {
                    min_arrival = p[i].arrival_time;
                    k = i;
                }
            }
            total_time = min_arrival;
        }

        int j, check = 0;
        for (j = 0; j < p[k].remaining_time; j++) {
            for (int l = 0; l < n; l++) {
                if (l != k) {
                    if (p[l].status == pending && p[l].arrival_time == total_time + j) {
                        if (p[l].priority <= p[k].priority) {
                            check = 1;
                            break;
                        }
                    }
                }
            }
            if (check)
                break;
        }

        total_time += j;
        if (j == p[k].remaining_time) {
            p[k].status = finished;
            p[k].turnaround_time = total_time - p[k].arrival_time;
            avg_turnaround_time += p[k].turnaround_time;
            p[k].waiting_time = p[k].turnaround_time - p[k].burst_time;
            avg_waiting_time += p[k].waiting_time;
        }
        else {
            p[k].remaining_time -= j;
        }

        cout << "___P" << k + 1 << "___|" << total_time << "|";

        int if_finished = 0;
        for (int i = 0; i < n; i++)
            if (p[i].status == pending)
                if_finished = 1;
        if (!if_finished)
            break;
    }

    cout << "\n";
    cout << "\nAVERAGE WAITING TIME : " << avg_waiting_time / n;
    cout << "\nAVERAGE TURNAROUND TIME : " << avg_turnaround_time / n << endl;
}

int sequencing::minimum(int n, sequencing p[]) {
    int min = 9999;
    for (int i = 0; i < n; i++)
        if (p[i].arrival_time < min)
            min = p[i].arrival_time;
    return min;
}

int main() {
    int n;
    cout << "ENTER THE NUMBER OF JOBS : ";
    cin >> n;

    sequencing *p;
    p = new sequencing[n];

    for (int i = 0; i < n; i++)
        p[i].input(i);

    sequencing x;
    x.PRIPRE(n, p);

    cout << "\nPROCESS BURST TIME ARRIVALTIME WAITINGTIME TURNAROUND_TIME PRIORITY :\n ";
    for (int i = 0; i < n; i++)
        p[i].output(i);

    delete[] p; // Release dynamically allocated memory
    return 0;
}
// 4
// 6
// 0
// 3
// 4
// 1
// 1
// 8
// 2
// 5
// 3
// 2
// 3