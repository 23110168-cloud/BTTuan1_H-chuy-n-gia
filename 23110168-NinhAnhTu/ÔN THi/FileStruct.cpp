#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct sinhvien
{
    string masv;    // mã sinh viên;
    string malop;   // mã lớp
    string hoten;   // họ tên sinh viên
    float diemki;   // điểm tổng kết kỳ 1
    float diemkii;  // điểm tổng kết kỳ 2
    float diemtk;   // điểm tổng kết cả năm
    int xeploai; // xếp loại
};
typedef sinhvien SinhVien;
SinhVien SV[100];
int n;

void xephang(int &n, SinhVien SV[]){
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n;j++){
            if(SV[i].diemtk<SV[j].diemtk)
            swap(SV[i],SV[j]);
        }
    }
}

// Tính thứ hạng (xếp loại) dựa trên điểmtk
void tinhhang(int n, SinhVien SV[]) {
    xephang(n, SV); // sắp xếp giảm dần điểm tổng kết

    int rank = 1;
    SV[0].xeploai = rank;
    for (int i = 1; i < n; ++i) {
        if (SV[i].diemtk == SV[i - 1].diemtk) {
            SV[i].xeploai = rank;
        } else {
            rank = i + 1;
            SV[i].xeploai = rank;
        }
    }
}


void docfile(int &n, const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Erol!";
        return;
    }
    file >> n;
    file.ignore(); // xóa kí tự thừa
    for (int i = 0; i < n; i++)
    {
        string line;
        getline(file, line);
        stringstream ss(line);
        getline(ss, SV[i].masv, ',');
        getline(ss, SV[i].malop, ',');
        getline(ss, SV[i].hoten, ',');
        ss >> SV[i].diemki;
        ss.ignore();
        ss >> SV[i].diemkii;
        ss.ignore();
        SV[i].diemtk = (SV[i].diemki + SV[i].diemkii) / 2;
    }
    file.close();
}


void ghifile(int &n, const string &filename)
{
    ofstream file(filename);
    if (!file)
    {
        cerr << "Erol";
        return;
    }
    file << n << "\n";
    tinhhang(n,SV);
    for (int i = 0; i < n; i++)
    {
        file << SV[i].masv << ", " << SV[i].malop << ", " << SV[i].hoten << ", "  << SV[i].diemki << ", "  << SV[i].diemkii << ", "  << SV[i].diemtk << ", "  << SV[i].xeploai << "\n";
    }
    file.close();
}

int main()
{
    docfile(n, "inputsinvien.txt");
    ghifile(n, "OutPutDaTaSV.txt");
    return 0;
}