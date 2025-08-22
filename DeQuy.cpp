// Đệ quy tuyến tính
// VD: Tính n!
/*#include <iostream>
using namespace std;

int n;
int DeQuyTT(int n)
{
    if (n == 0)
        return 1;
    return n * DeQuyTT(n - 1);
}

int main()
{
    cin >> n;
    cout << DeQuyTT(n) << endl;
    return 0;
}*/
// Đệ quy nhị phân (Binary)
// VD: Tính số Fibonaci thứ n
/*#include <iostream>
using namespace std;

int Fibonaci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return Fibonaci(n - 1) + Fibonaci(n - 2);
}

int main()
{
    int n;
    cin >> n;
    cout << Fibonaci(n) << endl;
    return 0;
}*/
// Đệ quy lồng nhau 

// Hệ nhị phân 
#include <iostream>

using namespace std;

void dec_to_bin(long long n){
   if(n < 2){
      printf("%d", n);
   }
   else{
      dec_to_bin(n / 2);
      cout << n % 2;
   }
}

int main(){
   cout << "37 = "; dec_to_bin(37);
   cout << endl;
   cout << "282828282828 = "; dec_to_bin(282828282828);
   return 0;
}