#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct sinhvien
{
    string masv;
    string malop;
    string hoten;
    float diemki;
    float diemkii;
    float diemtk;
    string xeploai;
    int xephang;
};
typedef sinhvien SinhVien;

sinhvien ds_SV[100];
int n;
void docfile(const string &filename, int &n)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Erol!";
        return;
    }
    file >> n;
    file.ignore();
    for (int i = 0; i < n; i++)
    {
        string line;
        getline(file, line);
        stringstream ss(line);
        getline(ss, ds_SV[i].masv, ',');
        getline(ss, ds_SV[i].malop, ',');
        getline(ss, ds_SV[i].hoten, ',');
        ss >> ds_SV[i].diemki;
        ss.ignore();
        ss >> ds_SV[i].diemkii;
        ds_SV[i].diemtk = (ds_SV[i].diemki + ds_SV[i].diemkii) / 2;
        if (ds_SV[i].diemtk >= 8.5)
            ds_SV[i].xeploai = "Gioi";
        else if (ds_SV[i].diemtk >= 7.0)
            ds_SV[i].xeploai = "Kha";
        else if (ds_SV[i].diemtk >= 5.0)
            ds_SV[i].xeploai = "Trung binh";
        else
            ds_SV[i].xeploai = "Yeu";
    }
    file.close();
}

void tinhXepHang(int n)
{
    ds_SV[0].xephang = 1;
    int rank = 1;
    for (int i = 1; i < n; i++)
    {
        if (ds_SV[i].diemtk == ds_SV[i - 1].diemtk)
        {
            ds_SV[i].xephang = rank;
        }
        else
        {
            rank = i + 1 - (i - rank);
            ds_SV[i].xephang = rank;
        }
    }
}

void ghiFile(const string &filename, int n)
{
    ofstream file(filename);
    if (!file)
    {
        cerr << "Erol!\n";
        return;
    }

    file << n << "\n";

    for (int i = 0; i < n; i++)
    {
        file << ds_SV[i].masv << ","
             << ds_SV[i].malop << ","
             << ds_SV[i].hoten << ","
             << ds_SV[i].diemki << ","
             << ds_SV[i].diemkii << ","
             << ds_SV[i].diemtk << ","
             << ds_SV[i].xeploai << ","
             << ds_SV[i].xephang << "\n";
    }

    file.close();
}

int main()
{
    docfile("DataSV.txt", n);

    sort(ds_SV, ds_SV + n, [](SinhVien a, SinhVien b)
         { return a.diemtk > b.diemtk; });
    tinhXepHang(n);
    ghiFile("DataSV_OUT.txt", n);

    return 0;
}