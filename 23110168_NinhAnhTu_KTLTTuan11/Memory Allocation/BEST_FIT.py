#vừa khít nhất
def bestFit(blockSize, m, processSize, n):
     
    # Mảng lưu chỉ số block được cấp phát cho từng tiến trình
    allocation = [-1] * n
     
    for i in range(n):
         
        # Tìm khối bộ nhớ phù hợp nhất
        bestIdx = -1
        for j in range(m):
            if blockSize[j] >= processSize[i]:
                if bestIdx == -1:
                    bestIdx = j
                elif blockSize[bestIdx] > blockSize[j]:
                    bestIdx = j
 
        # Nếu tìm được khối bộ nhớ phù hợp
        if bestIdx != -1:
             
            allocation[i] = bestIdx
 
            blockSize[bestIdx] -= processSize[i]
 
    print("Số tiến trình   Kích thước tiến trình     Số khối bộ nhớ")
    for i in range(n):
        print(i + 1, "         ", processSize[i],
                                end = "         ")
        if allocation[i] != -1:
            print(allocation[i] + 1)
        else:
            print("Không được cấp phát")
 
# Chương trình chính
if __name__ == '__main__':
    blockSize = [100, 500, 200, 300, 600]
    processSize = [212, 417, 112, 426]
    m = len(blockSize)
    n = len(processSize)
 
    bestFit(blockSize, m, processSize, n)
