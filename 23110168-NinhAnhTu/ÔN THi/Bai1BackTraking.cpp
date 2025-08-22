/*Liệt kê tất cả tập con (Subsets) – Dễ

Mô tả: Cho một mảng các số nguyên phân biệt, hãy liệt kê tất cả các tập con của nó.

Input: nums = [1, 2, 3]

Output: [[], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]]

Gợi ý: Dùng backtracking chọn hoặc không chọn mỗi phần tử.*/

#include<iostream>
using namespace std;

int backtraking1(int &nums, int n, int queery, int kq ){
    
    for(int i=0;i<n;i++){

    }
}

int main(){
    int n;
    int nums[100];
    int queery[100];
    int kq[100];
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    for(int i=0;i<n;i++){
        if(backtraking1){
            cout<<queery[i]<<" "<<endl;
        }
    }
    return 0;
}