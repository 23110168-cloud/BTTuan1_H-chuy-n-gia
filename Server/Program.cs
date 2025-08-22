using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class Server
{
    static string GiaiPT(double a, double b, double c)
    {
        if (a == 0)
        {
            return "Không phải phương trình bậc hai.";
        }
        
        double delta = b * b - 4 * a * c;
        if (delta > 0)  
        {
            double x1 = (-b + Math.Sqrt(delta)) / (2 * a);
            double x2 = (-b - Math.Sqrt(delta)) / (2 * a);
            return $"Nghiệm x1 = {x1}, x2 = {x2}";
        }
        else if (delta == 0)
        {
            double x = -b / (2 * a);
            return $"Nghiệm kép x = {x}";
        }
        else
        {
            return "Phương trình vô nghiệm.";
        }
    }

    static void Main()
    {
        IPAddress ip = IPAddress.Parse("127.0.0.1");
        int port = 1001;
        TcpListener server = new TcpListener(ip, port);
        server.Start();
        Console.WriteLine("Server đang chờ kết nối...");

        while (true)
        {
            TcpClient client = server.AcceptTcpClient();
            Console.WriteLine("Kết nối thành công từ client!");
            NetworkStream stream = client.GetStream();
            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);
            string data = Encoding.UTF8.GetString(buffer, 0, bytesRead);

            string[] parts = data.Split(' ');
            double a = double.Parse(parts[0]);
            double b = double.Parse(parts[1]);
            double c = double.Parse(parts[2]);

            string result = GiaiPT(a, b, c);
            byte[] response = Encoding.UTF8.GetBytes(result);
            stream.Write(response, 0, response.Length);

            client.Close();
        }
    }
}
