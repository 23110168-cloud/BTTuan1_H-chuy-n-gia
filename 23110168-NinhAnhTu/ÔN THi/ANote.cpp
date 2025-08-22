#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<iomanip>
#include<string>
#include <cctype>

using namespace std;

// Chuyển chuỗi về chữ thường
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
// Cấu trúc vector với nhiều cột điểm
struct HocSinh {
    string maHS;
    string hoTen;
    vector<float> diem;
    float DTB;
    int xepHang;
};

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
        while (ss >> d) // đọc file với 1 điểm
            hs.diem.push_back(d);
        ds.push_back(hs);
    }

    fin.close();
}

// Tính điểm trung bình
void tinhDTB(vector<HocSinh>& ds) {
    for (auto& hs : ds) {
        float tong = 0;
        for (float d : hs.diem)
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

// So sánh theo DTB giảm dần
bool soSanhDTB(const HocSinh& a, const HocSinh& b) {
    return a.DTB > b.DTB;
}
// Xắp xếp
void sapXep(vector<HocSinh>& ds) {
    sort(ds.begin(), ds.end(), soSanhDTB);
}

// Hàm xếp hạng (Sắp xếp song xếp hạng)
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

// Câu 2 Greedy + Chi phí 
/*Chọn tối đa số lượng hoạt động không chồng lấn nhau, đồng thời tổng chi phí phải thấp nhất có thể002E
Yêu cầu:
1.	Viết chương trình C++ dùng Greedy Algorithm chọn ra các hoạt động thỏa mãn:
o	Không chồng lấn.
o	Có tổng chi phí nhỏ nhất trong số các phương án tối đa hoạt động.
2.	In ra danh sách hoạt động được chọn và tổng chi phí.*/
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

/*Câu 3 (3 điểm) – Bài toán cái túi có giới hạn (Bounded Knapsack – Dynamic Programming)
Đề bài:
Có n món đồ. Mỗi món có:
•	trọng lượng w[i],
•	giá trị v[i],
•	số lượng tối đa có thể lấy c[i].
Túi có sức chứa W.
Yêu cầu: Viết chương trình C++ sử dụng Dynamic Programming giải bài toán Bounded Knapsack:
•	Tìm giá trị lớn nhất có thể mang theo không vượt quá sức chứa W.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Struct biểu diễn một món đồ
struct Item {
    int weight;
    int value;
    int quantity;
};

// Đọc dữ liệu từ file
bool docFile(const string& tenFile, vector<Item>& items, int& W) {
    ifstream fin(tenFile);
    if (!fin) {
        cerr << "Khong the mo file input!\n";
        return false;
    }

    int n;
    fin >> n >> W;
    items.resize(n);

    for (int i = 0; i < n; ++i) fin >> items[i].weight;
    for (int i = 0; i < n; ++i) fin >> items[i].value;
    for (int i = 0; i < n; ++i) fin >> items[i].quantity;

    fin.close();
    return true;
}

// Giải bài toán Bounded Knapsack bằng Dynamic Programming
int giaiKnapsack(const vector<Item>& items, int W) {
    vector<int> dp(W + 1, 0);

    for (const auto& item : items) {
        vector<int> new_dp = dp;

        for (int j = 0; j <= W; ++j) {
            for (int k = 1; k <= item.quantity && k * item.weight <= j; ++k) {
                new_dp[j] = max(new_dp[j], dp[j - k * item.weight] + k * item.value);
            }
        }

        dp = new_dp;
    }

    return dp[W];
}

// Ghi kết quả ra file
void ghiFile(const string& tenFile, int giaTriToiUu) {
    ofstream fout(tenFile);
    if (!fout) {
        cerr << "Khong the mo file output!\n";
        return;
    }

    fout << "Gia tri lon nhat co the dat duoc: " << giaTriToiUu << "\n";
    fout.close();
}

int main() {
    vector<Item> items;
    int W;

    if (!docFile("knapsack_input.txt", items, W)) return 1;

    int ketQua = giaiKnapsack(items, W);
    ghiFile("knapsack_output.txt", ketQua);

    cout << "Da ghi ket qua ra file knapsack_output.txt\n";
    return 0;
}

// Hàm tìm dãy con tăng dài nhất
void timLIS(const vector<int> &a){
    int n= a.size();
    vector<int> L(n,1);//vector dãy kết thúc ở a[i];
    vector<int> trc(n,-1);//vector truy vấn;
    int Maxdodai=1;
    int vitri=0;
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            if(a[j]<a[i] && L[j]+1 >L[i]){
                L[i]=L[j]+1;
                trc[i]=j;
            }
        }
        if(L[i]>Maxdodai){
            Maxdodai=L[i];
            vitri=i;
        }
    }
    vector<int> lis;
    while(vitri!=-1){
        lis.push_back(a[vitri]);
        vitri=trc[vitri];
    }
    reverse(lis.begin(),lis.end());
    // In kết quả
    cout << "Do dai LIS: " << Maxdodai << endl;
    cout << "Day con: ";
    for (int x : lis) cout << x << " ";
    cout << endl;
}

// Greedy + hiệu suất
//docfile
//chon tong loi nhuan lon nhat- kiem tra tg ko vượt
//ghifile

#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

struct congviec{
    string MaCv;
    int Tg;
    int LoiNhuan;
    float hieusuat;
};

// Xắp xếp công việc theo tg
bool kiemtra(const congviec &a, const congviec &b){
    return a.hieusuat<b.hieusuat;
}
void xapxep(vector<congviec> &cv){
    sort(cv.begin(),cv.end(),kiemtra);
}

void docfile(const string &filename, int &n, int &T, vector<congviec> &cv){
    ifstream file(filename);
    if(!file){
        cerr<<"Erol"; return;
    }
    file >> n;
    file.ignore();
    file >> T;
    file.ignore();
    for(int i=0;i<n;i++){
         congviec ds;
        file >> ds.MaCv >>ds.Tg >>ds.LoiNhuan;
        ds.hieusuat=(float)ds.LoiNhuan/ds.Tg;   
        cv.push_back(ds);
    }
    file.close();
}

// Chon cong viec
void choncongviec(vector<congviec> &ds, int &n, int &T, vector<string> &dcchon, int &tongloinhuan){
    int tongthoigian=0;
    xapxep(ds);
    for(const auto &cv:ds){
        if(tongthoigian+cv.Tg<=T && tongloinhuan+cv.LoiNhuan>tongloinhuan){
            tongthoigian+=cv.Tg;
            tongloinhuan+=cv.LoiNhuan;
            dcchon.push_back(cv.MaCv);
        }
    }
}

void ghifile(const string &filename,vector<string> &dcchon,int tongloinhuan){
    ofstream file(filename);
    if(!file){
        cerr<<"Erol"; return;
    }
    file << "Chon cong viec: ";
    for(size_t i=0; i<dcchon.size();i++){
        file<<dcchon[i]<<" ";
    }
    file << "\nTong loi nhuan: "<<tongloinhuan<<endl;
    file.close();
}


int main(){
    int n,T;
    vector<string> dcchon;
    vector<congviec> CV;
    int tongloinhuan=0;
    docfile("inputCau3De2.txt",n,T,CV);
    choncongviec(CV,n,T,dcchon,tongloinhuan);
    ghifile("outputCau3De2.txt",dcchon,tongloinhuan);
    return 0;
}

// lấy giá trị cuối trong vector
sanpham sps1(vector<sanpham> &ds){
        xapxep(ds);
        sanpham s=ds.back();// lấy giá trị cuối trong vector
        cout << s.masp<<" "<<s.tensp<<" "<<s.dongia<<" "<<s.soluong<<" "<<s.thanhtien<<endl;
        return s;
 }

 /*Câu 2 (3 điểm) – Bài toán chia tiền (Dynamic Programming – Subset Sum)
Đề bài:
Cho n tờ tiền có mệnh giá a[i]. Hỏi có thể chia thành 2 nhóm sao cho tổng 2 nhóm bằng nhau không?
Yêu cầu:
1.	Nhập hoặc đọc danh sách mệnh giá.
2.	Viết chương trình Dynamic Programming để kiểm tra khả năng chia đều.
*/
#include <iostream>
#include <vector>
using namespace std;

// Hàm kiểm tra và truy vết tập con có tổng bằng target (sum / 2)
bool chiaTien(const vector<int>& a, vector<int>& nhom1, vector<int>& nhom2) {
    int n = a.size();
    int sum = 0;
    for (int val : a) sum += val;

    cout << "Tong tien: " << sum << endl;

    if (sum % 2 != 0) return false; // Không thể chia đều

    int target = sum / 2;

    // dp[i][j] = true nếu dùng i phần tử đầu có thể đạt tổng j
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    dp[0][0] = true;

    // DP – kiểm tra có tập con nào tổng bằng target không
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= target; ++j) {
            dp[i][j] = dp[i - 1][j]; // Không chọn phần tử thứ i
            if (j >= a[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - a[i - 1]];
            }
        }
    }

    if (!dp[n][target]) return false; // Không thể chia

    // Truy vết để lấy tập con (nhóm 1)
    int i = n, j = target;
    vector<bool> daChon(n, false);
    while (i > 0 && j > 0) {
        if (j >= a[i - 1] && dp[i - 1][j - a[i - 1]]) {
            nhom1.push_back(a[i - 1]);
            daChon[i - 1] = true;
            j -= a[i - 1];
        }
        i--;
    }

    // Tập còn lại là nhóm 2
    for (int k = 0; k < n; ++k) {
        if (!daChon[k]) nhom2.push_back(a[k]);
    }

    return true;
}

