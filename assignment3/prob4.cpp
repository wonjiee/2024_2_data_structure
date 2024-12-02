#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    Node *prev, *next;
};
void ordered_insert(string item);
void remove_dup();
void print_list_twice();

Node *head = nullptr, *tail = nullptr; /* 2중 연결리스트의 처음과 마지막 노드 */

int main() {
    int n;
    string word;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> word;
        ordered_insert(word);
    }
    print_list_twice();
    remove_dup();
    print_list_twice();
    return 0;
}

void ordered_insert(string item) {
/* head와 tail이 가리키는 2중 연결리스트에 문자열들이 사전식 순서로 정렬된 순서를 유지하
도록 새로운 문자열 item을 삽입한다. */
    Node *i = new Node;
    i->data = item;
    if (head == nullptr) {
        head = i;
    }
    else if (tail == nullptr) {
        if (item > head->data) {
            head->next = i;
            head->prev = nullptr;
            i->prev = head;
            i->next = nullptr;
            tail = i;
        } else {
            tail = head;
            i->next = tail;
            i->prev = nullptr;
            tail->prev = i;
            tail->next = nullptr;
            head = i;
        }
    }
    else {
        Node *p = head;
        while (p != tail && p->data < item) {
            p = p->next;
        }
        if (p == tail) {
            if(item>p->data) {
                p->next = i;
                i->prev = p;
                i->next = nullptr;
                tail = i;
            }
            else {
                Node *tmp = p->prev;
                tmp->next = i;
                i->next = p;
                i->prev = tmp;
                p->prev = i;
                p->next = nullptr;
            }
        } else {
            if (p != head) {
                Node *tmp = p->prev;
                p->prev = i;
                i->next = p;
                i->prev = tmp;
                tmp->next = i;
            } else {
                i->next = p;
                p->prev = i;
                i->prev = nullptr;
                head = i;
            }
        }

    }
}

void remove_dup() {
/* 2중 연결리스트에 저정된 문자열들 중에서 모든 중복된 문자열을 찾아 하나만 남기고 제거한
다. */
    Node *p=head;
    while(p->next!=nullptr){
        if(p->data==p->next->data) {
            Node *tmp = p->next;
            p->next = p->next->next;
            delete tmp;
            if(p->next==nullptr) {
                tail = p;
                return;
            }
            p->next->prev = p;
        }
        else
            p=p->next;
    }

}
void print_list_twice() {
    Node *p = head;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
    Node *q = tail;
    while (q != nullptr) {
        cout << q->data << " ";
        q = q->prev;
    }
    cout << endl;
}