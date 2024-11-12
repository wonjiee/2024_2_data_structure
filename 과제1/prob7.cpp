#include <iostream>

using namespace std;

int main(){
    int n;
    cin>>n;
    int tmp=n;
    int *data=new int[n];
    for(int i=2;i<=n;i++)
    {
        data[i-2]=i;
    }
    for(int i=2;i<=n/2+1;i++){
        for(int j=0;j<=n-2;j++)
        {
            if(data[j]%i==0 && data[j]!=i) {
                for (int k = j; k < n - 2; k++) {
                    data[k] = data[k + 1];
                }
                n--;
            }
        }

    }



    for(int i=2;i<=n;i++)
        cout<<data[i-2]<<" ";
    cout<<n;


}