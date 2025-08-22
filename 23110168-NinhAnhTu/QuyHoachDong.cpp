#include <iostream>
#include <vector>
#include<fstream>
using namespace std;

int main() {
    // Bước 1: Mở file input.txt để đọc dữ liệu
    ifstream inp("inputgame.txt");
    if (!inp) {
        cout << "Khong the mo file input.txt!" << endl;
        return 1;
    }

    // Bước 2: Đọc dữ liệu từ file
    int N, K;
    inp >> N; // Số lượng trò chơi
    inp >> K; // Số tiền Việt có
    
    vector<int> cost(N), time(N);
    for (int i = 0; i < N; i++) {
        inp >> cost[i] >> time[i]; // Chi phí và thời gian của trò chơi thứ i
    }
    inp.close(); // Đóng file input.txt

    // Bước 3: Khởi tạo mảng DP và mảng để truy vết
    vector<int> dp(K + 1, 0); // dp[i] là thời gian tối đa với số tiền i
    vector<int> last_game(K + 1, -1); // Lưu trò chơi cuối cùng được chọn để đạt dp[i]
    dp[0] = 0; // Với 0 tiền thì không chơi được
    
    // Bước 4: Tính DP và lưu thông tin truy vết
    for (int j = 1; j <= K; j++) {
        for (int i = 0; i < N; i++) {
            if (j >= cost[i]) {
                int new_time = dp[j - cost[i]] + time[i];
                if (new_time > dp[j]) {
                    dp[j] = new_time;
                    last_game[j] = i; // Lưu trò chơi i là trò cuối cùng được chọn
                }
            }
        }
    }

    // Bước 5: Truy vết để tìm cách chọn trò chơi
    vector<int> count_games(N, 0); // Đếm số lần chơi của từng trò
    int remaining_money = K;
    while (remaining_money > 0 && last_game[remaining_money] != -1) {
        int game = last_game[remaining_money]; // Trò chơi được chọn
        count_games[game]++; // Tăng số lần chơi trò game
        remaining_money -= cost[game]; // Trừ số tiền đã dùng
    }

    // Bước 6: Mở file output.txt để ghi kết quả
    ofstream out("outputgame.txt");
    if (!out) {
        cout << "Khong the mo file output.txt!" << endl;
        return 1;
    }

    // Bước 7: Ghi kết quả vào file output.txt
    out << "Tong thoi gian toi da: " << dp[K] << " phut" << endl;
    out << "Chi tiet cach chon tro choi:" << endl;
    for (int i = 0; i < N; i++) {
        if (count_games[i] > 0) {
            out << "- Tro choi " << (i + 1) << " (Chi phi: " << cost[i] << "K, Thoi gian: " << time[i] 
                << " phut): Chon " << count_games[i] << " lan, tong thoi gian " 
                << count_games[i] * time[i] << " phut" << endl;
        }
    }
    out.close(); // Đóng file output.txt

    // Bước 8: In kết quả ra màn hình (tùy chọn, để kiểm tra)
    cout << "Tong thoi gian toi da: " << dp[K] << " phut" << endl;
    cout << "Chi tiet cach chon tro choi:" << endl;
    for (int i = 0; i < N; i++) {
        if (count_games[i] > 0) {
            cout << "- Tro choi " << (i + 1) << " (Chi phi: " << cost[i] << "K, Thoi gian: " << time[i] 
                 << " phut): Chon " << count_games[i] << " lan, tong thoi gian " 
                 << count_games[i] * time[i] << " phut" << endl;
        }
    }

    return 0;
}