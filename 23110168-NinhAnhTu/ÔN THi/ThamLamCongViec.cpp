#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<iomanip>
#include<sstream>
#include<vector>

using namespace std;

const int N=4;


void docfile(const string &filename, int a[][100], int n){
    ifstream file(filename);
    if(!file){
        cerr<<"erol"; return;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            file>>a[i][j];
        }
    }
    file.close();
}

 int xuly(int n, int b[][100], int socot){
        int kq=INT_MAX;
        bool danhdau[4] ={false,false,false,false};
        for(int i=0;i<n;i++){
            if(b[i][socot]<kq && danhdau[i]==false){
                kq=b[i][socot];
            }
        }
        for(int i=0;i<n;i++){
            if(kq==b[i][socot]){
                danhdau[i]=true;
            }
        }
        return kq;
    }

    int congnhan(int &n, int a[][100], int socot, int kq){
        int danhdau=0;
        for(int i=0;i<n;i++){
            if(a[i][socot]==kq){
                danhdau=i;
            }
        }
        return danhdau;
    }

void ghifile(const string &filename, int a[][100],int n){
    ofstream file(filename);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            file<<a[i][j]<<" ";
        }
        file<<"\n";
    }
    file<<"Phan cong cong viec: "<<"\n";

   int kqc=0;
   int danhdau=0;
   int kqcc=0;
    for(int i=0;i<n;i++){
       kqc=xuly(n,a,i);
       kqcc+=kqc;
        danhdau=congnhan(n,a,i,kqc);
        file<<"Cong viec "<<i+1<<" duoc cong nhan "<<danhdau+1<<" nhan voi thoi gian "<<kqc<<"\n";
    }
    file<< "Tong thoi gian: "<<kqcc;
    file.close();
}

int main(){
    int a[100][100];
    int kq[100][100];
    docfile("inputCongViec.txt",a,N);
    ghifile("outputCongViec.txt",a,N);
    return 0;
}