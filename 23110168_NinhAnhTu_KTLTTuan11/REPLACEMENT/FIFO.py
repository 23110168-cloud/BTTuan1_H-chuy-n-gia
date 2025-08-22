# Nhập số lượng khung trang (frame)
print("Nhập số lượng khung trang: ", end="")
capacity = int(input())

f, fault, top, pf = [], 0, 0, 'No'

# Nhập chuỗi tham chiếu trang (reference string)
print("Nhập chuỗi trang tham chiếu: ", end="")
s = list(map(int, input().strip().split()))

# In tiêu đề hiển thị bảng kết quả
print("\nTrang|Khung trang →\t", end='')
for i in range(capacity):
    print(i, end=' ')
print("Lỗi\n   ↓\n")

# Duyệt từng trang trong chuỗi tham chiếu
for i in s:
    if i not in f:
        if len(f) < capacity:
            f.append(i)
        else:
            f[top] = i 
            top = (top + 1) % capacity
        fault += 1 
        pf = 'Yes'
    else:
        pf = 'No'

    # In trạng thái khung trang sau mỗi truy cập
    print("   %d\t\t" % i, end='')
    for x in f:
        print(x, end=' ')
    for x in range(capacity - len(f)):
        print(' ', end=' ')
    print(" %s" % pf)
  