#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int *n=new int;
    cin >> *n;
    int *data=new int[*n];
    int *value=new int;
    int *MaxNum=new int;
    int *MinNum=new int;
    double *Average = new double(0.0);
    int *i=new int;
    for(*i=0;*i<*n;(*i)++){
        cin>>*value;
        data[*i]=*value;
        if (*i==0){
            *MaxNum=*value;
            *MinNum=*value;
        }
        else {
            if (*MaxNum <= *value) {
                *MaxNum = *value;
            }
            if (*MinNum >= *value)
                *MinNum = *value;
        }
        *Average+=*value;
    }
    *Average=*Average/(*n);

    double *deviation=new double;
    double *sumdeviation = new double(0.0);
    for (*i=0;*i<*n;(*i)++){
        *deviation=data[*i]-*Average;
        *sumdeviation+=(*deviation)*(*deviation);
    }
    cout<<*MinNum<<" "<<*MaxNum<<" "<<*Average<<" "<<sqrt(*sumdeviation/(*n));
    return 0;
}
