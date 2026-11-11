#include <iostream>
#include <iomanip>
using namespace std;

// FCFS (First Come First Serve) CPU Scheduling
class FCFS {
    int n;                                   // total number of processes
    int at[100], bt[100], ct[100], tat[100], wt[100];
    // at  = Arrival Time     (when the process arrives)
    // bt  = Burst Time       (CPU time required by the process)
    // ct  = Completion Time  (when the process finishes)
    // tat = Turnaround Time  (completion time - arrival time)
    // wt  = Waiting Time     (time spent waiting in the ready queue)

public:

    // Function to take input from the user
    void input() {
        cout << "Enter number of processes: ";
        cin >> n;                            // read number of processes

        for (int i = 0; i < n; i++) {
            cout << "Enter AT and BT for P" << i + 1 << ": ";
            cin >> at[i] >> bt[i];           // read AT and BT of each process
        }
    }

    // Function to calculate CT, TAT and WT
    void calculate() {

        // Completion time of the first process = AT + BT
        ct[0] = at[0] + bt[0];

        // For the remaining processes:
        // CT = max(previous process CT, own AT) + BT
        // max is used because the CPU may be idle until the process arrives
        for (int i = 1; i < n; i++) {
            ct[i] = max(ct[i - 1], at[i]) + bt[i];
        }

        for (int i = 0; i < n; i++) {
            tat[i] = ct[i] - at[i];          // TAT = CT - AT
            wt[i] = tat[i] - bt[i];          // WT  = TAT - BT
        }
    }

    // Function to print the result table
    void display() {

        int totalWT = 0;                     // sum of all waiting times
        int totalTAT = 0;                    // sum of all turnaround times

        // Print table header
        cout << "\n";
        cout << left
             << setw(6) << "P"
             << setw(6) << "AT"
             << setw(6) << "BT"
             << setw(6) << "CT"
             << setw(7) << "TAT"
             << setw(6) << "WT" << endl;

        // Print data of each process
        for (int i = 0; i < n; i++) {

            cout << left
                 << setw(6) << "P" + to_string(i + 1)   // process name (P1, P2, ...)
                 << setw(6) << at[i]
                 << setw(6) << bt[i]
                 << setw(6) << ct[i]
                 << setw(7) << tat[i]
                 << setw(6) << wt[i] << endl;

            totalWT += wt[i];                // add up for the average
            totalTAT += tat[i];
        }

        cout << fixed << setprecision(2);    // show 2 digits after the decimal point

        // average = total / number of processes
        cout << "Average Waiting Time = " << (float)totalWT / n << endl;
        cout << "Average Turnaround Time = " << (float)totalTAT / n << endl;
    }
};

int main() {

    FCFS obj;           // create an object of the class

    obj.input();        // 1. take input
    obj.calculate();    // 2. do the calculations
    obj.display();      // 3. show the result

    return 0;
}
