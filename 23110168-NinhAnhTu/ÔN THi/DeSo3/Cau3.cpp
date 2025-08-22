#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
using namespace std;

struct sukien{
    int start, end, importance;
};

void docfile(const string &filename, vector<sukien> &ds, int &n){
    ifstream file(filename);
    if(!file){
        cerr<<"Erol"; return;
    }
    file >>n;
    file.ignore();
    sukien sk;
    for(int i=0;i<n;i++){
        file >> sk.start >>sk.end>>sk.importance;
        ds.push_back(sk);
    }
    file.close();
}

void xapxep(vector<sukien>&ds){
    sort(ds.begin(),ds.end(),[](const sukien &a, const sukien &b){
        return a.end<b.end;
    });
}

int main(){
    vector<sukien> SK;
    vector<sukien> kq;
    int n;
    docfile("inputCau3De3.txt",SK,n);
    xapxep(SK);
    int sumimprotance=SK[0].importance;
    kq.push_back(SK[0]);
    int sktam=0;
    for(int i=1;i<n;i++){
            if(SK[i+1].start>SK[i].end){
                sumimprotance+=SK[i].importance;
                kq.push_back(SK[i]);
            }
    }
    cout<<"Chon cac su kien: ";
    for(const auto &d:kq){
        cout<<"("<<d.start<<","<<d.end<<")"<<" ";
    }
    cout<<endl;
    cout<<"Tong muc do quan trong: "<<sumimprotance;
    return 0;
}