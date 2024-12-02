#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Words{
public:
    string name;
    int n;
};

void sortdata(vector<Words>&data){
    for(int i=0;i<data.size();i++){
        for(int j=i+1;j<data.size();j++)
        {
            if (data[j].name<data[i].name){
                Words tmp=data[j];
                data[j]=data[i];
                data[i]=tmp;
            }
        }
    }

}
void delblank(string & data){
    while (data[0]==' ' )
        data.erase(0,1);
    while (data[data.length()-1]==' ')
        data.erase(data.length()-1,1);

}
void delspecialchar(string &data) {
    int n;
    int datasize=data.size();
    while (isalpha(data[0]) == 0) {
        data.erase(0, 1);
        n++;
        if (n==datasize)
            break;
    }
    while (isalpha(data[data.length() - 1]) == 0) {
        data.erase(data.length() - 1, 1);
        if (n==datasize)
            break;
    }
}

void insertword(vector<Words>&data,string &word) {
    int n = 0;
    for (int i = 0; i < data.size(); i++)
        if (word == data[i].name) {
            n++;
            data[i].n++;
            break;
        }
    if (n == 0 && word.length() > 1) {
        Words tmp;
        tmp.name = word;
        tmp.n = 1;
        data.push_back(tmp);
    }
}


int main(){
    string line;
    string word;
    vector<Words>data;
    int n;
    int brk=0;
    ifstream infile("input4.txt");
    while(getline(infile,line)) {
        if (line.length()<2)
            continue;
        brk=0;
        delblank(line);
        while (brk==0) {
            n = line.find(' ');
            word = line.substr(0, n);
            delspecialchar(word);
            line.erase(0, n+1);
            if (word.length()>1) {
                insertword(data,word);
            }
            if (line.find(' ') == -1|| line.length()<2) {
                delspecialchar(line);
                insertword(data,line);
                brk=1;
            }
        }
    }
    sortdata(data);
    for(int i=0;i<data.size();i++)
        cout<<data[i].name<<" "<<data[i].n<<endl;
    return 0;
}