int main() {
    int n;
    cout << "Nhap so luong to tien: ";
    cin >> n;

    vector<int> a(n);
    cout << "Nhap cac menh gia: ";
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> nhom1, nhom2;

    if (chiaTien(a, nhom1, nhom2)) {
        int tong = 0;
        for (int x : nhom1) tong += x;
        cout << "Co the chia thanh 2 nhom co tong bang nhau: " << tong << endl;

        cout << "Nhom 1: ";
        for (int x : nhom1) cout << x << " ";
        cout << "(Tong: " << tong << ")" << endl;

        cout << "Nhom 2: ";
        int tong2 = 0;
        for (int x : nhom2) {
            cout << x << " ";
            tong2 += x;
        }
        cout << "(Tong: " << tong2 << ")" << endl;
    } else {
        cout << "Khong the chia deu." << endl;
    }

    return 0;
}

// a.resize(n); cấp phát bộ nhớ
// a.back(); lấy giá trị cuối cùng trong vector
// stoi(n); ép kiển int 
// stof(n); ép kiểu float
// to_string(x); chuyển số thành chuỗi
// toupper(n); chuyển string thành hoa
// tolower(n); chuyển string thành thường
// compare(): so sánh chuỗi
/*string a = "apple", b = "banana";
if (a.compare(b) < 0) cout << "apple < banana";
// s.empty(): kt chuỗi rỗng
*/

