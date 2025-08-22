import socket

def xu_ly_chuoi(command, chuoi, *args):
    if command == "UPPER":
        return chuoi.upper()
    elif command == "LOWER":
        return chuoi.lower()
    elif command == "DELETE":
        start, end = map(int, args)
        return chuoi[:start] + chuoi[end:]
    elif command == "INSERT":
        vi_tri, chuoi_con = int(args[0]), args[1]
        return chuoi[:vi_tri] + chuoi_con + chuoi[vi_tri:]
    else:
        return "Lệnh không hợp lệ"

host = "127.0.0.1"
port = 1004

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))
server_socket.listen(5)
print("Server đang chờ kết nối...")

while True:
    client_socket, addr = server_socket.accept()
    print(f"Kết nối từ {addr}")

    data = client_socket.recv(1024).decode()
    parts = data.split("|")
    command = parts[0]
    chuoi = parts[1]
    args = parts[2:] if len(parts) > 2 else []
    
    result = xu_ly_chuoi(command, chuoi, *args)
    client_socket.send(result.encode())

    client_socket.close()
