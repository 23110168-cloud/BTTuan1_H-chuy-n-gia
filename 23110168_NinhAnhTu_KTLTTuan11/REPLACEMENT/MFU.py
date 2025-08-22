#Tìm trang có số lần sử dụng nhiều nhất, xét từ đầu đến cuối và chọn trang đó để thay thế
from collections import defaultdict

print("Nhập số lượng khung trang: ", end="")
capacity = int(input())

# Lưu trữ số lần mỗi trang được truy cập (page_count)
f, fault, page_count = [], 0, defaultdict(int)

# Nhập chuỗi tham chiếu
print("Nhập chuỗi tham chiếu: ", end="")
s = list(map(int, input().strip().split()))

print("\nString|Khung trang →\t", end="")
for i in range(capacity):
    print(i, end=' ')
print("Lỗi trang\n   ↓\n")

# Duyệt từng trang trong chuỗi tham chiếu
for i in s:
    if i not in f:  
        if len(f) < capacity:
            f.append(i)
        else:
    
            max_count = max(page_count.values())
            max_pages = [k for k, v in page_count.items() if v == max_count]
            max_page = f.index(min(set(f) & set(max_pages)))
            f[max_page] = i

        fault += 1
        page_count[i] += 1
        pf = 'Có'  
    else:
        page_count[i] += 1
        pf = 'Không'

    # In kết quả từng bước
    print("   %d\t\t" % i, end='')
    for x in f:
        print(x, end=' ')
    for x in range(capacity - len(f)):  # Điền vào khoảng trống nếu bộ nhớ chưa đầy
        print(' ', end=' ')
    print(" %s" % pf)

# In kết quả tổng quát
print("\nTổng số yêu cầu: %d\nTổng số lỗi trang: %d\nTỉ lệ lỗi: %0.2f%%" % (len(s), fault, (fault / len(s)) * 100))
#Nhập số lượng khung trang: 3
#Nhập chuỗi tham chiếu: 1 2 3 3 4 1 2 5