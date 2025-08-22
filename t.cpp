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