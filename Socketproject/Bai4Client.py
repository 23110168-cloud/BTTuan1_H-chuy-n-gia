import socket

host = "127.0.0.1"
port = 1004

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((host, port))

print("Các lệnh: UPPER, LOWER, DELETE, INSERT")
command = input("Nhập lệnh: ").strip().upper()
chuoi = input("Nhập chuỗi: ").strip()

args = ""
if command == "DELETE":
    start = input("Nhập vị trí bắt đầu: ").strip()
    end = input("Nhập vị trí kết thúc: ").strip()
    args = f"|{start}|{end}"
elif command == "INSERT":
    vi_tri = input("Nhập vị trí chèn: ").strip()
    chuoi_con = input("Nhập chuỗi con: ").strip()
    args = f"|{vi_tri}|{chuoi_con}"

client_socket.send(f"{command}|{chuoi}{args}".encode())

result = client_socket.recv(1024).decode()
print("Kết quả từ server:", result)

client_socket.close()
