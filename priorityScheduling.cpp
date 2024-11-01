#include <bits/stdc++.h>
using namespace std;

struct process {
    int pid;
    int priority;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int RT;
};

bool compare (const process &a, const process &b) {
    if (a.priority != b.priority) {
        return a.priority < b.priority;
    } else if (a.AT != b.AT) {
        return a.AT < b.AT;
    } else if (a.BT != b.BT) {
        return a.BT < b.BT;
    } else {
        return a.pid < b.pid;
    }
}

void runPrioritySceduling (int n, process p[]) {
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
            int ind = cur.pid - 1;
            p[ind].CT = cur_time + p[ind].BT;
            p[ind].TAT = p[ind].CT - p[ind].AT;
            p[ind].WT = p[ind].TAT - p[ind].BT;
            p[ind].RT = cur_time - p[ind].AT;
            cur_time = p[ind].CT;
            completed++;
        } else {
            cur_time++;
        }
    }
}

void print (int n, process p[]) {
    cout << "PID\t" << "priority\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << '\n';
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].priority << "\t\t" << p[i].AT << '\t' << p[i].BT << '\t' << p[i].CT << '\t' << p[i].TAT << '\t' << p[i].WT << '\t' << p[i].RT << '\n';
    }
}

int main () {
    int n;
    cin >> n;
    process p[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid;
        cin >> p[i].priority;
        cin >> p[i].AT;
        cin >> p[i].BT;
    }

    runPrioritySceduling (n, p);
    print (n, p);
}