//Liệt kê tất cả các xâu nhị phân có độ dài 5 mà không có hai bits 1 đứng liền nhau.
#include <iostream>
#include <vector>
using namespace std;

int n = 5;
vector<int> x(5);

void backtrack(int i) {
    for (int j = 0; j <= 1; ++j) {
        if (j == 1 && i > 0 && x[i - 1] == 1) continue; // không cho 2 số 1 liền nhau
        x[i] = j;
        if (i == n - 1) {
            for (int k = 0; k < n; ++k)
                cout << x[k];
            cout << endl;
        } else {
            backtrack(i + 1);
        }
    }
}

int main() {
    backtrack(0);
    return 0;
}

//Tìm hai số có tổng gần nhất với một số cho trước
void find_closest_sum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());  // Sắp xếp mảng
    int left = 0, right = nums.size() - 1;
    int closest_sum = nums[left] + nums[right];
    int closest_pair[2] = {left, right};

    while (left < right) {
        int sum = nums[left] + nums[right];
        if (abs(sum - target) < abs(closest_sum - target)) {
            closest_sum = sum;
            closest_pair[0] = left;
            closest_pair[1] = right;
        }

        if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    cout << "Indices of the closest pair: " << closest_pair[0] << " " << closest_pair[1] << endl;
}

//Tìm cặp điểm có khoảng cách gần nhất
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Diem {
    int x, y, chiSo;
    double khoangCach() const {
        return sqrt(x * x + y * y);
    }
};

bool soSanh(const Diem& a, const Diem& b) {
    return a.khoangCach() < b.khoangCach();
}

