

import socket
import json

MT1 = [[1, 5, 9], [1, 5, 9]]

MT2 = [[15, 9], [2, 0], [0, 5]]

host = '127.0.0.1'
port = 1002

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((host, port))

data = json.dumps({"MT1": MT1, "MT2": MT2})
client_socket.send(data.encode())

result = client_socket.recv(4096).decode()
print("Kết quả phép nhân ma trận:")
print(json.loads(result))  
client_socket.close()
