#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<iomanip>

using namespace std; 
#define N 8

// Hàm kiểm tra xem nước đi có hợp lệ hay không
// Một nước đi hợp lệ khi nó nằm trong bàn cờ và chưa được đi qua
int kt(int x, int y, int matran[N][N]);

// Hàm in ma trận kết quả
void print(int matran[N][N]);

// Hàm đệ quy tìm lời giải  
int Dequy(int x, int y, int dem, int matran[N][N], int ktx[8], int kty[8]);

// Hàm chính để giải quyết bài toán hành trình quân mã
int Knight_Tour();

int main(){
    Knight_Tour();
    return 0;
}

// Hàm kiểm tra nước đi hợp lệ
int kt(int x, int y, int matran[N][N]){
    return (x >= 0 && x < N && y >= 0 && y < N && matran[x][y] == -1);
}

// Hàm in bàn cờ với đường đi của quân mã
void print(int matran[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            cout << " " << setw(2) << matran[i][j] << " ";
        cout << endl;
    }
}

// Hàm chính giải quyết bài toán
int Knight_Tour(){
    int matran[N][N];
    
    // Mảng chứa các bước di chuyển hợp lệ của quân mã theo trục x và y
    int x[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int y[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    
    // Khởi tạo bàn cờ với giá trị -1 (chưa đi qua ô nào)
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            matran[i][j] = -1;
    }
    
    // Quân mã bắt đầu từ ô (0,0)
    matran[0][0] = 0;
    
    // Gọi hàm đệ quy để tìm lời giải
    if(Dequy(0, 0, 1, matran, x, y) == 0)
    {
        cout << "Solution does not exist";
        return 0;
    }
    else
        print(matran);
    return 1;
}

// Hàm đệ quy tìm lời giải cho bài toán hành trình quân mã
int Dequy(int x, int y, int dem, int matran[N][N], int ktx[8], int kty[8]){
    int k, nextx, nexty;
    
    // Nếu quân mã đã đi qua tất cả các ô trên bàn cờ, trả về thành công
    if(dem == N * N) return 1;

    // Kiểm tra tất cả 8 nước đi hợp lệ của quân mã
    for(k = 0; k < 8; k++){
        nextx = x + ktx[k];
        nexty = y + kty[k];
        
        // Nếu nước đi hợp lệ thì thực hiện bước tiếp theo
        if(kt(nextx, nexty, matran)){
            matran[nextx][nexty] = dem;
            
            // Nếu tìm được lời giải từ bước tiếp theo, trả về thành công
            if(Dequy(nextx, nexty, dem + 1, matran, ktx, kty) == 1)
                return 1;
            
            // Nếu không tìm được lời giải, quay lui (Backtracking)
            matran[nextx][nexty] = -1;
        }
    }
    
    // Nếu không có nước đi nào hợp lệ, trả về thất bại
    return 0; 
}