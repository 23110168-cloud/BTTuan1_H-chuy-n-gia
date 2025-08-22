#Tìm trang có thể được sử dụng ít nhất trong tương lai
print("Nhập số lượng khung trang: ", end="")
capacity = int(input())


#occurance: Danh sách lưu trữ chỉ số thời điểm xuất hiện tiếp theo của các trang trong chuỗi tham chiếu.
f, fault, pf = [], 0, 'No'
occurance = [None for i in range(capacity)]

# Nhập chuỗi truy vấn
print("Nhập chuỗi tham chiếu: ", end="")
s = list(map(int, input().strip().split()))
print("\nString|Khung trang →\t", end='')
for i in range(capacity):
    print(i, end=' ')
print("Lỗi trang\n   ↓\n")

for i in range(len(s)): 
    if s[i] not in f:  
        if len(f) < capacity: 
            f.append(s[i])
        else:
            for x in range(len(f)): 
                if f[x] not in s[i + 1:]:  # nếu trang đó không có trong chuỗi truy vấn
                    f[x] = s[i]  # thay thế trang đó bằng trang mới
                    break
                else:
                    # Nếu không thì tính toán thời điểm xuất hiện tiếp theo của phần tử tham chiếu (nhỏ nhất)
                    occurance[x] = s[i + 1:].index(f[x])
            else:
                # Nếu cùng số occurance thì tìm thời điểm xuất hiện tiếp theo xa nhất
                f[occurance.index(max(occurance))] = s[i]  # thay thế trang có thời điểm xuất hiện xa nhất
        fault += 1
        pf = 'Có' 
    else:
        pf = 'Không'

    print("   %d\t\t" % s[i], end='')
    for x in f:
        print(x, end=' ')
    for x in range(capacity - len(f)):
        print(' ', end=' ')
    print(" %s" % pf)

print("\nTổng số yêu cầu: %d\nTổng số lỗi trang: %d\nTỉ lệ lỗi: %0.2f%%" % (len(s), fault, (fault / len(s)) * 100))
#Nhập số lượng khung trang: 3
#Nhập chuỗi tham chiếu: 1 2 3 3 4 1 2 5