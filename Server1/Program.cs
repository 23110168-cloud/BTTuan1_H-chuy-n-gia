using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using Newtonsoft.Json;

class Server
{
    static double[,] NhanHaiMaTran(double[,] MT1, double[,] MT2)
    {
        int row1 = MT1.GetLength(0), col1 = MT1.GetLength(1);
        int row2 = MT2.GetLength(0), col2 = MT2.GetLength(1);
        
        if (col1 != row2)
        {
            throw new Exception("Lỗi: Không thể nhân hai ma trận có kích thước không phù hợp.");
        }
        
        double[,] result = new double[row1, col2];
        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < col2; j++)
            {
                for (int k = 0; k < col1; k++)
                {
                    result[i, j] += MT1[i, k] * MT2[k, j];
                }
            }
        }
        return result;
    }

    static void Main()
    {
        IPAddress ip = IPAddress.Parse("127.0.0.1");
        int port = 1002;
        TcpListener server = new TcpListener(ip, port);
        server.Start();
        Console.WriteLine("Server đang chờ kết nối...");

        while (true)
        {
            TcpClient client = server.AcceptTcpClient();
            Console.WriteLine("Kết nối từ client!");
            NetworkStream stream = client.GetStream();
            byte[] buffer = new byte[4096];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);
            string data = Encoding.UTF8.GetString(buffer, 0, bytesRead);
            
            try
            {
                var matrices = JsonConvert.DeserializeObject<dynamic>(data);
                double[,] MT1 = JsonConvert.DeserializeObject<double[,]>(matrices.MT1.ToString());
                double[,] MT2 = JsonConvert.DeserializeObject<double[,]>(matrices.MT2.ToString());
                
                double[,] result = NhanHaiMaTran(MT1, MT2);
                string jsonResult = JsonConvert.SerializeObject(result);
                byte[] response = Encoding.UTF8.GetBytes(jsonResult);
                stream.Write(response, 0, response.Length);
            }
            catch (Exception ex)
            {
                byte[] errorResponse = Encoding.UTF8.GetBytes(ex.Message);
                stream.Write(errorResponse, 0, errorResponse.Length);
            }

            client.Close();
        }
    }
}
