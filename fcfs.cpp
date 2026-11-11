#include <iostream>
#include <iomanip>
using namespace std;

// FCFS (First Come First Serve) CPU Scheduling
class FCFS {
    int n;                                   // total process shongkha
    int at[100], bt[100], ct[100], tat[100], wt[100];
    // at  = Arrival Time     (process kokhon ashlo)
    // bt  = Burst Time       (CPU te koto shomoy lagbe)
    // ct  = Completion Time  (kokhon shesh hoyeche)
    // tat = Turnaround Time  (shesh hoyar shomoy - ashar shomoy)fcfs.cpp
    // wt  = Waiting Time     (koto shomoy opekkha korte hoyeche)

public:

    // User theke input nowar function
    void input() {
        cout << "Enter number of processes: ";
        cin >> n;                            // process er shongkha input

        for (int i = 0; i < n; i++) {
            cout << "Enter AT and BT for P" << i + 1 << ": ";
            cin >> at[i] >> bt[i];           // protita process er AT ar BT input
        }
    }

    // CT, TAT ar WT hishab korar function
    void calculate() {

        // prothom process er CT = AT + BT
        ct[0] = at[0] + bt[0];

        // baki process er CT = (ager process er CT ar nijer AT er boro ta) + BT
        // max use kora hoyeche karon CPU idle thakte pare (process ashar age)
        for (int i = 1; i < n; i++) {
            ct[i] = max(ct[i - 1], at[i]) + bt[i];
        }

        for (int i = 0; i < n; i++) {
            tat[i] = ct[i] - at[i];          // TAT = CT - AT
            wt[i] = tat[i] - bt[i];          // WT  = TAT - BT
        }
    }

    // Result table print korar function
    void display() {

        int totalWT = 0;                     // moট waiting time
        int totalTAT = 0;                    // mot turnaround time

        // table er header print
        cout << "\n";
        cout << left
             << setw(6) << "P"
             << setw(6) << "AT"
             << setw(6) << "BT"
             << setw(6) << "CT"
             << setw(7) << "TAT"
             << setw(6) << "WT" << endl;

        // protita process er data print
        for (int i = 0; i < n; i++) {

            cout << left
                 << setw(6) << "P" + to_string(i + 1)   // process er naam (P1, P2...)
                 << setw(6) << at[i]
                 << setw(6) << bt[i]
                 << setw(6) << ct[i]
                 << setw(6) << tat[i]
                 << setw(6) << wt[i] << endl;

            totalWT += wt[i];                // average er jonno jog korchi
            totalTAT += tat[i];
        }

        cout << fixed << setprecision(2);    // dosomik er por 2 ghor porjonto dekhabe

        // average = mot / process shongkha
        cout << "Average Waiting Time = " << (float)totalWT / n << endl;
        cout << "Average Turnaround Time = " << (float)totalTAT / n << endl;
    }
};

int main() {

    FCFS obj;           // class er object toiri

    obj.input();        // 1. input nao
    obj.calculate();    // 2. hishab koro
    obj.display();      // 3. result dekhao

    return 0;
}
