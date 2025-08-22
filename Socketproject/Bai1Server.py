import socket
import math

def GiaiPT(a, b, c):
    if a == 0:
        return "Không phải phương trình bậc hai."
    
    delta = b**2 - 4*a*c
    if delta > 0:
        x1 = (-b + math.sqrt(delta)) / (2*a)
        x2 = (-b - math.sqrt(delta)) / (2*a)
        return f"Nghiệm x1 = {x1}, x2 = {x2}"
    elif delta == 0:
        x = -b / (2*a)
        return f"Nghiệm kép x = {x}"
    else:
        return "Phương trình vô nghiệm."

host='127.0.0.1'
port=1001
#tạo Socket TCP cho Server
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))
server_socket.listen(10)
print("Server đang chờ kết nối")

while True:
    client_socket, addr = server_socket.accept()
    print(f"Kết nối từ {addr}")

    data = client_socket.recv(1024).decode()
    a, b, c = map(float, data.split())
    result = GiaiPT(a, b, c)
    #gửi đi
    client_socket.send(result.encode())
    client_socket.close()