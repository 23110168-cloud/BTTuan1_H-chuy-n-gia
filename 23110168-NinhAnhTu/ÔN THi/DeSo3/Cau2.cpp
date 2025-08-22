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
