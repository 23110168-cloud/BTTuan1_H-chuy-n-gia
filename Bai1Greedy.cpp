#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

/*Hàm xắp xếp hoạt động theo thời gian kết thúc tăng dần:
Nếu thời gian hoạt động của a (a[1]) nhỏ hơn thời gian hoạt động của b (b[1]) thì xếp a trước b.
Hàm in danh sách hoạt động:
Duyệt từ đầu đến cuối của danh sách đã chọn và in ra.
Hàm chọn các hoạt động tối đa
Tạo danh sách lưu hoạt động: thêm các phần tử trong mảng start và end vào danh sách arr
Sắp xếp theo thời gian kết thúc
Tạo biến đếm totalActivity để đếm các hoạt động để chọn 
Ghi nhận thời gian kết thúc của hoạt động đầu tiên để làm mốc so sánh 
Luôn chọn hoạt động đầu tiên và thêm nó vào danh sách chọn activities
Duyệt qua các hoạt động còn lại 
Nếu thời gian thực hiện của hoạt động arr[i][0] lớn hơn endValue hiện tại (arr[0][1])
Cập nhật endValue là thời gian kết thúc của hoạt động đang xét
Tăng biến đếm và thêm nó vào danh sách hoạt động đã chọn
*/
bool xapxep(vector<int>& a, vector<int>& b){
    return a[1]< b[1];
}

void in(vector<pair<int,int>>& activities){
    '\n';
    for(auto activiti: activities){
        cout << activiti.first<<","<<activiti.second<<endl;
    }
}

int xuly(vector<int>start, vector<int> end, int n, vector<pair<int,int>>& activities){
    vector<vector<int>> arr;
    for(int i=0;i<n;i++){
        arr.push_back({start[i],end[i]});
    }
    sort(arr.begin(),arr.end(),xapxep);
    int tong=1;
    int endvalue = arr[0][1];
    activities.push_back({arr[0][0], arr[0][1]});
    for(int i=1;i<n;i++){
        if(arr[i][0]>=endvalue){
            endvalue=arr[i][1];
            tong++;
            activities.push_back({arr[i][0], arr[i][1]});
        
    }
}
    return tong; 
}

int main(){
    vector<int> start={10,12,20};
    vector<int> end={20,25,30};
    int n=start.size();
    vector<pair<int,int>> activities;
    int kq=xuly(start,end,n,activities);
    cout <<"Tong hoat dong: "<<kq<<endl;
    in(activities);
    return 0;
}
