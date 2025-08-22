#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int n, t, m;
double g = 0;
double k = INT_MAX, d = 0, e = 0;

struct ps
{
    int ts, ms;
};
ps a[101];
double b[102];
double c[103];
int main()
{
    cin >> n;
    double kq = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].ts >> a[i].ms;
        t = a[i].ts;
        m = a[i].ms;
        kq = (double)t / m;
        b[i] = kq;
    }
    sort(b, b + 1);
    for (int i = 0; i < n; i++)
    {
        g = abs(b[i] - b[i + 1]);
        c[i] = g;
        if (c[i] < k)
        {
            k = c[i];
            d = i;
            e = i + 1;
        }
    }
    cout << d << " " << e << endl;
    return 0;
}