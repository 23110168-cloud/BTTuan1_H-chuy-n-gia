import socket

def ThayTheChuoi(file_content, s1, s2):
    return file_content.replace(s1, s2)

host = "127.0.0.1"
port = 1003

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))
server_socket.listen(5)
print("Server đang chờ kết nối...")

while True:
    client_socket, addr = server_socket.accept()
    print(f"Kết nối từ {addr}")

    # Dùng makefile để đọc đúng từng dòng dữ liệu
    file_obj = client_socket.makefile()
    filename = file_obj.readline().strip()
    s1 = file_obj.readline().strip()
    s2 = file_obj.readline().strip()

    print(f"Nhận file: {filename}")
    print(f"Chuỗi cần thay: {s1}")
    print(f"Chuỗi thay thế: {s2}")

    try:
        with open(filename, "r", encoding="utf-8") as f:
            content = f.read()

        print(f"Nội dung file gốc:\n{content}")

        # Thay thế chuỗi trong nội dung file
        modified_content = ThayTheChuoi(content, s1, s2)

        with open(filename, "w", encoding="utf-8") as f:
            f.write(modified_content)

        # Đọc lại file sau khi thay thế và gửi về client
        with open(filename, "r", encoding="utf-8") as f:
            data = f.read()
            print("Gửi nội dung đã sửa về client...")
            client_socket.sendall(data.encode())
            print("Đã gửi xong!")

    except Exception as e:
        print(f"Lỗi mở file: {e}")
        client_socket.sendall(f"Lỗi xử lý file: {str(e)}".encode())

    client_socket.close()
