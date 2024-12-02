#include <iostream>

using namespace std;

void find_hamming_distance_2(string num, int n,int index,int flip){
    if (flip==n) {
        cout << num<<endl;
        return;
    }
    if(index>num.length()-1)
        return;
    num[index]=(num[index]=='0')?'1':'0';
    find_hamming_distance_2(num,n,index+1,flip+1);

    num[index]=(num[index]=='0')?'1':'0';
    find_hamming_distance_2(num,n,index+1,flip);
}


int main(){
    string num;
    int n;
    cin>>num>>n;
    find_hamming_distance_2(num,n,0,0);

}