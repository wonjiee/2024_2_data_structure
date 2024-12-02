#include <iostream>
#include <string>
#include <vector>

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
    string num_s;
    int erase_n;
    cin >> num_s >> erase_n;
    Stack<vector<int>> data;
    int num_size = num_s.length();

    int i=0;
    int erase=0;
    while (i<num_size) {
        if (data.empty()) {
            data.push(int(num_s[i]) - '0');
            i++;
            continue;
        } else {
            if ((int(num_s[i]) - '0') < data.top()) {
                data.push(int(num_s[i]) - '0');
            } else if ((int(num_s[i]) - '0') == data.top()) {
                data.push(int(num_s[i]) - '0');
            } else {
                while((int(num_s[i]) - '0') > data.top()) {
                    if(data.empty() || erase>=erase_n)
                        break;
                    data.pop();
                    erase++;
                }
                data.push(int(num_s[i]) - '0');
            }
        }
        i++;
        if(erase==erase_n)
            break;
    }

    if(data.size()>num_size-erase_n)
        while(data.size()!=num_size-erase_n)
            data.pop();
    else
        for(;i<num_size;i++)
            data.push(int(num_s[i])-'0');

    Stack<vector<int>>result;

    while(!data.empty()) {
        result.push(data.top());
        data.pop();
    }
    while(!result.empty()) {
        cout << result.top();
        result.pop();
    }
    return 0;
}