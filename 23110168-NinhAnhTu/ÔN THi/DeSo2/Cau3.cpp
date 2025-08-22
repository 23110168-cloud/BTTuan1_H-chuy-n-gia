//docfile
//chon tong loi nhuan lon nhat- kiem tra tg ko vượt
//ghifile

#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

struct congviec{
    string MaCv;
    int Tg;
    int LoiNhuan;
    float hieusuat;
};

// Xắp xếp công việc theo tg
bool kiemtra(const congviec &a, const congviec &b){
    return a.hieusuat<b.hieusuat;
}
void xapxep(vector<congviec> &cv){
    sort(cv.begin(),cv.end(),kiemtra);
}

void docfile(const string &filename, int &n, int &T, vector<congviec> &cv){
    ifstream file(filename);
    if(!file){
        cerr<<"Erol"; return;
    }
    file >> n;
    file.ignore();
    file >> T;
    file.ignore();
    for(int i=0;i<n;i++){
         congviec ds;
        file >> ds.MaCv >>ds.Tg >>ds.LoiNhuan;
        ds.hieusuat=(float)ds.LoiNhuan/ds.Tg;   
        cv.push_back(ds);
    }
    file.close();
}

// Chon cong viec
void choncongviec(vector<congviec> &ds, int &n, int &T, vector<string> &dcchon, int &tongloinhuan){
    int tongthoigian=0;
    xapxep(ds);
    for(const auto &cv:ds){
        if(tongthoigian+cv.Tg<=T && tongloinhuan+cv.LoiNhuan>tongloinhuan){
            tongthoigian+=cv.Tg;
            tongloinhuan+=cv.LoiNhuan;
            dcchon.push_back(cv.MaCv);
        }
    }
}

void ghifile(const string &filename,vector<string> &dcchon,int tongloinhuan){
    ofstream file(filename);
    if(!file){
        cerr<<"Erol"; return;
    }
    file << "Chon cong viec: ";
    for(size_t i=0; i<dcchon.size();i++){
        file<<dcchon[i]<<" ";
    }
    file << "\nTong loi nhuan: "<<tongloinhuan<<endl;
    file.close();
}


int main(){
    int n,T;
    vector<string> dcchon;
    vector<congviec> CV;
    int tongloinhuan=0;
    docfile("inputCau3De2.txt",n,T,CV);
    choncongviec(CV,n,T,dcchon,tongloinhuan);
    ghifile("outputCau3De2.txt",dcchon,tongloinhuan);
    return 0;
}
// bài toán phòng thi
