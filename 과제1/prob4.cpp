#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void delblank(string & data){
    while (data[0]==' ' )
        data.erase(0,1);
    while (data[data.length()-1]==' ')
        data.erase(data.length()-1,1);
}

void insertword(vector<string>&words,string &word){
    int n=0;
    for(int i=0;i<words.size();i++)
        if (word==words[i]){
            n=1;
            break;
        }
    if(n==0)
        words.push_back(word);
}

int main(){
    string line;
    string word;
    vector<string>words;
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
            if (word.length()>1) {
                insertword(words,word);
            }
            line.erase(0, n+1);
            if (line.find(' ') == -1) {
                insertword(words,line);
                brk=1;
            }
        }
    }
    for(auto a:words){
        cout<<a<<endl;
    }
    return 0;
}