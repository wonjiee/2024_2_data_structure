#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Dictionary{
public:
    string word;
    string explanation;
};

void findWords(vector<Dictionary>&data) {
    string word;
    vector<string> words;
    cin >> word;
    int i;
    for (i = 0; i < data.size(); i++) {
        if (data[i].word == word) {
            cout << data[i].word << ": " << data[i].explanation << endl;
            break;
        }
    }
    vector<string> tokens;
    stringstream sstream(data[i].explanation);
    while (getline(sstream, word, ' ')) {
        words.push_back(word);
    }
    vector<string>duplicate;
    for (int j = 0; j < words.size(); j++) {
        for (int k = 0; k < data.size(); k++) {
            if (data[k].word == words[j] && words[j].length() > 2) {
                for(int q=0;q<duplicate.size();q++) {
                    if (words[j] == duplicate[q])
                        break;
                }
                cout << data[k].word << ": " << data[k].explanation << endl;
                duplicate.push_back(words[j]);
                break;
            }
        }
    }

}
int main(){
    string line;
    vector<Dictionary>data;

    ifstream infile("shuffled_dict.txt");
    while(getline(infile,line)){         //save data
        int n=line.find('\t');
        Dictionary tmp;
        tmp.word=line.substr(0,n);
        tmp.explanation=line.substr(n+1,line.size()-1);
        data.push_back(tmp);
    }

    findWords(data);


    infile.close();
    return 0;
}