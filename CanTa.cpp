#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> weights;
vector<vector<int>> memo;

// Hàm đệ quy có nhớ để tìm tập con có tổng lớn nhất ≤ target
int knapsack(int index, int target) {
    if (target < 0) return 0; // Không thể lấy quá target
    if (index == N) return 0; // Đã duyệt hết các quả tạ
    if (memo[index][target] != -1) return memo[index][target];

    // Không lấy quả tạ hiện tại
    int best = knapsack(index + 1, target);

    // Lấy quả tạ hiện tại nếu có thể
    if (target >= weights[index]) {
        best = max(best, weights[index] + knapsack(index + 1, target - weights[index]));
    }

    return memo[index][target] = best;
}

int max_balanced_weight() {
    int total_weight = 0;
    for (int w : weights) total_weight += w;

    int target = total_weight / 2;
    memo.assign(N, vector<int>(target + 1, -1));
    int best_sum = knapsack(0, target);

    // Nếu không tìm được bất kỳ tập con nào hợp lệ, in ra 0
    return best_sum == 0 ? 0 : 2 * best_sum;
}

int main() {
    cin >> N;
    weights.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> weights[i];
    }

    cout << max_balanced_weight() << endl;
    return 0;
}
