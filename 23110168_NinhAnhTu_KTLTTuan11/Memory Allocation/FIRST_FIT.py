#gặp là lấy
def FirstFit(block_Size, blocks, process_Size, proccesses):
    # Tạo danh sách lưu chỉ số block được cấp phát cho từng tiến trình
    allocate = [-1] * proccesses

    for i in range(proccesses):
        for j in range(blocks):
            if block_Size[j] >= process_Size[i]:
                allocate[i] = j
                block_Size[j] -= process_Size[i]
                break

    print("Số tiến trình\tKích thước tiến trình\t\tSố khối bộ nhớ")

    for i in range(proccesses):
        print(str(i + 1) + "\t\t\t" + str(process_Size[i]) + "\t\t\t", end=" ")

        if allocate[i] != -1:
            print(allocate[i] + 1)
        else:
            print("Không được cấp phát")


# Chương trình chính
if __name__ == "__main__":
    block_Size = [100, 500, 200, 300, 600]
    process_Size = [212, 417, 112, 426]
    m = len(block_Size)
    n = len(process_Size)

    FirstFit(block_Size, m, process_Size, n)
