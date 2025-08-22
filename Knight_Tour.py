N = 8

# Hàm kiểm tra xem vị trí (x, y) có hợp lệ không
# Một vị trí hợp lệ nếu nó nằm trong bàn cờ và chưa được đi qua

def kt(x, y, matran):
    return 0 <= x < N and 0 <= y < N and matran[x][y] == -1

# Hàm in bàn cờ dưới dạng ma trận

def print_board(matran):
    for row in matran:
        print(" ".join(f"{cell:2}" for cell in row))

# Hàm đệ quy để tìm lời giải của bài toán hành trình quân mã
# x, y: vị trí hiện tại của quân mã
# dem: số bước đã đi
# matran: ma trận lưu vết hành trình
# ktx, kty: danh sách các nước đi hợp lệ của quân mã

def dequy(x, y, dem, matran, ktx, kty):
    # Nếu quân mã đã đi hết tất cả các ô trên bàn cờ thì trả về True
    if dem == N * N:
        return True
    
    # Thử tất cả 8 nước đi có thể của quân mã
    for k in range(8):
        nextx, nexty = x + ktx[k], y + kty[k]
        
        # Nếu nước đi hợp lệ thì thực hiện bước tiếp theo
        if kt(nextx, nexty, matran):
            matran[nextx][nexty] = dem
            
            # Nếu tìm được lời giải từ bước tiếp theo, trả về True
            if dequy(nextx, nexty, dem + 1, matran, ktx, kty):
                return True
            
            # Nếu không tìm được đường đi hợp lệ, quay lui (Backtracking)
            matran[nextx][nexty] = -1  
    
    # Nếu không có nước đi nào hợp lệ, trả về False
    return False

# Hàm chính giải quyết bài toán hành trình quân mã

def knight_tour():
    # Khởi tạo bàn cờ với tất cả ô là -1 (chưa đi qua)
    matran = [[-1 for _ in range(N)] for _ in range(N)]
    
    # Danh sách các bước di chuyển hợp lệ của quân mã theo trục x và y
    ktx = [2, 1, -1, -2, -2, -1, 1, 2]
    kty = [1, 2, 2, 1, -1, -2, -2, -1]
    
    # Quân mã bắt đầu từ ô (0,0)
    matran[0][0] = 0
    
    # Gọi hàm đệ quy để tìm lời giải
    if not dequy(0, 0, 1, matran, ktx, kty):
        print("Solution does not exist")  # Nếu không có lời giải, thông báo
        return False
    else:
        print_board(matran)  # Nếu có lời giải, in ra bàn cờ
        return True

# Chạy chương trình
if __name__ == "__main__":
    knight_tour()
