#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n; cin>>n;
    vector<pair<int, int>> M(n);
    for(int i=0;i<n;i++){
        cin >> M[i].first >> M[i].second; 
    } 
    sort(M.begin(), M.end(),[](auto &a,auto &b){
        return a.second < b.second;
    });
    int count = 0;
    int countEnd=-1;
    for(auto &m:M){
        if(m.first>=countEnd){
            count++;
            countEnd=m.second;
        }
    }
    cout<<count<<endl;
    return 0;

}