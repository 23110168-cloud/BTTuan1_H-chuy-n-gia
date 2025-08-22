/*
Cách tiếp cận hướng đến Giải pháp: Trong câu hỏi này, bạn không cần biết gì về cổ phiếu, cách tiếp cận mà chúng tôi cung cấp đủ dễ hiểu ngay cả với người mới bắt đầu. Bây giờ, khá rõ ràng rằng khi bạn muốn mua bất cứ thứ gì, bạn muốn trả mức giá thấp nhất có thể. Tương tự như vậy, khi bán cùng một thứ, bạn sẽ muốn tăng lợi nhuận bằng cách bán nó với giá cao hơn. Do đó, bạn tham lam muốn tăng lợi nhuận của mình. Vì vậy, chúng ta hãy xem bạn sẽ làm gì với câu hỏi này:

Ở đây, sắp xếp sẽ không hiệu quả vì bạn phải cung cấp số ngày. Vì vậy, trước tiên bạn sẽ tìm giá trị nhỏ nhất của cổ phiếu từ  prices[] . 
Chỉ số có giá trị nhỏ nhất sẽ là ngày bạn mua cổ phiếu. 
Để bán cổ phiếu, bạn phải kiểm tra giá trị của cổ phiếu vài ngày sau khi bạn mua cổ phiếu.
Do đó, chạy vòng lặp cho đến khi kết thúc bắt đầu từ  buyingDay và  tìm giá trị lớn nhất của cổ phiếu trong mảng còn lại.
Bây giờ, trừ giá trị của  buyingDay  khỏi  sellingDay và voila! Bạn đã có câu trả lời! 
Ví dụ:

Đầu vào:  {7,1,5,3,6,4}

Đầu ra:  5
*/

#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n;
    vector<int> a={7,1,5,3,6,4};
    pair<int,int> kq;
    int buyday;
    int sellingday;
    int giatrimua=INT_MAX;
    int giatriban=INT_MIN;
    for(int i=0; i<a.size();i++){
        if(a[i]<giatrimua){
            giatrimua=a[i];
            buyday=i+1;
        }
        if(giatriban<a[i]-giatrimua){
            giatriban=a[i]-giatrimua;
            sellingday=i+1;
            kq={buyday,sellingday};
        }
    }

    cout<<buyday<<endl;
    cout<<sellingday<<endl;
    cout<<giatriban;
    return 0;
}