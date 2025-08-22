import socket
import time

host = "127.0.0.1"
port = 1003

filename = input("Nhập tên file: ").strip()
s1 = input("Nhập chuỗi cần thay thế: ").strip()
s2 = input("Nhập chuỗi thay thế: ").strip()

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((host, port))

print("Đang gửi dữ liệu đến server...")
client_socket.sendall((filename + "\n").encode())
time.sleep(0.1)  # Đợi một chút để server xử lý
client_socket.sendall((s1 + "\n").encode())
time.sleep(0.1)
client_socket.sendall((s2 + "\n").encode())
time.sleep(0.1)
print("Dữ liệu đã gửi xong!")

# Nhận dữ liệu từ server
modified_content = client_socket.recv(4096).decode()
print("Phản hồi từ server nhận được!")
print("\nNội dung file sau khi thay thế:\n", modified_content)

client_socket.close()
