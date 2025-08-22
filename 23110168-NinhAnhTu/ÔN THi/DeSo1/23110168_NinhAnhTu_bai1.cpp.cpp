#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

struct sanpham{
	string maSP;
	string tenSP;
	float giaSP;
	int soLuong;
	int hang;
};

void docfile(const string &filename, vector<sanpham> &ds){
	ifstream file(filename);
	if(!file){
		cerr << "Erol"; return;
	}
	string line;
	while(getline(file,line)){
		stringstream ss(line);
		sanpham sp;
		getline(ss,sp.maSP,';');
		getline(ss,sp.tenSP,';');
		ss.ignore();
		float d;
		ss >> sp.giaSP;
		ss.ignore();
		ss >>sp.soLuong;
		ds.push_back(sp);
	}
	file.close();
}

void ghifile(const string &filename, vector<sanpham> &ds, vector<sanpham> &kq){
	ofstream file(filename);
		if(!file){
		cerr << "Erol"; return;
	}
	file << "Danh sach san pham: "<<endl;
	for(auto &d: ds){
		file << d.maSP <<";"<<d.tenSP<<";"<<d.giaSP<<";"<<d.soLuong<<";"<<d.hang<<endl;
	}
	file<<"San pham duoc tim: "<<endl;
	for(auto &d: kq){
		file << d.maSP <<";"<<d.tenSP<<";"<<d.giaSP<<";"<<d.soLuong<<";"<<d.hang<<endl;
	}
	file.close();
	}

void timkiem(string &s, vector<sanpham> &ds,vector<sanpham> &kq){
	bool timthay=false;
	sanpham sp;
	for(auto &d:ds){
	if(d.tenSP.find(s) != string::npos){
		cout<<"Tim thay";
		timthay=true;
		kq.push_back(d);
	}
}
if(!timthay){
	cout<<"Khong tim thay";
}
}

void xapxep(vector<sanpham> &ds){
	sort(ds.begin(),ds.end(),[](const sanpham &a, const sanpham &b){
		return a.giaSP>b.giaSP;
	});
}

void xephang(vector <sanpham> &ds){
	int hang=0;
	sanpham sp;
	ds[0].hang=1;
	for(int i=1;i<ds.size();i++){
		if(ds[i].giaSP>=ds[i-1].giaSP){
			ds[i].hang=i;
		}
		else{
			ds[i].hang=hang+1;
			hang=hang+1;
		}
	}
}


int main(){
	vector<sanpham> SP;
	vector<sanpham> KQ;
	docfile("SanPham.txt",SP);
	cout<<"Nhap ten san pham: ";
	string s;
	getline(cin, s);
	xapxep(SP);
	xephang(SP);
	timkiem(s,SP,KQ);
	ghifile("KetQua.txt",SP,KQ);
	return 0;
}