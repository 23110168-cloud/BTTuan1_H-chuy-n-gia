#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<iomanip>

using namespace std;

struct khosach{
    string masach;
    string theloai;
    float gia;
    string tensach;
};
typedef khosach KhoSach;
vector<KhoSach> Sach;

struct ketqua {
    string masach;
    string theloai;
    float gia;
    int xephang;
};

void docfile(const string &filename, vector<KhoSach> &Sach){
    ifstream file(filename);
    if(!file){
        cerr << "Erol";
        return;
    }
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        string giatamthoi;
        KhoSach s;
        getline(ss,s.masach,';');
        getline(ss,s.theloai,';');
        getline(ss,giatamthoi,';');
        getline(ss,s.tensach);
        s.gia=stof(giatamthoi);
        Sach.push_back(s);
    }
    file.close();
}

vector<ketqua> xuly(const string &loai, vector<KhoSach> &Sach){
    vector<ketqua> ds;

    // Lọc sách theo thể loại
    for(auto &s : Sach){
        if(s.theloai == loai){
            ds.push_back({s.masach, s.theloai, s.gia, 0});
        }
    }

    // Sắp xếp giảm dần theo giá
    sort(ds.begin(), ds.end(), [](ketqua a, ketqua b){
        return a.gia > b.gia;
    });

    // Tính xếp hạng
    int hang = 1;
    ds[0].xephang = hang;
    for(int i = 1; i < ds.size(); ++i){
        if(ds[i].gia == ds[i-1].gia){
            ds[i].xephang = hang;
        } else {
            hang = i + 1;
            ds[i].xephang = hang;
        }
    }
    return ds;
}

void ghifile(const string& filename, const vector<ketqua>& ds){
    ofstream file(filename);
    if(!file){
        cerr << "Erol ghi file!";
        return;
    }
    file << "MaSach;TheLoai;Gia;XepHang\n";
    for(auto &s : ds){
        file << s.masach << ";" << s.theloai << ";" << fixed << setprecision(2) << s.gia << ";" << s.xephang << "\n";
    }
    file.close();
}

int main(){
    string loai;
    docfile("khosach.txt", Sach);
    cout << "Nhap the loai can tim: ";
    getline(cin, loai);
    vector<ketqua> ketquaTim = xuly(loai, Sach);
    ghifile("ketqua_sach.txt", ketquaTim);
    cout << "Da ghi ket qua vao file ketqua_sach.txt" << endl;
    return 0;
}
