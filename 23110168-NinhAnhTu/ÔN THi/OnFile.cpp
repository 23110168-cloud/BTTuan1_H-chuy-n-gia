/*📝 Đề bài: Quản lý danh sách sinh viên
Yêu cầu:
Viết chương trình C hoặc C++ để quản lý danh sách sinh viên với các yêu cầu sau:

1. Cấu trúc dữ liệu
Định nghĩa một struct SinhVien gồm các thông tin:

Mã sinh viên (chuỗi ký tự)

Họ tên (chuỗi ký tự)

Giới tính (Nam/Nữ)

Điểm trung bình (số thực)

2. Đọc dữ liệu từ file
Đọc danh sách sinh viên từ file sinhvien.txt với định dạng mỗi dòng như sau:
MaSV;HoTen;GioiTinh;DiemTB

Ví dụ:
3
SV001;Nguyen Van A;Nam;7.8
SV002;Le Thi B;Nu;8.3
SV003;Tran Van C;Nam;6.5

In toàn bộ danh sách sinh viên ra màn hình.
Sắp xếp danh sách theo điểm trung bình giảm dần.
Ghi kết quả đã sắp xếp vào file output.txt.
*/

#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<fstream>
#include<algorithm>
#include<cstring>

/*
using namespace std;

struct SV{
    string MaSV;
    string HoTen;
    string GioiTinh;
    float Dtb;
};
typedef SV sv;
int n;
SV sinhvien[100];

void docfie(const string &filename, int &n){
    fstream file(filename);
    if(!file){
        cerr << "Eroll!";
        return;
    }
    file >> n;
    file.ignore();
    for(int i=0; i<n; i++){
        string line;
        getline(file,line);
        stringstream ss(line);
        getline(ss ,sinhvien[i].MaSV,';');
        getline(ss, sinhvien[i].HoTen,';');
        getline(ss,sinhvien[i].GioiTinh,';');
        ss >> sinhvien[i].Dtb;
        ss.ignore();
    }
}

void in(SV sinhvien[],int n){
    cout << "\nDanh sach sinh vien:\n";
    for (int i = 0; i < n; i++) {
        cout << sinhvien[i].MaSV << " - " << sinhvien[i].HoTen << " - " << sinhvien[i].GioiTinh << " - " << sinhvien[i].Dtb << endl;
    }
}


void xapxep(SV sinhvien[],int n){
    for(int i=0;i<n-1;i++){
       for(int j=1;j<n;j++){
        if(sinhvien[i].Dtb<sinhvien[j].Dtb){
            swap(sinhvien[i],sinhvien[j]);
        }
       }
    }
}
void ghifile(const string &filename,int &n){
    ofstream file(filename);
    if (!file){
        cerr<<"Eroll!";
        return;
    }
    file << n << "\n";
    for(int i=0;i<n;i++){
        file << sinhvien[i].MaSV<<" - "
        <<sinhvien[i].HoTen<<" - "
        <<sinhvien[i].GioiTinh<< " - "
        <<sinhvien[i].Dtb<<"\n";
    }
    file.close();
}


    

int main(){
    docfie("sinhvien.txt",n);
    in(sinhvien,n);
    xapxep(sinhvien,n);
    ghifile("OutputSinhVien.txt",n);
    return 0;
}*/
/*BÀI 1:(FILE-STRUCT-ARRAY-SORTING)
Viết chương trình quản lý điểm thi của sinh viên, thông tin về mỗi sinh viên được định nghĩa thông
qua cấu trúc sau:
struct sinhvien{
string masv; // mã sinh viên;
string malop; //mã lớp
string hoten; //họ tên sinh viên
float diemki; // điểm tổng kết kỳ 1
float diemkii;// điểm tổng kết kỳ 2
float diemtk; // điểm tổng kết cả năm
string xeploai; // xếp loại
};
typedef sinhvien SinhVien;
Dữ liệu danh sách sinh viên gồm một số sinh viên được lưu sẵn trong tập tin DataSV.txt
Dòng thứ 1 chứa số nguyên là số sinh viên sẽ được đọc vào biến nguyên n.
Từ dòng thứ 2 đến dòng thứ n+1 là mẫu tin sinh viên theo cấu trúc
sinhvien(masv,malop,hoten,diemki,diemkii) sẽ được đọc vào mảng(hay vector) n phần tử với các
phần tử có kiểu dữ liệu sinhvien.
Thuộc tính diemtk=(diemki+diemkii)/2 được tính khi có hai giá trị diemki và diemkii đọc từ file
(cho giá trị của điểm trong file luôn hợp lệ với giá trị từ 0-10).
Thuộc tính xeploai sẽ dựa theo diemtk vừa tính với các xếp loại như sau:
Nếu diemtk>=0 và diemtk<5: xeploai=YEU
Nếu diemtk>=5 và diemtk<6.5: xeploai=TB
Nếu diemtk>=6.5 và diemtk<9: xeploai=KHA
Nếu diemtk>=9 và diemtk<=10: xeploai=GIOI
*/

using namespace std;

struct sinhvien{
    string masv; // mã sinh viên;
    string malop; //mã lớp
    string hoten; //họ tên sinh viên
    float diemki; // điểm tổng kết kỳ 1
    float diemkii;// điểm tổng kết kỳ 2
    float diemtk; // điểm tổng kết cả năm
    string xeploai; // xếp loại
    };
    typedef sinhvien SinhVien;
    int n;
    SinhVien sv[100];

void docfile(const string &filename, int &n){
    ifstream file(filename);
    if(!file){
        cerr << "Eroll!";
        return;
    }
    file >> n;
    file.ignore();
    for(int i=0; i<n;i++){
        string line;
        getline(file, line);
        stringstream ss(line);
        getline(ss,sv[i].masv, ',');
        getline(ss,sv[i].malop, ',');
        getline(ss,sv[i].hoten, ',');
        ss >> sv[i].diemki;
        ss.ignore();
        ss >> sv[i].diemkii;
        ss.ignore();
        sv[i].diemtk = (sv[i].diemki + sv[i].diemkii)/2;
        if(sv[i].diemtk >= 9 && sv[i].diemtk <=10){
            sv[i].xeploai = "Gioi";
        } else if(sv[i].diemtk >= 6.5 && sv[i].diemtk <9){
            sv[i].xeploai = "Kha";
        }else if(sv[i].diemtk >= 5 && sv[i].diemtk <6.5){
            sv[i].xeploai = "Trung binh";
        }else{
            sv[i].xeploai = "Yeu";
        }
    }
    file.close();
}

void xapxep(SinhVien sv[], int &n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(sv[i].diemtk<sv[j].diemtk){
                swap(sv[i],sv[j]);
            }
        }
    }
}

void ghifile(const string &filename, int &n){
    ofstream file(filename);
    if(!file){
        cerr<< "Errol!";
        return;
        
    }
    xapxep(sv,n);
    file <<n<<"\n";
    for (int i=0; i<n;i++){
        file << sv[i].masv << ", "<<sv[i].malop<< ", "<<sv[i].hoten<< ", "<<sv[i].diemki<< ", "<<sv[i].diemkii<< ", "<<sv[i].diemtk<< ", "<<sv[i].xeploai<<"\n";
    }
}

int main(){
    docfile("inputsinvien.txt",n);
    ghifile("OutPutDaTaSV.txt",n);
    return 0;
}