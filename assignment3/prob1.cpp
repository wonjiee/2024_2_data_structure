#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    int x, y, w, h;
    Node *next;
};

Node *head = nullptr;

void print_list()
{
    Node *p = head;
    while(p!=nullptr) {
        cout << p->x << " " << p->y << " " << p->w << " " << p->h << endl;
        p = p->next;
    }
}
void read_file() {
// rects.txt 파일을 읽어서 사각형들을 파일에 저장된 순서대로
// head가 가리키는 연결리스트에 저장한다.
    ifstream infile("rects.txt");
    int num;
    infile >> num;
    Node *p = nullptr;
    for (int i = 0; i < num; i++) {
        Node *tmp = new Node;
        infile >> tmp->x >> tmp->y >> tmp->w >> tmp->h;
        if (i == 0) {
            head = tmp;
            p = tmp;
        } else {
            p->next = tmp;
            p = p->next;
        }
    }
}
void sort_by_area() {
    Node *p=head;
    if(p== nullptr)
        return;
    Node *q=head;
    while(q->next!=nullptr) {
        p=q;
        while (p!= nullptr) {
            if(p->w*p->h < q->w*q->h){
                Node *tmp=new Node;
                tmp->x=q->x,tmp->y=q->y,tmp->w=q->w,tmp->h=q->h;
                q->x=p->x,q->y=p->y,q->w=p->w,q->h=p->h;
                p->x=tmp->x,p->y=tmp->y,p->w=tmp->w,p->h=tmp->h;
                delete tmp;
            }
            p=p->next;
        }
        q=q->next;
    }
// head가 가리키는 연결리스트를 면적순으로 정렬한다.
    return;
}

void remove_rects(int min_w,int min_h){
    Node *p=head;
    while(p->next!=nullptr){
        if(p->next->w< min_w || p->next->h < min_h) {
            Node *tmp= p->next;
            p->next=p->next->next;
        }
        else
            p=p->next;
    }
    if(head->w <min_w || head->h < min_h) {
        Node *tmp = head;
        head = head->next;
        delete tmp;
    }
}
int main() {
// (1)
    read_file(); // 파일을 읽어서 파일에 저장된 순서대로 저장된 연결리스트를 구성한다.
    print_list(); // 파일에 저장된 순서대로 출력된다.
    cout << endl; // 한 줄을 띄운다.
// (2)
    sort_by_area(); // 연결리스트의 노드들을 면적순으로 정렬한다.
    print_list(); // 정렬된 순서대로 출력한다.
    cout << endl; // 한 줄을 띄운다.
// (3)
    int min_w, min_h;
    cin >> min_w >> min_h;
    remove_rects(min_w, min_h);
    print_list();
    return 0;
}