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
    ifstream fin("input04.txt");
    ofstream fout("output04.txt");

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
