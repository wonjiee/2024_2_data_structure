#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int data;
    Node *next;
};

Node *add_first(Node *p,int a){
    Node *tmp=new Node;
    tmp->data=a;
    tmp->next=p;
    return tmp;
}

int main() {
    vector<int> vals{1, 2, 3, 4};
    Node *a = nullptr;
    for (int d: vals) {
        a = add_first(a, d);
    }
    Node *p = a;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
    vals = {9, 8, 7, 6};
    Node *b = nullptr;
    for (int d: vals) {
        b = add_first(b, d);
    }
    p = b;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}