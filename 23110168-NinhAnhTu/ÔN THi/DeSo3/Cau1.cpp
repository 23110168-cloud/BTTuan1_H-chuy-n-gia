#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
using namespace std;

struct sanpham{
    string masp;
    string tensp;
    float dongia;
    float soluong;
    float thanhtien;
};

void docfile(const string &filename, vector<sanpham> &ds, float &tong){
    ifstream file(filename);
    if(!file){
        cerr<<"Erol"; return;
    }
    string line;
    sanpham sp;
    while(getline(file,line)){
        stringstream ss(line);
        getline(ss,sp.masp,' ');
        getline(ss,sp.tensp,' ');
        ss >> sp.dongia;
        ss.ignore();
        ss >> sp.soluong;
        sp.thanhtien = sp.dongia*sp.soluong;
        tong+=sp.thanhtien;
        ds.push_back(sp);
    }
    cout << "Danh sach da doc tu file: \n";
    for(const auto &d:ds){
        cout << d.masp<<" "<<d.tensp<<" "<<d.dongia<<" "<<d.soluong<<" "<<d.thanhtien<<"\n";
    }
    file.close();
}


void ghifile(const string &filename, vector<sanpham> &ds,float &tong){
    ofstream file(filename);
    if(!file){
        cerr<<"Erol"; return;
    }
    for(const auto &d : ds){
        file << d.masp<<" "<<d.tensp<<" "<<d.dongia<<" "<<d.soluong<<" "<<d.thanhtien<<"\n";
    }
    file <<"Tong so tien SP: "<<tong<<"\n";
    file <<"SP co thanh tien cao nhat: "<<"\n";
    sanpham s=ds.back();
        file << s.masp<<" "<<s.tensp<<" "<<s.dongia<<" "<<s.soluong<<" "<<s.thanhtien<<endl;
    file.close();
}
void xapxep(vector<sanpham>&a){
    sort(a.begin(),a.end(),[](const sanpham &b, const sanpham &c){
        return b.thanhtien<c.thanhtien;
    });
}
 sanpham sps1(vector<sanpham> &ds){
        xapxep(ds);
        sanpham s=ds.back();// lấy giá trị cuối trong vector
        cout << s.masp<<" "<<s.tensp<<" "<<s.dongia<<" "<<s.soluong<<" "<<s.thanhtien<<endl;
        return s;
 }
int main(){
    vector<sanpham> SP;
    float tong=0;
    docfile("inputCau1De3.txt",SP,tong);
    cout <<"Tong so tien sp: "<<tong<<"\n";
    cout << "SP co thanh tien cao nhat: ";
    sps1(SP);
    ghifile("outputCau1De3.txt",SP,tong);
    return 0;
}