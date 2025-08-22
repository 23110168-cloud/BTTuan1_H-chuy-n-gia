#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cmath>

using namespace std;

// Cấu trúc tiến trình
struct Process {
    int P;             // ID tiến trình
    int Arr;     // Thời gian đến
    int Burs;       // Thời gian thực thi
    int Remain;   // Thời gian còn lại
    int Com;  // Thời gian hoàn thành
    int Turn;  // Thời gian quay vòng (TAT = CT - AT)
    int Wait;     // Thời gian chờ (WT = TAT - BT)
};

// Cấu trúc Gantt Chart
struct GanttChart {
    int P;
    int startTime;
    int endTime;
};

void RR(vector<Process> &Pr, int n, int quantum) {
    queue<int> readyQueue;
    vector<GanttChart> ganttChart; 
    int currentTime = 0;
    int completedPr = 0;
    vector<bool> inQueue(n, false);

    for (int i = 0; i < n; i++) {
        if (Pr[i].Arr == 0) {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }

    while (completedPr < n) {
        if (!readyQueue.empty()) {
            int idx = readyQueue.front();
            readyQueue.pop();

            int startTime = currentTime;
            int executionTime = min(quantum, Pr[idx].Remain);
            Pr[idx].Remain -= executionTime;
            currentTime += executionTime;
            int endTime = currentTime;

            ganttChart.push_back({Pr[idx].P, startTime, endTime});

            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && Pr[i].Arr <= currentTime) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }

            if (Pr[idx].Remain == 0) {
                Pr[idx].Com = currentTime;
                Pr[idx].Turn = Pr[idx].Com - Pr[idx].Arr;
                Pr[idx].Wait = Pr[idx].Turn - Pr[idx].Burs;
                completedPr++;
            } else {
                readyQueue.push(idx);
            }
        } else {
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && Pr[i].Arr <= currentTime) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
        }
    }

    cout << "\nRound Robin Scheduling (Quantum = " << quantum << "):\n";
    cout << "P\tArrival\tBurs\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++) {
        cout << Pr[i].P << "\t"
             << Pr[i].Arr << "\t"
             << Pr[i].Burs << "\t"
             << Pr[i].Com << "\t\t"
             << Pr[i].Turn << "\t\t"
             << Pr[i].Wait << "\n";
    }

    cout << "\nGantt Chart:\n ";
    for (auto &entry : ganttChart) {
        cout << "------";
    }
    cout << "\n|";

    for (auto &entry : ganttChart) {
        cout << " P" << entry.P << " |";
    }
    cout << "\n ";

    for (auto &entry : ganttChart) {
        cout << "------";
    }
    cout << "\n";

    cout << ganttChart[0].startTime;
    for (auto &entry : ganttChart) {
        cout << setw(5) << entry.endTime;
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
    cout << "nhap so luong tien trinh: ";
    cin >> n;
    cout << "Nhap Quantum Time: ";
    cin >> quantum;

    vector<Process> Pr(n);

    cout << "Nhập thong tin tien trinh (Arrival Time, Burs Time):\n";
    for (int i = 0; i < n; i++) {
        Pr[i].P = i + 1;
        cout << "Tien trinh " << Pr[i].P << ":\n";
        cout << "Thoi gian den: ";
        cin >> Pr[i].Arr;
        cout << "Thoi gian thuc thi: ";
        cin >> Pr[i].Burs;
        Pr[i].Remain = Pr[i].Burs;
    }

    RR(Pr, n, quantum);

    return 0;
}
