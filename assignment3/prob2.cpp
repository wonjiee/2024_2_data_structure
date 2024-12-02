#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    string word;
    int n;
    Node *next=nullptr;
};

Node *head=nullptr;

void read_file(){
    ifstream infile("harry.txt");
    string s;
    while(infile>>s) {
        Node *p = new Node;
        Node *q = head;
        Node *r = nullptr;
        p->word = s, p->n = 1;
        if (head == nullptr) {
            head = p;
            continue;
        }
        while (q!= nullptr) {
            if (q->word == s) {
                q->n++;
                delete p;
                break;
            }
            r=q;
            q=q->next;
        }
        if(q==nullptr && r->word!=s){
            r->next=p;
        }

    }
}

void sort_words(){
    Node *q=head;
    if(q==nullptr || q->next==nullptr)
        return;
    while(q->next!=nullptr){
        Node *p=q->next;
        while(p!=nullptr){
            if(q->word > p->word) {
                Node *tmp=new Node;
                tmp->word = p->word, tmp->n = p->n;
                p->word=q->word, p->n=q->n;
                q->word=tmp->word,q->n=tmp->n;
                delete tmp;
            }
            p=p->next;
        }
        q=q->next;
    }
}

int del_low_word(){
    Node *p=head;
    int n=0;
    Node *q =p;
    while(p!=nullptr){
        if(p!=nullptr && p->n<=10) {
            Node *tmp=p;
            q->next = p->next;
            p=p->next;
            delete tmp;
            continue;
        }
        q=p;
        p=p->next;
        n++;
    }
    if(head->n<=10) {
        Node *tmp = head;
        head = head->next;
        delete tmp;
    }
    return n;
}

Node *sort_nums() {
    Node *sorted = nullptr;

    while (head != nullptr) {
        Node *current = head;
        head = head->next;

        // 정렬된 리스트에 현재 노드를 삽입할 위치 찾기
        if (sorted == nullptr || current->n > sorted->n ||
            (current->n == sorted->n && current->word < sorted->word)) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            // 현재 노드를 삽입할 위치를 찾음
            while (temp->next != nullptr &&
                   (temp->next->n > current->n ||
                    (temp->next->n == current->n && temp->next->word < current->word))) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
    return sorted;
}



void print_list(Node *data){
    Node *p=data;
    while(p!=nullptr){
        cout<<p->word <<" "<<p->n<<endl;
        p=p->next;
    }
}
int main(){
    //1
    read_file();
    sort_words();
    print_list(head);
    cout<<endl;
    //2
    int num=del_low_word();
    print_list(head);
    cout<<num<<endl;
    cout<<endl;
    //3
    Node *final=sort_nums();
    print_list(final);
    cout<<num<<endl;


}
