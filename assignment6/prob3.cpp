#include <iostream>

using namespace std;

const int MAX_SIZE = 1000;

int find_2_SUM(int k,int num[],int start, int end) {
    int sum = num[start] + num[end];
    if (start >= end)
        return 0;
    if (sum > k)
        return find_2_SUM(k, num, start, --end);
    else if (sum < k)
        return find_2_SUM(k, num, ++start, end);
    else
        return 1 + find_2_SUM(k, num, ++start, --end);
}

int main(){
    int k,n;
    cin>>n;
    int num[MAX_SIZE];
    for(int i=0;i<n;i++)
        cin>>num[i];
    cin>>k;
    cout<<find_2_SUM(k,num,0,n-1);
}