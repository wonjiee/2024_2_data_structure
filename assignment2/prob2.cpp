#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(){
    int num;
    vector<int>numbers;
    cin>>num;
    for(int i=2;i<=num;i++){
        numbers.push_back(i);
    }
    int n;
    for(n=2;n<=sqrt(num);n++) {
        auto it=numbers.begin();
        while (it!=numbers.end()) {
            if (*it!=n && *it%n==0){
                it = numbers.erase(it);
            }
            else
                it++;
        }
    }
    for(auto a:numbers)
        cout<<a<<" ";
    cout<<endl;
    return 0;

}