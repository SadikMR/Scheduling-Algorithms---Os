#include <bits/stdc++.h>
using namespace std;

struct process {
    int AT;
    int pid;
    int BT;
    int CT;
    int TAT;
    int WT;
    int ST;
    int RT;
};

void runRoundRobin (int n, int time_quantum, process p[]) {
    vector<int> remaining_time (n), started (n, 0), alreadyInQueue (n, 0);
    for (int i = 0; i < n; i++) {
        remaining_time[i] = p[i].BT;
    }
    int completed = 0, cur_time = 0, prev = -1;
    queue<int> rq;

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= cur_time && remaining_time[i] > 0 && !alreadyInQueue[i]) {
                rq.push (i);
                alreadyInQueue[i] = 1;
            }
        }
        if (prev != -1 && remaining_time[prev] > 0) {
            rq.push (prev);
        }

        if (!rq.empty ()) {
            int ind = rq.front ();
            rq.pop ();
            if (!started[ind]) {
                p[ind].ST = cur_time;
                started[ind] = 1;
            }
            if (remaining_time[ind] > time_quantum) {
                cur_time += time_quantum;
                remaining_time[ind] -= time_quantum;
            } else {
                cur_time += remaining_time[ind];
                remaining_time[ind] = 0;
                p[ind].CT = cur_time;
                p[ind].TAT = p[ind].CT - p[ind].AT;
                p[ind].WT = p[ind].TAT - p[ind].BT;
                p[ind].RT = p[ind].ST - p[ind].AT;
                completed++;
            }
            prev = ind;
        } else {
            cur_time++;
        }
    }
}

void print (int n, process p[]) {
    cout << "PID\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << '\t' << p[i].AT << '\t' << p[i].BT << '\t' << p[i].CT << '\t'
             << p[i].TAT << '\t' << p[i].WT << '\t' << p[i].RT << '\n';
    }
}

int main () {
    int n, time_quantum;
    cin >> n >> time_quantum;
    process p[n];

    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].AT >> p[i].BT;
    }

    runRoundRobin (n, time_quantum, p);
    print (n, p);
}
