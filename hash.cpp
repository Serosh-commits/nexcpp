#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int check(int num,vector<int>& a,int n,int i) {
        for(int j=0;j<i;j++) {
            if(a[j]==num) return 8;
        }
        return 0;
    }
    vector<vector<int>> hashFrequency(vector<int>& a,int n) {
        vector<vector<int>> p;
        int visited[100001]={0};
        int l=0;
        for(int i=0;i<n;i++) {
            int num=a[i];
            int b=check(num,a,n,i);
            if(b==8) continue;
            if(visited[num+50000]) continue;
            visited[num+50000]=1;
            int count=1;
            for(int j=i+1;j<n;j++) {
                if(a[j]==num) count++;
            }
            vector<int> entry;
            entry.push_back(num);
            entry.push_back(count);
            p.push_back(entry);
            l++;
        }
        return p;
    }
};

int main() {
    Solution sol;
    int n;
    cout<<"enter the number of elements"<<endl;
    cin>>n;
    vector<int> a(n);
    cout<<"enter the elements"<<endl;
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }
    vector<vector<int>> result=sol.hashFrequency(a,n);
    cout<<"the hashing completed"<<endl;
    for(int i=0;i<result.size();i++) {
        cout<<result[i][0]<<" "<<result[i][1]<<endl;
    }
    return 0;
}
