#dư nhiều nhất
def WorstFit(blockSize, blocks, processSize, processes):
    # Mảng này sẽ lưu ID khối bộ nhớ đã cấp phát cho từng tiến trình
    allocation = [-1] * processes

    for i in range(processes):
        indexPlaced = -1
        for j in range(blocks):
      
            if blockSize[j] >= processSize[i]:
      
                if indexPlaced == -1:
                    indexPlaced = j
            
                elif blockSize[indexPlaced] < blockSize[j]:
                    indexPlaced = j
        
        # Nếu tìm được khối phù hợp cho tiến trình
        if indexPlaced != -1:
  
            allocation[i] = indexPlaced
 
   
            blockSize[indexPlaced] -= processSize[i]
 
    print("\nProcess No.\tProcess Size\tBlock no.")
    for i in range(processes):
        print(f"{i+1} \t\t\t {processSize[i]} \t\t\t", end="")
        if allocation[i] != -1:
            print(allocation[i] + 1)
        else:
            print("Chưa được cấp phát")
 

# Chương trình chính
if __name__ == "__main__":
    blockSize =  [100, 500, 200, 300, 600]
    processSize = [212, 417, 112, 426]
    blocks = len(blockSize)
    processes = len(processSize)

    WorstFit(blockSize, blocks, processSize, processes)
