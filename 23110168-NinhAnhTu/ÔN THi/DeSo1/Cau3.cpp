#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Struct đại diện cho một món đồ
struct Item {
    int weight;
    int value;
    int quantity;
};

int main() {
    ifstream fin("knapsack_input.txt");
    ofstream fout("knapsack_output.txt");

    if (!fin) {
        cerr << "Khong the mo file input!\n";
        return 1;
    }

    int n, W;
    fin >> n >> W;

    vector<Item> items(n);

    // Đọc trọng lượng
    for (int i = 0; i < n; ++i)
        fin >> items[i].weight;

    // Đọc giá trị
    for (int i = 0; i < n; ++i)
        fin >> items[i].value;

    // Đọc số lượng tối đa
    for (int i = 0; i < n; ++i)
        fin >> items[i].quantity;

    // Khởi tạo mảng DP
    vector<int> dp(W + 1, 0);

    // Dynamic Programming cho Bounded Knapsack
    for (int i = 0; i < n; ++i) {
        vector<int> new_dp = dp;

        for (int j = 0; j <= W; ++j) {
            for (int k = 1; k <= items[i].quantity && k * items[i].weight <= j; ++k) {
                new_dp[j] = max(new_dp[j], dp[j - k * items[i].weight] + k * items[i].value);
            }
        }

        dp = new_dp;
    }

    fout << "Gia tri lon nhat co the dat duoc: " << dp[W] << "\n";

    cout << "Da ghi ket qua ra file knapsack_output.txt\n";

    fin.close();
    fout.close();
    return 0;
}


