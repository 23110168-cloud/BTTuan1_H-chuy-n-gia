#số lần xuất hiện ít nhất
# Tìm trang có số lần sử dụng lâu nhất và chọn trang đó để thay thế
print("Nhập số lượng khung trang: ", end="")
capacity = int(input())

# Khởi tạo danh sách đánh dấu thời điểm từng khung trang được thêm vào (st)
f, st, fault, pf = [], [], 0, 'Không'

# Nhập chuỗi tham chiếu
print("Nhập chuỗi tham chiếu: ", end="")
s = list(map(int, input().strip().split()))

# In tiêu đề
print("\nTrang|Khung trang →\t", end='')
for i in range(capacity):
    print(i, end=' ')
print("Lỗi trang\n   ↓\n")

for i in s:  
    if i not in f:  
        if len(f) < capacity:
            f.append(i)  
            st.append(len(f) - 1)  # Đánh dấu vị trí thêm vào
        else:
            ind = st.pop(0)  
            f[ind] = i  
            st.append(ind)  # Đánh dấu lại vị trí mới sử dụng
        pf = 'Có'
        fault += 1
    else:
   
        st.append(st.pop(st.index(f.index(i))))
        pf = 'Không'

    # In trạng thái khung sau mỗi bước
    print("   %d\t\t" % i, end='')
    for x in f:
        print(x, end=' ')
    for x in range(capacity - len(f)):
        print(' ', end=' ')
    print(" %s" % pf)

# In thống kê kết quả cuối cùng
print("\nTổng số yêu cầu: %d\nTổng số lỗi trang: %d\nTỉ lệ lỗi: %0.2f%%" % (len(s), fault, (fault / len(s)) * 100))

#Số khung trang: 3  
#Chuỗi tham chiếu: 1 2 3 3 4 1 2 5
