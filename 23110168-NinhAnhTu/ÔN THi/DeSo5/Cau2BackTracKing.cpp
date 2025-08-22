#include<iostream>
#include<vector>

using namespace std;

void sinhNhiphan(int n, vector<int> &a, int i){
    if(i==n){
        for(int bit : a) cout<<bit; 
        cout<<endl;
        return;
    }
    for(int j=0;j<=1;j++){
        a[i]=j;
        sinhNhiphan(n,a,i+1);
    }
}

int main(){
    int n; cin >>n;
    
}