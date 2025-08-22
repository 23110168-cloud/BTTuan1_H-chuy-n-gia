#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

struct HocSinh {
    string maHS;
    string hoTen;
    vector<float> diem;
    float DTB;
    int xepHang;
};

// Chuyển chuỗi về chữ thường
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Đọc dữ liệu từ file diem.txt
void docFile(vector<HocSinh>& ds, const string& tenFile) {
    ifstream fin(tenFile);
    if (!fin) {
        cerr << "Khong mo duoc file " << tenFile << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        HocSinh hs;
        ss >> hs.maHS >> hs.hoTen;
        float d;
        while (ss >> d)
            hs.diem.push_back(d);
        ds.push_back(hs);
    }

    fin.close();
}

// Tính điểm trung bình
void tinhDTB(vector<HocSinh>& ds) {
    for (auto& hs : ds) { //duyệt các hs trong vector ds
        float tong = 0;
        for (float d : hs.diem)// duyệt các điểm trong hs.diem
            tong += d;
        hs.DTB = tong / hs.diem.size();
    }
}

// Tìm kiếm học sinh theo mã hoặc tên
void timKiem(const vector<HocSinh>& ds) {
    cout << "Nhap ma so hoac ten hoc sinh can tim: ";
    string tuKhoa;
    cin >> tuKhoa;
    tuKhoa = toLower(tuKhoa);

    bool timThay = false;
    for (const auto& hs : ds) {
        if (toLower(hs.maHS).find(tuKhoa) != string::npos ||
            toLower(hs.hoTen).find(tuKhoa) != string::npos) {
            cout << hs.maHS << "\t" << hs.hoTen << "\t" << fixed << setprecision(2) << hs.DTB << endl;
            timThay = true;
        }
    }

    if (!timThay)
        cout << "Khong tim thay hoc sinh phu hop.\n";
}

// Sắp xếp theo DTB giảm dần
bool soSanhDTB(const HocSinh& a, const HocSinh& b) {
    return a.DTB > b.DTB;
}

void sapXep(vector<HocSinh>& ds) {
    sort(ds.begin(), ds.end(), soSanhDTB);
}

// Xếp hạng học sinh
void xepHang(vector<HocSinh>& ds) {
    for (size_t i = 0; i < ds.size(); ++i) {
        ds[i].xepHang = i + 1;
    }
}

// Ghi kết quả ra file
void ghiFile(const vector<HocSinh>& ds, const string& tenFile) {
    ofstream fout(tenFile);
    fout << left << setw(8) << "MaHS" << setw(20) << "HoTen" 
         << setw(6) << "DTB" << "XepHang" << endl;
    for (const auto& hs : ds) {
        fout << left << setw(8) << hs.maHS 
             << setw(20) << hs.hoTen 
             << setw(6) << fixed << setprecision(2) << hs.DTB 
             << hs.xepHang << endl;
    }
    fout.close();
}

int main() {
    vector<HocSinh> ds;

    docFile(ds, "inputCau1.txt");
    tinhDTB(ds);
    sapXep(ds);
    xepHang(ds);
    ghiFile(ds, "ketqua.txt");

    // Tùy chọn: gọi tìm kiếm nếu muốn
    char chon;
    cout << "Ban co muon tim hoc sinh? (y/n): ";
    cin >> chon;
    if (chon == 'y' || chon == 'Y')
        timKiem(ds);

    cout << "Da ghi ket qua ra file ketqua.txt\n";
    return 0;
}