double tinhKhoangCach(const Diem& a, const Diem& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void timCapDiemGanNhat(vector<Diem>& danhSachDiem) {
    sort(danhSachDiem.begin(), danhSachDiem.end(), soSanh);

    double khoangCachNhoNhat = 1e9;
    pair<int, int> capGanNhat;

    for (int i = 0; i < danhSachDiem.size() - 1; i++) {
        double kc = tinhKhoangCach(danhSachDiem[i], danhSachDiem[i + 1]);
        if (kc < khoangCachNhoNhat) {
            khoangCachNhoNhat = kc;
            capGanNhat = {danhSachDiem[i].chiSo, danhSachDiem[i + 1].chiSo};
        }
    }

    cout << "Chi so cua cap diem gan nhat: " 
         << capGanNhat.first << " " << capGanNhat.second << endl;
}

// Đảo ngược chuỗi
void daoNguocChuoi(string &s) {
    reverse(s.begin(), s.end());
}

// Liệt kê tất cả các tập con của n pt
#include <iostream>
#include <vector>
using namespace std;

void generate_subsets(vector<int>& nums, vector<int>& subset, int index) {
    if (index == nums.size()) {
        cout << "{ ";
        for (int num : subset) cout << num << " ";
        cout << "}\n";
        return;
    }

    // Không chọn phần tử hiện tại
    generate_subsets(nums, subset, index + 1);

    // Chọn phần tử hiện tại
    subset.push_back(nums[index]);
    generate_subsets(nums, subset, index + 1);
    subset.pop_back(); // Quay lui (Backtracking)
}

// Liệt kê tất cả hoán vị của n pt
void generate_permutations(vector<int>& nums, int start) {
    if (start == nums.size()) {
        cout << "{ ";
        for (int num : nums) cout << num << " ";
        cout << "}\n";
        return;
    }

    for (int i = start; i < nums.size(); i++) {
        swap(nums[start], nums[i]);              // Hoán đổi phần tử
        generate_permutations(nums, start + 1);  // Gọi đệ quy
        swap(nums[start], nums[i]);              // Quay lui (Backtrack)
    }
}
// Hàm tìm cặp phân số gần nhau nhất
void find_closest_fractions(int n, vector<Fraction> &fractions) {
    sort(fractions.begin(), fractions.end(), compare);

    double min_diff = 1e9;
    pair<int, int> closest_pair;

    for (int i = 0; i < n - 1; i++) {
        double diff = abs(fractions[i].value() - fractions[i + 1].value());
        if (diff < min_diff) {
            min_diff = diff;
            closest_pair = {fractions[i].index, fractions[i + 1].index};
        }
    }

    if (closest_pair.first > closest_pair.second)
        swap(closest_pair.first, closest_pair.second);

    cout << closest_pair.first << " " << closest_pair.second << endl;
}

// Sinh tổ hợp chập k của n
// Hàm sinh tổ hợp chập k của n phần tử
void sinhToHop(int n, int k) {
    int a[k + 1]; // Mảng để lưu tổ hợp hiện tại
    for (int i = 1; i <= k; i++)
        a[i] = i; // Khởi tạo tổ hợp đầu tiên

    while (true) {
        // In tổ hợp hiện tại
        for (int i = 1; i <= k; i++)
            cout << a[i] << " ";
        cout << endl;

        // Tìm vị trí cần tăng
        int i = k;
        while (i > 0 && a[i] == n - k + i)
            i--;

        // Nếu i = 0, đã liệt kê hết tổ hợp
        if (i == 0)
            break;

        a[i]++; // Tăng phần tử tại vị trí i
        for (int j = i + 1; j <= k; j++)
            a[j] = a[j - 1] + 1; // Cập nhật các phần tử sau i
    }
}

//Lập lịch có thời hạn
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct Job {
    int start, end, profit, index;
};

bool cmp(Job a, Job b) {
    return a.end < b.end;
}

// Tìm công việc gần nhất không xung đột
int findLastNonConflict(const vector<Job>& jobs, int i) {
    int left = 0, right = i - 1, res = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (jobs[mid].end <= jobs[i].start) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return res;
}

int main() {
    ifstream fin("input01.txt");
    ofstream fout("output01.txt");

    int n;
    fin >> n;
    vector<Job> jobs(n);
    for (int i = 0; i < n; ++i) {
        fin >> jobs[i].start >> jobs[i].end >> jobs[i].profit;
        jobs[i].index = i; // để nhận diện ban đầu nếu cần
    }

    // Sắp xếp công việc theo thời gian kết thúc
    sort(jobs.begin(), jobs.end(), cmp);

    // DP + Truy vết
    vector<int> dp(n);
    vector<int> prev(n, -1); // lưu chỉ số công việc trước được chọn
    dp[0] = jobs[0].profit;

    for (int i = 1; i < n; ++i) {
        int incl = jobs[i].profit;
        int last = findLastNonConflict(jobs, i);
        if (last != -1) {
            incl += dp[last];
        }

        if (incl > dp[i - 1]) {
            dp[i] = incl;
            prev[i] = last;
        } else {
            dp[i] = dp[i - 1];
            prev[i] = prev[i - 1];
        }
    }

    // Truy vết các công việc được chọn
    vector<Job> selected;
    int i = n - 1;
    while (i >= 0) {
        int last = findLastNonConflict(jobs, i);
        int incl = jobs[i].profit + (last != -1 ? dp[last] : 0);
        if (incl > (i > 0 ? dp[i - 1] : 0)) {
            selected.push_back(jobs[i]);
            i = last;
        } else {
            i--;
        }
    }

    // Xuất kết quả
    fout << "Loi nhuan toi da: " << dp[n - 1] << "\n";
    fout << "Cac cong viec duoc chon:\n";

    // Vì ta truy vết ngược nên cần đảo ngược lại để in đúng thứ tự
    reverse(selected.begin(), selected.end());
    for (auto& job : selected) {
        fout << "Start: " << job.start << ", End: " << job.end << ", Profit: " << job.profit << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}

// tg kt gần nhất
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

// Bài toán phòng thi
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

struct Exam {
    int start, end, id;
};

bool cmp(Exam a, Exam b) {
    return a.start < b.start;
}

int main() {
    ifstream fin("input03.txt");
    ofstream fout("output03.txt");

    int n;
    fin >> n;
    vector<Exam> exams(n);

    for (int i = 0; i < n; ++i) {
        fin >> exams[i].start >> exams[i].end;
        exams[i].id = i + 1; // gán số thứ tự bài kiểm tra
    }

    // Bước 1: Sắp xếp theo thời gian bắt đầu
    sort(exams.begin(), exams.end(), cmp);

    // Bước 2: Min-heap theo thời gian kết thúc + id phòng
    typedef pair<int, int> RoomEnd; // {thời gian kết thúc, id phòng}
    priority_queue<RoomEnd, vector<RoomEnd>, greater<RoomEnd>> heap;

    int roomCount = 0;
    vector<vector<Exam>> roomAssignments; // roomAssignments[i] chứa các bài trong phòng i

    for (auto& exam : exams) {
        if (!heap.empty() && heap.top().first <= exam.start) {
            // Dùng lại phòng có thời gian kết thúc sớm nhất
            int roomID = heap.top().second;
            heap.pop();
            roomAssignments[roomID].push_back(exam);
            heap.push({exam.end, roomID});
        } else {
            // Mở phòng mới
            roomAssignments.push_back({exam});
            heap.push({exam.end, roomCount});
            roomCount++;
        }
    }

    // Ghi kết quả ra file
    fout << "So phong thi toi thieu can dung: " << roomCount << "\n";
    fout << "Chi tiet xep phong:\n\n";
    for (int i = 0; i < roomCount; ++i) {
        fout << "Phong " << i + 1 << ":\n";
        for (auto& e : roomAssignments[i]) {
            fout << "(" << e.start << " -> " << e.end << ")\n";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}

//Code C++ không dùng heap:
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct Exam {
    int start, end;
};

bool cmp(Exam a, Exam b) {
    return a.start < b.start;
}

int main() {
    ifstream fin("input03.txt");
    ofstream fout("output03.txt");

    int n;
    fin >> n;
    vector<Exam> exams(n);
    for (int i = 0; i < n; ++i) {
        fin >> exams[i].start >> exams[i].end;
    }

    // B1: Sắp xếp theo thời gian bắt đầu
    sort(exams.begin(), exams.end(), cmp);

    vector<int> roomEndTime; // roomEndTime[i]: thời gian kết thúc của phòng i
    vector<vector<Exam>> roomAssignments;

    for (auto& exam : exams) {
        bool assigned = false;

        // Tìm phòng có thể gán
        for (int i = 0; i < roomEndTime.size(); ++i) {
            if (roomEndTime[i] <= exam.start) {
                // Gán bài này vào phòng i
                roomAssignments[i].push_back(exam);
                roomEndTime[i] = exam.end;
                assigned = true;
                break;
            }
        }

        // Nếu chưa gán được → mở phòng mới
        if (!assigned) {
            roomEndTime.push_back(exam.end);
            roomAssignments.push_back({exam});
        }
    }

    int roomCount = roomEndTime.size();
    fout << "So phong thi toi thieu can dung: " << roomCount << "\n";
    fout << "Chi tiet xep phong:\n\n";

    for (int i = 0; i < roomCount; ++i) {
        fout << "Phong " << i + 1 << ":\n";
        for (auto& e : roomAssignments[i]) {
            fout << "(" << e.start << " -> " << e.end << ")\n";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
