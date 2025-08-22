#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

struct Process {
    int P;             // ID tiến trình
    int Arr;     // Thời gian đến
    int Burs;       // Thời gian thực thi ban đầu
    int remainingTime;   // Thời gian thực thi còn lại
    int Prio;        // Độ ưu tiên (Số nhỏ hơn có mức độ ưu tiên cao hơn)
    int Com;  // Thời gian hoàn thành
    int Turn;  // Thời gian quay vòng (TAT = CT - AT)
    int Wait;     // Thời gian chờ (WT = TAT - BT)
};

bool Sort_Prio(Process a, Process b) {
    return a.Prio < b.Prio;
}

void Pri_RR(vector<Process> &Pr, int n, int quantum) {
    sort(Pr.begin(), Pr.end(), Sort_Prio); // Sắp xếp theo độ ưu tiên

    queue<int> readyQueue;
    vector<tuple<int, int, int>> ganttChart; // (P, Start Time, End Time)
    int currentTime = 0;
    int completedPr = 0;
    vector<bool> inQueue(n, false);

    for (int i = 0; i < n; i++) {
        if (Pr[i].Arr <= currentTime) {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }

    while (completedPr < n) {
        if (readyQueue.empty()) { 
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (Pr[i].Arr <= currentTime) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        vector<int> tempQueue;
        while (!readyQueue.empty()) {
            tempQueue.push_back(readyQueue.front());
            readyQueue.pop();
        }

        sort(tempQueue.begin(), tempQueue.end(), [&](int a, int b) {
            return Pr[a].Prio < Pr[b].Prio;
        });

        for (int i : tempQueue) {
            readyQueue.push(i);
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        int execTime = min(quantum, Pr[idx].remainingTime);
        ganttChart.push_back({Pr[idx].P, currentTime, currentTime + execTime});

        Pr[idx].remainingTime -= execTime;
        currentTime += execTime;

        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && Pr[i].Arr <= currentTime) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        // Nếu tiến trình hoàn thành
        if (Pr[idx].remainingTime == 0) {
            Pr[idx].Com = currentTime;
            Pr[idx].Turn = Pr[idx].Com - Pr[idx].Arr;
            Pr[idx].Wait = Pr[idx].Turn - Pr[idx].Burs;
            completedPr++;
        } else {
            readyQueue.push(idx);
        }
    }

    cout << "\nPrio Scheduling with Round Robin:\n";
    cout << "P\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++) {
        cout << Pr[i].P << "\t"
             << Pr[i].Arr << "\t"
             << Pr[i].Burs << "\t"
             << Pr[i].Prio << "\t\t"
             << Pr[i].Com << "\t\t"
             << Pr[i].Turn << "\t\t"
             << Pr[i].Wait << "\n";
    }

    cout << "\nGantt Chart:\n ";
    for (auto &entry : ganttChart) {
        cout << "-------";
    }
    cout << "\n|";

    for (auto &entry : ganttChart) {
        cout << " P" << get<0>(entry) << " |";
    }
    cout << "\n ";

    for (auto &entry : ganttChart) {
        cout << "-------";
    }
    cout << "\n";

    cout << get<1>(ganttChart[0]);
    for (auto &entry : ganttChart) {
        cout << setw(5) << get<2>(entry);
    }
    cout << "\n";
    double sum=0;
    for(int i=0;i<n;i++){
        sum+=Pr[i].Wait;
    }
    cout << "\nAverage Waiting Time: " <<  (double) round((sum / n)*100)/100 << " ms\n";
}

int main() {
    int n, quantum;
    cout << "Nhap so luong tien trinh: ";
    cin >> n;
    cout << "Nhập quantum time: ";
    cin >> quantum;

    vector<Process> Pr(n);

    cout << "nhap thong tin tien trinh (Arrival Time, Burst Time, Prio):\n";
    for (int i = 0; i < n; i++) {
        Pr[i].P = i + 1;
        cout << "Tien trinh " << Pr[i].P << ":\n";
        cout << "Thoi gian den: ";
        cin >> Pr[i].Arr;
        cout << "Thoi gian thuc thi: ";
        cin >> Pr[i].Burs;
        cout << "muc uu tien(nho hon uu tien hon): ";
        cin >> Pr[i].Prio;
        Pr[i].remainingTime = Pr[i].Burs;
    }

    Pri_RR(Pr, n, quantum);

    return 0;
}
