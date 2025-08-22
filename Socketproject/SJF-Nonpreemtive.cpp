#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

int n;
struct Process{
    int P;          //Số thứ tự tiến trình
    int Arr;        //Thời gian đến
    int Bur;        //Thời gian thực thi
    int Com;        //Thời gian hoàn thành
    int Turn;       //Thời gian quay vòng
    int Wait;       //Thời gian chờ
    bool InCom;     //Đánh dấu tiến trình hoàn thành
};

bool SortArr(Process a, Process b){
    return a.Arr<b.Arr;
}

void SJF_Non(Process pr[], int n){
    sort(pr, pr + n, SortArr);

    int Curr = 0, ComP = 0;// tg hiện tại và tg hoàn thành
    
    while (ComP < n) {
        int idx = -1;
        int minBur = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!pr[i].InCom && pr[i].Arr <= Curr) {
                if (pr[i].Bur < minBur) {
                    minBur = pr[i].Bur;
                    idx = i;
                }
            }
        }
        if (idx == -1) { 
            Curr++;
        } else {
            pr[idx].Com = Curr + pr[idx].Bur;
            pr[idx].Turn = pr[idx].Com - pr[idx].Arr;
            pr[idx].Wait = pr[idx].Turn - pr[idx].Bur;
            pr[idx].InCom = true;

            Curr = pr[idx].Com;
            ComP++;
        }
    }
    cout << "\nSJF (Non-preemptive) Scheduling:\n";
    cout << "P\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++) {
        cout << pr[i].P << "\t"
             << pr[i].Arr << "\t"
             << pr[i].Bur << "\t"
             << pr[i].Com << "\t\t"
             << pr[i].Turn << "\t\t"
             << pr[i].Wait << "\n";
    }
    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < n; i++) {
        cout << "------";
    }
    cout << "\n|";
    for (int i = 0; i < n; i++) {
        cout << " P" << pr[i].P << " |";
    }
    cout << "\n ";
    for (int i = 0; i < n; i++) {
        cout << "------";
    }
    cout << "\n";
    cout << "0";
    for (int i = 0; i < n; i++) {
        cout << setw(5) << pr[i].Com;
    }
    cout << "\n";
    double sum=0;
    for(int i=0;i<n;i++){
        sum+=pr[i].Wait;
    }
    cout << "\nAverage Waiting Time: " <<  (double) round((sum / n)*100)/100 << " ms\n";
}

int main() {
    int n;
    cout << "Nhap so luong tien trinh: ";
    cin >> n;

    Process pr[n];

    cout << "Nhap thong tin tien trinh (Arrival Time, Burst Time):\n";
    for (int i = 0; i < n; i++) {
        pr[i].P = i + 1;
        pr[i].InCom = false;
        cout << "Tien trinh " << pr[i].P << ":\n";
        cout << "Thoi gian den: ";
        cin >> pr[i].Arr;
        cout << "Thoi gian thuc thi: ";
        cin >> pr[i].Bur;
    }
    SJF_Non(pr, n);
    return 0;
}
