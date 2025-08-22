import socket
# Khai báo địa chỉ sever
host='127.0.0.1'
port=1001
# Khởi tạo kết nối TCP
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Kết nối đến Server
client_socket.connect((host, port))

a, b, c = input("Nhập a, b, c (cách nhau bằng dấu cách): ").split()
client_socket.send(f"{a} {b} {c}".encode())
#nhận kết quả từ Server
result = client_socket.recv(1024).decode()
print("Kết quả từ server:", result)

client_socket.close()