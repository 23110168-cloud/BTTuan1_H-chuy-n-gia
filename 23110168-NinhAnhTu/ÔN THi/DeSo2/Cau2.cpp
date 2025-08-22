#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std; 

void docfile(vector <int> &a, const string &filename){
    int luachon;
    cout<< "Nhap lua chon:\n1. Ban phim\n2. File\nChon: ";
    cin>>luachon;
    if(luachon==1){
        int n;
        cout<< "Nhap so luong phan tu: ";
        cin>> n;
        a.resize(n);
        cout<< "Nhap so phan tu: ";
        for(int i=0;i<n;i++){
            cin >> a[i];
        }
    }
    else{
        ifstream file(filename);
        if(!file){
            cerr<< "erol"; return;
        }
        int x;
        while( file >> x){
            a.push_back(x);

        }
        file.close();
    }
}

void timLIS(const vector<int> &a){
    int n= a.size();
    vector<int> L(n,1);//vector dãy kết thúc ở a[i];
    vector<int> trc(n,-1);//vector truy vấn;
    int Maxdodai=1;
    int vitri=0;
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            if(a[j]<a[i] && L[j]+1 >L[i]){
                L[i]=L[j]+1;
                trc[i]=j;
            }
        }
        if(L[i]>Maxdodai){
            Maxdodai=L[i];
            vitri=i;
        }
    }
    vector<int> lis;
    while(vitri!=-1){
        lis.push_back(a[vitri]);
        vitri=trc[vitri];
    }
    reverse(lis.begin(),lis.end());
    // In kết quả
    cout << "Do dai LIS: " << Maxdodai << endl;
    cout << "Day con: ";
    for (int x : lis) cout << x << " ";
    cout << endl;
}

int main(){
    vector<int> a;
    docfile(a,"inputCau2De2.txt");
    timLIS(a);
    return 0;
}