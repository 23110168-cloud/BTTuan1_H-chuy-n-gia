#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <cmath>

using namespace std;

// Cấu trúc tiến trình
struct Process {
    int P;             // ID tiến trình
    int Arr;     // Thời gian đến
    int Burs;       // Thời gian thực thi ban đầu
    int Remain;   // Thời gian thực thi còn lại
    int Prio;        // Độ ưu tiên (Số nhỏ hơn có mức độ ưu tiên cao hơn)
    int Com;  // Thời gian hoàn thành
    int Turn;  // Thời gian quay vòng (TAT = CT - AT)
    int Wait;     // Thời gian chờ (WT = TAT - BT)
};

bool SortArr(Process a, Process b) {
    return a.Arr < b.Arr;
}

void Pri_Pre(vector<Process> &Pr, int n) {
    sort(Pr.begin(), Pr.end(), SortArr); 

    int currentTime = 0;
    int completedPr = 0;
    vector<tuple<int, int, int>> ganttChart; // Lưu (P, Start Time, End Time)
    int prevIdx = -1;

    while (completedPr < n) {
        int idx = -1;
        int highestPrio = INT_MAX;

        // Chọn tiến trình có độ ưu tiên cao nhất trong các tiến trình đã đến
        for (int i = 0; i < n; i++) {
            if (Pr[i].Arr <= currentTime && Pr[i].Remain > 0) {
                if (Pr[i].Prio < highestPrio) {
                    highestPrio = Pr[i].Prio;
                    idx = i;
                }
            }
        }

        if (idx == -1) { 
            currentTime++;
        } else {
            if (prevIdx != idx) {
                if (prevIdx != -1) {
                    get<2>(ganttChart.back()) = currentTime; 
                }
                ganttChart.push_back({Pr[idx].P, currentTime, 0}); 
            }

            Pr[idx].Remain--;
            currentTime++;
            prevIdx = idx;

            if (Pr[idx].Remain == 0) {
                Pr[idx].Com = currentTime;
                Pr[idx].Turn = Pr[idx].Com - Pr[idx].Arr;
                Pr[idx].Wait = Pr[idx].Turn - Pr[idx].Burs;
                completedPr++;
            }
        }
    }
    get<2>(ganttChart.back()) = currentTime;

    cout << "\nPrio Scheduling (Preemptive):\n";
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
        cout << "--------";
    }
    cout << "\n|";

    for (auto &entry : ganttChart) {
        cout << " P" << get<0>(entry) << " |";
    }
    cout << "\n ";

    for (auto &entry : ganttChart) {
        cout << "--------";
    }
    cout << "\n";

    cout << get<1>(ganttChart[0]); 
    for (auto &entry : ganttChart) {
        cout << setw(8) << get<2>(entry);
    }
    cout << "\n";
    double sum=0;
    for(int i=0;i<n;i++){
        sum+=Pr[i].Wait;
    }
    cout << "\nAverage Waiting Time: " <<  (double) round((sum / n)*100)/100 << " ms\n";
}

int main() {
    int n;
    cout << "nhap so luong tien trinh: ";
    cin >> n;

    vector<Process> Pr(n);

    cout << "nhap thong tin tien trinh (Arrival Time, Burst Time, Prio):\n";
    for (int i = 0; i < n; i++) {
        Pr[i].P = i + 1;
        cout << "tien trinh " << Pr[i].P << ":\n";
        cout << "thoi gian den: ";
        cin >> Pr[i].Arr;
        cout << "thoi gian thuc thi: ";
        cin >> Pr[i].Burs;
        cout << "muc do uu tien (so nho hon co uu tien cao hon): ";
        cin >> Pr[i].Prio;
        Pr[i].Remain = Pr[i].Burs;
    }

    // Gọi thuật toán Prio Scheduling (Preemptive)
    Pri_Pre(Pr, n);

    return 0;
}
