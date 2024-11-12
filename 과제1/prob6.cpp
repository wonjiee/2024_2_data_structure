#include <iostream>
#include <string>

using namespace std;

void eraseblank(string &data){
    while(data[0]==' ')
        data.erase(0,1);

}
int findword(string data){
    int n=0;
    eraseblank(data);
    while(data[data.length()-1]==' ')
        data.erase(data.length()-1,1);
    if (data.find(' ')==-1)
        return 1;
    while(data.find(' ')!=-1){
        int tmp=data.find(' ');
        n++;
        data.erase(0,tmp+1);
        eraseblank(data);
        if(data.find(' ')==-1)
            n++;
    }
    return n;
}
int main(){
    string command;
    while(command!="exit"){
        cout<<"$ ";
        getline(cin,command);
        int n=findword(command);
        cout<<command<<":"<<command.length()<<":"<<n<<endl;
    }
}