//23110168 Ninh Anh Tú
// Bài tập tuần 1: Xây dựng hệ chuyên gia tư vấn ngủ hay bấm điện thoại
#include <iostream>
#include <string>
using namespace std;

int main() {
    int gio;
    string suckhoe, congviec, dienthoai, tranbong, thoigian;

    cout << "He chuyen gia: Tu van Ngu hay Bam dien thoai\n";

    cout << "Nhap gio hien tai (0-23): ";
    cin >> gio;

    if (gio <= 22) thoigian = "som";
    else thoigian = "tre";
    cout << "Suc khoe (met/khoe): ";
    cin >> suckhoe;

    cout << "Sang mai co cong viec khong (co/khong): ";
    cin >> congviec;

    cout << "Pin dien thoai (het/chuahet): ";
    cin >> dienthoai;

    cout << "Tran bong da (co/khong): ";
    cin >> tranbong;

    cout << "\n==> Tu van: ";

    if (suckhoe == "met") {
        if (thoigian == "som" && dienthoai == "chuahet" && tranbong == "co" && congviec == "co") {
            cout << "Ban co the bam dien thoai mot chut roi ngu sau.\n";
        } else if (thoigian == "som" && dienthoai == "chuahet" && tranbong == "co" && congviec == "khong") {
            cout << "Ban co the bam dien thoai mot chut roi ngu sau.\n";
        } else if (thoigian == "som" && dienthoai == "chuahet" && tranbong == "co") {
            cout << "Ban co the bam dien thoai mot chut roi ngu sau.\n";
        } else {
            cout << "Ban nen di ngu ngay de nghi ngoi.\n";
        }
    } 
    else if (suckhoe == "khoe") {
        if (thoigian == "tre" && congviec == "co") {
            cout << "Ban nen di ngu de mai sang tinh tao.\n";
        } else if (dienthoai == "het") {
            cout << "Pin het roi, hay di ngu thay vi bam dien thoai.\n";
        } else if (thoigian == "tre" && dienthoai == "chuahet" && tranbong == "co" && congviec == "khong") {
            cout << "Ban co the bam dien thoai mot chut roi ngu sau.\n";
        } else if (thoigian == "tre" && dienthoai == "chuahet" && tranbong == "co" && congviec == "co") {
            cout << "Ban co the bam dien thoai mot chut roi ngu sau.\n";
        } else {
            cout << "Ban co the tu chon, nhung ngu som se tot hon cho suc khoe.\n";
        }
    }

    return 0;
}
