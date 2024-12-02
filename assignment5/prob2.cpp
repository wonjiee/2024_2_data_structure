#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename Cont> class Stack{
private:
    Cont c;
public:
    typedef typename Cont::value_type value_type;
    bool empty() {
        return c.empty();
    }
    int size() {
        return c.size();
    }
    value_type &top() {
        return c.back();
    }
    void push(value_type x){
        c.push_back(x);
    }
    void pop() {
        c.pop_back();
    }
};

int main() {
    int N;
    Stack<vector<int>> data;
    Stack<vector<int>> data_next;
    cin>>N;
    for(int i=0;i<N;i++){
        int num;
        cin>>num;
        while(!data.empty()) {
            if (data.top() > num)
                data_next.push(data.top());
            data.pop();
        }
        data_next.push(num);
        cout<<data_next.size()<<" ";
        data=data_next;
        data_next=Stack<vector<int>>();
    }
    return 0;
}
