#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Cấu trúc lưu thông tin học sinh
struct Student {
    string maHS;
    string hoTen;
    vector<int> diem;
    double dtb;
    int xepHang;
};

// Hàm chuyển chuỗi thành chữ thường
string toLowerCase(string s) {
    string res = s;
    transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

// Hàm đọc dữ liệu từ file diem.txt
void readFile(vector<Student>& students) {
    ifstream inFile("diem.txt");
    if (!inFile) {
        cout << "Khong mo duoc file diem.txt!" << endl;
        return;
    }

    string ma, ten;
    int d1, d2, d3, d4;
    while (inFile >> ma >> ten >> d1 >> d2 >> d3 >> d4) {
        Student s;
        s.maHS = ma;
        s.hoTen = ten;
        s.diem = {d1, d2, d3, d4};
        
        // Tính điểm trung bình
        s.dtb = (d1 + d2 + d3 + d4) / 4.0;
        students.push_back(s);
    }
    inFile.close();
}

// Hàm tìm kiếm học sinh theo mã hoặc tên
void searchStudent(const vector<Student>& students) {
    string query;
    cout << "Nhap ma HS hoac ten can tim: ";
    cin.ignore();
    getline(cin, query);
    query = toLowerCase(query);

    bool found = false;
    for (const auto& s : students) {
        if (toLowerCase(s.maHS).find(query) != string::npos || 
            toLowerCase(s.hoTen).find(query) != string::npos) {
            cout << "MaHS: " << s.maHS << ", HoTen: " << s.hoTen 
                 << ", DTB: " << fixed << setprecision(2) << s.dtb << endl;
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay hoc sinh!" << endl;
}

// Hàm sắp xếp học sinh theo điểm trung bình giảm dần
void sortStudents(vector<Student>& students) {
    sort(students.begin(), students.end(), 
         [](const Student& a, const Student& b) {
             return a.dtb > b.dtb;
         });
}

// Hàm xếp hạng học sinh
void rankStudents(vector<Student>& students) {
    for (size_t i = 0; i < students.size(); i++) {
        students[i].xepHang = i + 1;
    }
}

// Hàm ghi kết quả ra file ketqua.txt
void writeFile(const vector<Student>& students) {
    ofstream outFile("ketqua.txt");
    if (!outFile) {
        cout << "Khong mo duoc file ketqua.txt!" << endl;
        return;
    }

    outFile << left << setw(10) << "MaHS" 
            << setw(20) << "HoTen" 
            << setw(10) << "DTB" 
            << setw(10) << "XepHang" << endl;

    for (const auto& s : students) {
        outFile << left << setw(10) << s.maHS 
                << setw(20) << s.hoTen 
                << setw(10) << fixed << setprecision(2) << s.dtb 
                << setw(10) << s.xepHang << endl;
    }
    outFile.close();
}

int main() {
    vector<Student> students;

    // 1. Đọc dữ liệu từ file
    readFile(students);

    // 2. Tính điểm trung bình (đã tính trong readFile)

    // 3. Tìm kiếm học sinh
    searchStudent(students);

    // 4. Sắp xếp theo điểm trung bình
    sortStudents(students);

    // 5. Xếp hạng học sinh
    rankStudents(students);

    // 6. Ghi kết quả ra file
    writeFile(students);

    cout << "Da xu ly xong, ket qua duoc ghi vao ketqua.txt" << endl;
    return 0;
}