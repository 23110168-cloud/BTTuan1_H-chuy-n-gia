//Bài 2: Coloring problem
#include <iostream>
using namespace std;

//Số lượng đỉnh trong đồ thị
const int V = 4;

void printSolution(int color[]);

//Hàm kiểm tra điều kiện
bool isSafe(int v, bool graph[V][V], int color[], int c)
{
    for (int i = 0; i < V; i++)

    //Nếu có cạnh nối và màu trùng 
        if (graph[v][i] && c == color[i])
            return false;

    return true;
}

//Hàm tô màu
bool graphColoringUtil(bool graph[V][V], int m, int color[], int v)
{
    //Nếu đã tô màu xong cho tất cả các đỉnh
    if (v == V)
        return true;

    for (int c = 1; c <= m; c++)
    {//Thử màu 1 đến màu m
        //Gọi hàm kiểm tra => Nếu thỏa => Gán màu cho đỉnh v
        if (isSafe(v, graph, color, c))
        {
            //Gán màu
            color[v] = c;

            //Đê quỵ kiểm tra đỉnh kế tiếp
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;
            
            //Quay lui nếu không tìm thấy lời giải
            color[v] = 0;
        }
    }
       return false;
}

bool graphColoring(bool graph[V][V], int m)
{
    int color[V]; //Mảng lưu màu của các đỉnh
    for (int i = 0; i < V; i++)
        color[i] = 0;

    //Gọi hàm tô màu bắt đầu từ đỉnh 0
    if (graphColoringUtil(graph, m, color, 0) == false)
    {
        //Nếu false => Noooo
        cout << "Noooo";
        return false;
    }

    //Gọi hàm in
    printSolution(color);
    return true;
}

//Hàm in lời giải
void printSolution(int color[])
{
    cout << "Loi giai: "<<endl;
    for (int i = 0; i < V; i++)
        cout << " " << color[i] << " ";

    cout << "\n";
}

int main()
{

    /* Minh họa đồ thị 
    (3)---(2)
    | / |
    | / |
    | / |
    (0)---(1)
    */
    bool graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };

    //Số màu
    int m = 3;

    //Gọi hàm
    graphColoring(graph, m);
    return 0;
}