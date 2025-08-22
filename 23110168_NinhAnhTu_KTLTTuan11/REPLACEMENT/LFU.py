# tần xuất truy cập ít nhất
# Tìm trang có số lần sử dụng ít nhất, xét từ đầu đến cuối và chọn trang đó để thay thế
from collections import defaultdict

print("Nhập số lượng khung trang: ", end="")
capacity = int(input())

f, fault, page_count = [], 0, defaultdict(int)

# Nhập chuỗi tham chiếu trang
print("Nhập chuỗi tham chiếu: ", end="")
s = list(map(int, input().strip().split()))

# In tiêu đề bảng
print("\nTrang|Khung trang →\t", end='')
for i in range(capacity):
    print(i, end=' ')
print("Lỗi trang\n   ↓\n")

# Duyệt từng trang trong chuỗi tham chiếu
for i in s:
    if i not in f:
        if len(f) < capacity:
            f.append(i)
        else:
            min_count = min(page_count.values())
            min_pages = [k for k, v in page_count.items() if v == min_count]
            min_page = f.index(min(set(f) & set(min_pages)))
            del page_count[f[min_page]]
            f[min_page] = i
        fault += 1 
        page_count[i] += 1 
        pf = 'Có' 
    else:
        page_count[i] += 1 
        pf = 'Không' 

    # In trạng thái hiện tại của khung trang
    print("   %d\t\t" % i, end='')
    for x in f:
        print(x, end=' ')
    for x in range(capacity - len(f)):
        print(' ', end=' ')
    print(" %s" % pf)

# In thống kê tổng kết
print("\nTổng số yêu cầu: %d\nTổng số lỗi trang: %d\nTỉ lệ lỗi: %0.2f%%" %
      (len(s), fault, (fault / len(s)) * 100))
#Nhập số lượng khung trang: 3
#Nhập chuỗi tham chiếu: 1 2 3 3 4 1 2 5