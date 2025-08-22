#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include<cmath>

using namespace std;

// Cấu trúc tiến trình
struct Process {
    int P;             // ID tiến trình
    int Arr;     // Thời gian đến
    int Burs;       // Thời gian thực thi
    int Prio;        // Độ ưu tiên (Số nhỏ hơn có mức độ ưu tiên cao hơn)
    int Com;  // Thời gian hoàn thành
    int Turn;  // Thời gian quay vòng (TAT = CT - AT)
    int Wait;     // Thời gian chờ (WT = TAT - BT)
};

// Hàm sắp xếp tiến trình theo Arrival Time
bool SortArr(Process a, Process b) {
    return a.Arr < b.Arr;
}

// Hàm thực hiện thuật toán Prio Scheduling (Non-Preemptive)
void Pri_Non(vector<Process> &Pr, int n) {
    sort(Pr.begin(), Pr.end(), SortArr); 
    int currentTime = 0;
    int completedPr = 0;
    vector<tuple<int, int, int>> ganttChart; // Lưu (P, Start Time, End Time)
  
    while (completedPr < n) {
        int idx = -1;
        int highestPrio = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (Pr[i].Arr <= currentTime && Pr[i].Com == 0) {
                if (Pr[i].Prio < highestPrio) {
                    highestPrio = Pr[i].Prio;
                    idx = i;
                }
            }
        }

        if (idx == -1) { 
            currentTime++;
        } else {
            int startTime = currentTime;
            currentTime += Pr[idx].Burs;
            ganttChart.push_back({Pr[idx].P, startTime, currentTime});

            Pr[idx].Com = currentTime;
            Pr[idx].Turn = Pr[idx].Com - Pr[idx].Arr;
            Pr[idx].Wait = Pr[idx].Turn - Pr[idx].Burs;
            completedPr++;
        }
    }

    // In kết quả
    cout << "\nPrio Scheduling (Non-Preemptive):\n";
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

    // In biểu đồ Gantt
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

    cout << get<1>(ganttChart[0]); // In thời gian bắt đầu của tiến trình đầu tiên
    for (auto &entry : ganttChart) {
        cout << setw(5) << get<2>(entry); // In thời gian kết thúc của từng tiến trình
    }
    cout << "\n";
    double sum=0;
    for(int i=0;i<n;i++){
        sum+=Pr[i].Wait;
    }
    cout << "\nAverage Waiting Time: " <<  (double) round((sum / n)*100)/100 << " ms\n";
}

// Hàm chính
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
        cout << "muc uu tien (nho hon uu tien hon): ";
        cin >> Pr[i].Prio;
    }

    // Gọi thuật toán Prio Scheduling
    Pri_Non(Pr, n);

    return 0;
}
