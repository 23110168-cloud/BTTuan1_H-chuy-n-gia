#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Hàm đọc file
void ReadFile(int mat[][100], int &numVertices, int &vertex)
{
    fstream fi;
    fi.open("matranbai3.txt");
    fi >> numVertices;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            fi >> mat[i][j];
        }
    }
    fi >> vertex;
    fi.close();
}

// Hàm nhập ma trận
void Input(int mat[][100], int numVertices)
{
    cout << "Nhap ma tran:" << endl;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            cin >> mat[i][j];
        }
    }
}

// Hàm in ma trận
void Print(int mat[][100], int numVertices, int vertex)
{
    cout << "Input tu file text la: " << endl;
    cout << "So dinh: " << numVertices << endl;
    cout << "Ma tran:" << endl;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Dinh duoc nhap de kiem tra la: " << vertex << endl;
}

// Kiểm tra cạnh song song
void CheckParallel(int mat[][100], int numVertices)
{
    bool hasParallelEdge = false;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = i + 1; j < numVertices; j++)
        {
            if (mat[i][j] > 1)
            {
                cout << "Cap dinh co canh song song: " << i << " - " << j << endl;
                hasParallelEdge = true;
            }
        }
    }
    if (!hasParallelEdge)
    {
        cout << "Khong co canh song song trong do thi." << endl;
    }
}

// Kiểm tra cạnh vòng
void CheckLoop(int mat[][100], int numVertices)
{
    bool hasLoop = false;
    for (int i = 0; i < numVertices; i++)
    {
        if (mat[i][i] > 0)
        {
            cout << "Dinh co vong: " << i << endl;
            hasLoop = true;
        }
    }
    if (!hasLoop)
    {
        cout << "Khong co dinh co vong trong do thi." << endl;
    }
}

// Kiểm tra đỉnh treo
void CheckHangingVertices(int mat[][100], int numVertices)
{
    bool hasHangingVertex = false;
    for (int i = 0; i < numVertices; i++)
    {
        int deg = 0;
        for (int j = 0; j < numVertices; j++)
        {
            deg += mat[i][j];
        }
        if (deg == 1 && !mat[i][i]==1)
        {
            cout << "Dinh treo: " << i << endl;
            hasHangingVertex = true;
        }
    }
    if (!hasHangingVertex)
    {
        cout << "Khong co dinh treo trong do thi." << endl;
    }
}

// Kiểm tra đỉnh cô lập
void CheckIsolatedVertices(int mat[][100], int numVertices)
{
    bool hasIsolatedVertex = false;
    for (int i = 0; i < numVertices; i++)
    {
        int deg = 0;
        for (int j = 0; j < numVertices; j++)
        {
            deg += mat[i][j];
        }
        if (deg == 0)
        {
            cout << "Dinh co lap: " << i << endl;
            hasIsolatedVertex = true;
        }
    }
    if (!hasIsolatedVertex)
    {
        cout << "Khong co dinh co lap trong do thi." << endl;
    }
}

// Kiểm tra có cạnh vòng tại đỉnh
bool HasLoopAtVertex(int mat[][100], int numVertices, int vertex)
{
    return mat[vertex][vertex] > 0;
}

// Hàm tính bậc của một đỉnh
int DegreeOfVertex(int mat[][100], int numVertices, int vertex)
{
    int deg = 0;
    if (HasLoopAtVertex(mat, numVertices, vertex))
    {
        deg += mat[vertex][vertex];
    }
    for (int j = 0; j < numVertices; j++)
    {
        deg += mat[vertex][j];
    }
    return deg;
}

int main()
{
    int numVertices, vertex;
    int mat[100][100];
    ReadFile(mat, numVertices, vertex);
    Print(mat, numVertices, vertex);
    CheckParallel(mat, numVertices);
    CheckLoop(mat, numVertices);
    CheckHangingVertices(mat, numVertices);
    CheckIsolatedVertices(mat, numVertices);
    cout << "Bac cua dinh " << vertex << " la: " << DegreeOfVertex(mat, numVertices, vertex);
    return 0;
}
