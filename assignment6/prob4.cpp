#include <iostream>

using namespace std;

const int MAX_SIZE = 1000;

int floor(int data[],int K,int N,int n,int num){
    if(n>=N)
        return num;
    if(data[n]>=num && data[n]<=K) {
        return floor(data, K,N, n + 1,data[n]);
    }
    else
        return floor(data,K,N,n+1,num);
}

int ceiling(int data[], int K, int N, int n, int num) {
    if (n >= N)
        return num;

    if (data[n] >= K && (num == -1 || data[n] <= num))
        return ceiling(data, K, N, n + 1, data[n]);
    else
        return ceiling(data, K, N, n + 1, num);
}

int main(){
    int K,N;
    cin>>N;
    int data[MAX_SIZE];
    for(int i=0;i<N;i++)
        cin>>data[i];
    cin>>K;
    cout<<floor(data,K,N,0, -1)<<endl;
    cout<<ceiling(data,K,N,0,-1)<<endl;
}