#include <bits/stdc++.h>
using namespace std;

struct process {
    int pid;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int RT;
};

bool compare (const process &a, const process &b) {
    if (a.BT != b.BT) {
        return a.BT < b.BT;
    } else if (a.AT != b.AT) {
        return a.AT < b.AT;
    } else {
        return a.pid < b.pid;
    }
};

void runSJF (int n, process p[]) {
    int completed = 0, cur_time = 0;
    vector<bool> is_completed (n, 0);
    deque<process> ready_queue;
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= cur_time && !is_completed[i]) {
                ready_queue.push_back (p[i]);
                is_completed[i] = 1;
            }
        }
        if (!ready_queue.empty ()) {
            sort (ready_queue.begin (), ready_queue.end (), compare);
            process cur = ready_queue.front ();
            ready_queue.pop_front ();
            int idx = cur.pid - 1;
            p[idx].CT = cur_time + p[idx].BT;
            p[idx].TAT = p[idx].CT - p[idx].AT;
            p[idx].WT = p[idx].TAT - p[idx].BT;
            p[idx].RT = cur_time - p[idx].AT;
            cur_time = p[idx].CT;
            completed++;
        } else {
            cur_time++;
        }
    }
}

void print (int n, process p[]) {
    cout << "PID\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << '\n';
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << '\t' << p[i].AT << '\t' << p[i].BT << '\t' << p[i].CT << '\t' << p[i].TAT << '\t' << p[i].WT << '\t' << p[i].RT << '\n';
    }
}

int main () {
    int n;
    cin >> n;
    process p[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].AT >> p[i].BT;
    }
    runSJF (n, p);
    print (n, p);
}