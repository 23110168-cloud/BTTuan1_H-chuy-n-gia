
import socket
import numpy as np # hỗ trợ tính toán matran
import json # hỗ python object sang json và ngược lại

def NhanHaiMaTran(MT1, MT2):
    try:
        result = np.dot(MT1, MT2).tolist()  
        return result
    except ValueError:
        return "Lỗi: Không thể nhân hai ma trận có kích thước không phù hợp."

host = '127.0.0.1'
port = 1002

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))
server_socket.listen(5)
print(f"Server đang chờ kết nối")

while True:
    client_socket, addr = server_socket.accept()
    print(f"Kết nối từ {addr}")

    data = client_socket.recv(4096).decode()
    matrices = json.loads(data)  
    
    MT1 = np.array(matrices["MT1"])
    MT2 = np.array(matrices["MT2"])

    result = NhanHaiMaTran(MT1, MT2)

    client_socket.send(json.dumps(result).encode())

    client_socket.close()
