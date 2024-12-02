#include <iostream>
#include <list>
#include <sstream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

int id_counter=0;

struct Artist;

struct Song{
    int index;
    string title,album,mv_url;
    Artist *artist;
    Song(){}
    Song(string ti, Artist *art,string alb,string mv):
            title(ti),artist(art),album(alb),mv_url(mv) {
        index = id_counter++;
    }
};

struct Artist {
    string name;
    list<Song *> songs;
    Artist(){}
    Artist(string name):name(name){}
};

list<Artist *> artist_directory[256];

const int SONG_DIRECTORY_SIZE=10;
list<Song *> song_directory[SONG_DIRECTORY_SIZE];

const string datafilename = "songs.csv";

string trim(string str){
    int s = 0, t = str.length()-1;;
    while(s<str.length() && isspace(str[s]))
        s++;
    while(t>=0 && isspace(str[t]))
        t--;
    if(s<=t)
        return str.substr(s,t-s+1);
    else
        return "";
}

vector<string>split_line(string &line,char delimiter){
    vector<string>tokens;
    string str;
    stringstream sstream(line);
    while(getline(sstream,str,delimiter))
        tokens.push_back(trim(str));
    return tokens;
}

Artist *find_artist(string name) {
    list<Artist *> artist_list = artist_directory[(unsigned char)name[0]];
    for (auto it=artist_list.begin(); it!=artist_list.end(); it++) {
        if ((*it)->name == name)
            return *it;
    }
    return nullptr;
}
void print_artist(Artist *p) {
    cout << p->name << ":" << endl;
    for (auto s: p->songs) {
        cout << " " << s->index << ":" << s->title << ", " << s->album <<
             ", " << s->mv_url << endl;
    }
}

void find_print_artist(string key){
    list<Artist *> artist_list = artist_directory[(unsigned char)key[0]];
    for (auto it=artist_list.begin(); it!=artist_list.end(); it++) {
        if((*it)->name.find(key)!=-1)
            print_artist(*it);
    }
}

void print_artist_directory() {
    for (int i=0; i<256; i++) {
        list<Artist *> &artist_list = artist_directory[i];
        for (auto ptr: artist_list) {
            print_artist(ptr);
        }
    }
}

Artist *add_artist(string name) {
    Artist *ptr_artist = new Artist(name);
    list<Artist *> &artist_list = artist_directory[(unsigned char)name[0]];
    artist_list.push_back(ptr_artist);
    return ptr_artist;
}

void add_song(string title, string artist, string album = "", string mv_url = "") {
    Artist *artist_ptr = find_artist(artist);
    if (artist_ptr == nullptr) {
        artist_ptr = add_artist(artist);
    }
    Song *song_ptr = new Song(title, artist_ptr, album, mv_url);
    artist_ptr->songs.push_back(song_ptr);
    list<Song *> &song_list = song_directory[song_ptr->index % SONG_DIRECTORY_SIZE];
    song_list.push_back(song_ptr);
}

void user_add_song(){
    string title,artist,album,mv_url;
    cout<<" Title: ";
    getline(cin,title);
    cout<<" Artist: ";
    getline(cin,artist);
    cout<<" Album: ";
    getline(cin,album);
    cout<<" MV url: ";
    getline(cin,mv_url);
    add_song(title,artist,album,mv_url);

}
void load_songs(string filename) {
    string line;
    ifstream songfile(filename);
    while(getline(songfile, line)) {
        vector<string> tokens = split_line(line, ',');
        assert(tokens.size()==4 || tokens.size()==3);
        if (tokens.size()==4)
            add_song(tokens[0], tokens[1], tokens[2], tokens[3]);
        else
            add_song(tokens[0], tokens[1], tokens[2]);
    }
    songfile.close();
}

void find_song(string key){
    for(int i=0;i<SONG_DIRECTORY_SIZE;i++){
        list<Song *> &song_list = song_directory[i];
        for(auto s:song_list) {
            if ((s->title.find(key)) != -1)
                cout << " " << s->index << ":" << s->title << ", "
                     << s->artist->name << ", " << s->album << ", " << s->mv_url << endl;
        }
    }
}
void remove_song(int ind){
    for(int i=0;i<SONG_DIRECTORY_SIZE;i++) {
        for (auto it = song_directory[i].begin(); it != song_directory[i].end(); it++)
            if ((*it)->index == ind) {
                Artist *artist_ptr = (*it)->artist;
                artist_ptr->songs.remove(*it);
                it = song_directory[i].erase(it);
                return;
            }
    }
}
void remove_artist(string key) {
    list<Artist *> &artist_list = artist_directory[(unsigned char)key[0]];
    for (auto it = artist_list.begin(); it != artist_list.end(); ) {
        if ((*it)->name.find(key)!=-1) {
            cout << "Want to remove artist \'" << (*it)->name << "\' ? ";
            string tmp;
            getline(cin, tmp);
            if (tmp.find("yes") != string::npos) {
                for (auto song : (*it)->songs) {
                    list<Song *> &song_list = song_directory[song->index % SONG_DIRECTORY_SIZE];
                    song_list.remove(song);
                    delete song;
                }
                (*it)->songs.clear();

                delete *it;
                it = artist_list.erase(it);
            } else {
                it++;
            }
        } else {
            it++;
        }
    }
}


void print_song_directory() {
    for (int i=0; i<SONG_DIRECTORY_SIZE; i++) {
        list<Song *> &song_list = song_directory[i];
        for (auto s: song_list) {
            cout << " " << s->index << ":" << s->title << ", "
                 << s->artist->name << ", " << s->album << ", " << s->mv_url << endl;
        }
    }
}

void save_song(){
    ofstream outfile(datafilename);
    for(int i=0;i<SONG_DIRECTORY_SIZE;i++) {
        list<Song *> &song_list = song_directory[i];
        for (auto s: song_list) {
            outfile << s->title << ", " << s->artist->name << ", " << s->album << ", " << s->mv_url << endl;
        }
    }
    outfile.close();
}

int main() {
    load_songs(datafilename);
     string input;


    while(1){
        cout<<"$ ";
        getline(cin,input);

        istringstream iss(input);
        string command;
        vector<string>args;
        iss>>command;

        string arg;
        while(iss>>arg){
            args.push_back(arg);
        }

        if(command =="list"){
            if(!args.empty() && args[0]=="-a")
                print_artist_directory();
            else
                print_song_directory();
        }
        else if (command =="add"){
            user_add_song();
        }
        else if (command == "find"){
            if(!args.empty() && args[0]=="-a"){
                find_print_artist(args[1]);
                continue;
            }
            find_song(args[0]);
        }
        else if (command =="remove"){
            if(!args.empty() && args[0]=="-a"){
                remove_artist(args[1]);
                continue;
            }
            remove_song(stoi(args[0]));

        }
        else if (command =="save"){
            save_song();
        }
        else if(command == "exit")
            break;
    }
    return 0;
}