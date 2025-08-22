using System;
using System.Net.Sockets;
using System.Text;

class Client
{
    static void Main()
    {
        string host = "127.0.0.1";
        int port = 1001;
        TcpClient client = new TcpClient();
        client.Connect(host, port);

        NetworkStream stream = client.GetStream();

        Console.Write("Nhập a, b, c (cách nhau bằng dấu cách): ");
        string input = Console.ReadLine();
        byte[] data = Encoding.UTF8.GetBytes(input);
        stream.Write(data, 0, data.Length);

        byte[] buffer = new byte[1024];
        int bytesRead = stream.Read(buffer, 0, buffer.Length);
        string result = Encoding.UTF8.GetString(buffer, 0, bytesRead);

        Console.WriteLine("Kết quả từ server: " + result);

        client.Close();
    }
}
