#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <cmath>

using namespace std;

// Cấu trúc tiến trình
struct Process {
    int P;          //Số thứ tự tiến trình            
    int Arr;        //Thời gian đến           
    int Burs;       //Thời gian thực thi          
    int Remain;     //Thời gian còn lại để thực hiệc tiến trình     
    int Com;        //Thời gian hoàn thành    
    int Turn;       //Thời gian quay vòng    
    int Wait;       //Thời gian chờ       
    bool InCom;     //Đánh dấu tiến trình hoàn thành       
};

struct GanttChart {
    int P;       // Tiến trình chạy
    int startTime; // Thời gian bắt đầu
    int endTime;   // Thời gian kết thúc
};

bool SortArr(Process a, Process b) {
    return a.Arr < b.Arr;
}

void SJF_Pree(vector<Process> &Pr, int n) {
    sort(Pr.begin(), Pr.end(), SortArr);

    int currentTime = 0, InComPr = 0;
    int prevIdx = -1; 
    vector<GanttChart> ganttChart; 

    while (InComPr < n) {
        int idx = -1;
        int minRemain = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!Pr[i].InCom && Pr[i].Arr <= currentTime) {
                if (Pr[i].Remain < minRemain) {
                    minRemain = Pr[i].Remain;
                    idx = i;
                }
            }
        }

        if (idx == -1) { 
            currentTime++;
        } else {
            if (prevIdx != idx) {
                if (prevIdx != -1) {
                    ganttChart.back().endTime = currentTime;
                }
                ganttChart.push_back({Pr[idx].P, currentTime, 0});
                prevIdx = idx;
            }

            Pr[idx].Remain--;
            currentTime++;

            if (Pr[idx].Remain == 0) {
                Pr[idx].Com = currentTime;
                Pr[idx].Turn = Pr[idx].Com - Pr[idx].Arr;
                Pr[idx].Wait = Pr[idx].Turn - Pr[idx].Burs;
                Pr[idx].InCom = true;
                InComPr++;
                ganttChart.back().endTime = currentTime; 
            }
        }
    }

    cout << "\nSJF Preemptive Scheduling:\n";
    cout << "P\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
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
    int n;
    cout << "Nhap so luong tien trinh: ";
    cin >> n;

    vector<Process> Pr(n);

    cout << "Nhap thong tin tien trinh (Arrival Time, Burst Time):\n";
    for (int i = 0; i < n; i++) {
        Pr[i].P = i + 1;
        Pr[i].InCom = false;
        cout << "Tien trinh " << Pr[i].P << ":\n";
        cout << "Thoi gian den: ";
        cin >> Pr[i].Arr;
        cout << "Thoi gian thuc thi: ";
        cin >> Pr[i].Burs;
        Pr[i].Remain = Pr[i].Burs;
    }

    SJF_Pree(Pr, n);

    return 0;
}
