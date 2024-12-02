#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Point2D {
    int x, y;
};

void add_to_array(int &i,Point2D *&data,int &capacity){
    capacity=capacity*2;
    Point2D *tmp = new Point2D[capacity];
    for(int j=0;j<i;j++){
        (*(tmp+j)).x=(*(data+j)).x;
        (*(tmp+j)).y=(*(data+j)).y;
    }
    delete[] data;
    data=tmp;

}

int main(){
    ifstream infile("input2.txt");
    int n=0;
    int num;
    int tmp=0;
    int capacity=4;
    Point2D *data = new Point2D[capacity];
    int i=-1;
    while(infile>>num) {
        if (i == -1) {
            n = num;
            i++;
        } else {
            if (tmp == 0) {
                (*(data + i)).x = num;
                tmp++;
            } else {
                (*(data + i)).y = num;
                tmp = 0;
                i++;
            }
        }
        if (i == capacity)
            add_to_array(i, data, capacity);
    }
    int j;
    int k;
    double value1;
    double value2;
    double distance;
    Point2D coord1;
    Point2D coord2;
    int value=-1;
    for(j=0;j<i;j++){
        for (k=j+1;k<=i;k++)
        {
            value1=((*(data+j)).x-(*(data+k)).x)*((*(data+j)).x-(*(data+k)).x);
            value2=((*(data+j)).y-(*(data+k)).y)*((*(data+j)).y-(*(data+k)).y);
            if (value1+value2>=value) {
                coord1.x = (*(data + j)).x;
                coord1.y = (*(data + j)).y;
                coord2.x = (*(data + k)).x;
                coord2.y = (*(data + k)).y;
                distance = sqrt(value1+value2);
                value=value1+value2;
            }
        }
    }
    cout<<coord1.x<<" "<<coord1.y<<endl;
    cout<<coord2.x<<" "<<coord2.y<<endl;
    cout<<distance;
    return 0;


}
