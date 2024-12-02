#include <vector>
#include <string>
#include <iostream>
using namespace std;


void SortWords(vector<string>&data){
    for(int i=0;i<data.size();i++){
        for(int j=i+1;j<data.size();j++){
            if (data[i]>data[j])
                swap(data[i],data[j]);
        }
    }
}
void FindWords(vector<string>&data,string &word){
    auto it=data.begin();
    while(it!=data.end()&&*it!=word)
        it++;
    if (it==data.end()){
        data.push_back(word);
    }
    else data.erase(it);
    SortWords(data);
}

int main(){
    string word;
    vector<string>words;
    cin>>word;

    words.push_back(word);
    if (word!="exit")
        cout<<words[0]<<endl;

    while(1){
        cin>>word;
        if(word=="exit")
            break;
        FindWords(words,word);
        for(int i=0;i<words.size();i++)
            cout<<words[i]<<" ";
        cout<<endl;
    }
    return 0;
}