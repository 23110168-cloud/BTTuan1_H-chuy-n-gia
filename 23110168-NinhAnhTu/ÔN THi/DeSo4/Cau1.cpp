/*Câu 1 (4 điểm) – Xử lý dữ liệu giá nhà từ tập tin
Mô tả:
•	File gia_nha.txt, mỗi dòng có định dạng:
<MaNha>;<KhuVuc>;<DienTich>;<GiaBan>
Ví dụ nội dung file gia_nha.txt:
N001;Q1;80;5200000
N002;Q2;90;4800000
N003;Q1;100;6000000
N004;Q3;85;4900000
Yêu cầu:
1.	Đọc dữ liệu từ file.
2.	Tìm kiếm theo khu vực (ví dụ nhập Q1).
3.	Sắp xếp giảm dần theo GiaBan.
4.	Xếp hạng theo giá bán.
5.	Ghi ra file ketqua_gianha.txt:
Ví dụ kết quả:
MaNha;KhuVuc;GiaBan;XepHang
N003;Q1;6000000;1
N001;Q1;5200000;2
N004;Q3;4900000;3
N002;Q2;4800000;4
Hướng dẫn cài đặt:
•	Dùng ifstream đọc file → tách dữ liệu bằng getline() với ';'.
•	Dùng struct để lưu thông tin từng căn nhà.
•	Tìm kiếm: lọc theo KhuVuc.
•	Sắp xếp: dùng std::sort() với comparator.
•	Ghi file: dùng ofstream.
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

struct gianha{
    string manha;
    string khuvuc;
    int dientich;
    string giaban;
    int xephang;
};

void docfile(const string &filename, vector<gianha> &ds){
    ifstream file(filename);
    if(!file){
        cerr << "erol"; return;
    }
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        gianha gh;
        getline(ss, gh.manha, ';');
        getline(ss,gh.khuvuc,';');
        ss >> gh.dientich;
        ss.ignore();
        getline(ss,gh.giaban);
        ds.push_back(gh);
}
    file.close();
}
void ghifile(const string &filename, vector<gianha> &ds){
    ofstream file(filename);
     if(!file){
        cerr << "erol"; return;
    }
    for(const auto &d:ds){
        file << d.manha <<";"<<d.khuvuc<<";"<<d.dientich<<";"<<d.giaban<<" "<<d.xephang<<endl;
    }
    file.close();
}

void timkiem(const string &a, vector<gianha> &ds){
    bool timthay=false;
    gianha d;
    for(const auto d:ds){
    if(d.khuvuc.find(a) != string ::npos){
        cout<< d.manha <<";"<<d.khuvuc<<";"<<d.dientich<<";"<<d.giaban<<" "<< d.xephang<<endl;
        timthay=true;
    }
    }
    if(!timthay){
        cout<<"Ko tim thay";
    }
}

int chuyenchuoi(string &ds)
{
    int x = stoi(ds);
    return x;
}
void xapxep(vector <gianha> &ds){
    sort(ds.begin(),ds.end(),[]( gianha &a, gianha &b){
        chuyenchuoi(a.giaban);
        chuyenchuoi(b.giaban);
      return  a.giaban>b.giaban;
    });
}

void xephang(vector<gianha> &ds){
    ds[0].xephang=1;
    int hang=1;
    for(int i=1;i<ds.size();i++){
        if(ds[i].giaban == ds[i-1].giaban){
            ds[i].xephang=i;
        }else{
            ds[i].xephang=hang+1;
            hang=hang+1;
        }
    }
}


int main(){
    vector<gianha> GH;
    string s;
    docfile("inputCau1De4.txt",GH);
    cout<<"nhap khu vuc can tim: ";
    getline(cin, s);
        xapxep(GH);
        xephang(GH);
    timkiem(s,GH);


    ghifile("outputCau1De4.txt",GH);
    return 0;
}