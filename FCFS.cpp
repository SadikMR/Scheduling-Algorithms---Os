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
    if (a.AT != b.AT) {
        return a.AT < b.AT;
    } else {
        return a.pid < b.pid;
    }
}

void runFCFS (int n, process p[]) {
    int pTime = 0;
    for (int i = 0; i < n; i++) {
        pTime = max (pTime, p[i].AT);
        p[i].CT = pTime + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        p[i].RT = pTime - p[i].AT;
        pTime = p[i].CT;
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

    sort (p, p + n, compare);
    runFCFS (n, p);
    print (n, p);
}