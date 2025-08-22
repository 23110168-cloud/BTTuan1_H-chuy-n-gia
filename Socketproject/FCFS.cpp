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
};

bool SortArr(Process a, Process b){
    return a.Arr<b.Arr;
}
void FCFS(Process pr[], int n){
    sort(pr, pr+n, SortArr);
    pr[0].Com=pr[0].Arr+pr[0].Bur;
    for(int i=1;i<n;i++){
        pr[i].Com=max(pr[i].Arr,pr[i-1].Com)+pr[i].Bur;
    }
    for(int i=0;i<n;i++){
        pr[i].Turn=pr[i].Com-pr[i].Arr;
        pr[i].Wait=pr[i].Turn-pr[i].Bur;
    }
    cout << "\nFCFS Scheduling:\n";
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++) {
        cout << pr[i].P << "\t"
             << pr[i].Arr << "\t"
             << pr[i].Bur << "\t"
             << pr[i].Com << "\t\t"
             << pr[i].Turn << "\t\t"
             << pr[i].Wait << "\n";
    }
    cout << "\nGantt Chart:\n";
    cout << " ";
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

int main(){
    cout << "Nhap so luong tien trinh: ";
    cin >> n;
    Process pr[n];
    cout << "nhap thong tin tien trinh (Arrival Time, Burst Time):\n";
    for (int i = 0; i < n; i++) {
        pr[i].P = i + 1;
        cout << "tien trinh: " << pr[i].P << ":\n";
        cout << "thoi gian den: ";
        cin >> pr[i].Arr;
        cout << "thoi gian thuc thi: ";
        cin >> pr[i].Bur;
    }
    FCFS(pr,n);
    return 0;
}