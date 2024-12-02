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
    string line;
    Stack<vector<int>> data;
    int code=1;
    cin>>line;
    for(int i=0;i<line.size();i++) {
        if (line[i] == '(') {
            data.push(code);
            cout<<code<<" ";
            code++;
        }
        if (line[i] == ')') {
            cout<<data.top()<<" ";
            data.pop();
        }
    }
    return 0;
}
