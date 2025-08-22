#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Activity {
    int start, end, cost;
};

// So sánh theo thời gian kết thúc trước, nếu bằng thì cost nhỏ hơn được ưu tiên
bool cmp(const Activity& a, const Activity& b) {
    if (a.end != b.end)
        return a.end < b.end;
    return a.cost < b.cost;
}

void docFile(const string& tenFile, vector<Activity>& ds) {
    ifstream fin(tenFile);
    if (!fin) {
        cerr << "Khong mo duoc file!" << endl;
        return;
    }

    int n;
    fin >> n;
    Activity act;
    for (int i = 0; i < n; ++i) {
        fin >> act.start >> act.end >> act.cost;
        ds.push_back(act);
    }

    fin.close();
}

void ghiFile(const string& tenFile, const vector<Activity>& chon, int tongChiPhi) {
    ofstream fout(tenFile);
    fout << "Cac hoat dong chon:\n";
    for (const auto& a : chon) {
        fout << "(" << a.start << "," << a.end << ") voi chi phi " << a.cost << "\n";
    }
    fout << "\nSo luong toi da: " << chon.size() << "\n";
    fout << "Tong chi phi: " << tongChiPhi << "\n";
    fout.close();
}

int main() {
    vector<Activity> ds;
    docFile("activity_input.txt", ds);

    sort(ds.begin(), ds.end(), cmp);

    vector<Activity> chon;
    int tongChiPhi = 0;
    int thoiGianKetThucGanNhat = -1;

    for (const auto& a : ds) {
        if (a.start >= thoiGianKetThucGanNhat) {
            chon.push_back(a);
            tongChiPhi += a.cost;
            thoiGianKetThucGanNhat = a.end;
        }
    }

    ghiFile("activity_output.txt", chon, tongChiPhi);
    cout << "Da ghi ket qua ra file activity_output.txt\n";
    return 0;
}
