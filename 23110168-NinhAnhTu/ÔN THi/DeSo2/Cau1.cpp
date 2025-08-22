#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<string>
#include<sstream> 

using namespace std;

struct dbdt{
    string MaNg;
    string HoTen;
    string SDT;
    string Email;
};

// ham chuyen hoa thanh thuong
string toLower(string str){
    transform(str.begin(),str.end(),str.begin(), ::tolower);
    return str;
}

// ham tim kiem
void timkiem(const vector<dbdt> &ds,vector<dbdt> &kq){
    string tukhoa;
    cout<<"Nhap tu khoa hoac sdt can tim: ";
    cin.ignore();
    getline(cin,tukhoa);
    tukhoa=toLower(tukhoa);

    bool timthay=false;
    dbdt tt;
    for( auto &db : ds){
        if(toLower(db.HoTen).find(tukhoa) != string::npos ||
    db.SDT.find(tukhoa) != string :: npos){
        cout<<db.MaNg<<" "<<db.HoTen<<" "<<db.SDT<<" "<<db.Email<<endl;
        timthay=true;
        kq.push_back(db);
    }
    }
    if(!timthay){
        cout<<"Khong tim thay";
    }
}

// ham xap xep 
void xapxep(vector<dbdt> &ds){
    sort(ds.begin(),ds.end(),[](const dbdt &a , const dbdt &b){
        if(a.HoTen==b.HoTen){
            return a.HoTen<b.HoTen;
            return a.SDT<b.SDT;
        }
    }
);
}

void docfile(const string &filename, vector<dbdt> &ds){
    ifstream file(filename);
    if(!file){
        cerr<<"erol"; return;
    }
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        dbdt danhba;
        getline(ss,danhba.MaNg,' ');
        getline(ss,danhba.HoTen,' ');
        getline(ss,danhba.SDT,' ');
        getline(ss,danhba.Email);
        ds.push_back(danhba);
        
    }
    file.close();
}

void ghifile(const string &filename, vector<dbdt>&ds ){
    ofstream file(filename);
    if(!file){
        cerr<<"erol"; return;
    }
    for(const auto & d: ds){
        file << d.MaNg << " "<<d.HoTen<<" "<<d.SDT<<" "<<d.Email<<"\n";
    }
    cout<<"Da ghi vao file";
    file.close();
}

int main(){
    vector<dbdt> danhba;
    vector<dbdt> kq;
    docfile("inputCau1De2.txt",danhba);
    timkiem(danhba,kq);
    xapxep(kq);
    ghifile("outputCau1De2.txt",kq);
    return 0;
}