#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg){
    cerr << "Error: " << msg;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (str1 == str2){
        return false;
    }
    
    int size1 = str1.size();
    int size2 = str2.size();
    if (size1 == size2){
        for (int i = 0; i < size1; ++i){
            //find first not matched char
            if (str1[i] != str2[i]){
                return str1.substr(i+1) == str2.substr(i+1);
            }
        }
    } else if (abs(size1 - size2) == 1){
        int i = 0; int j =0;
        while (i < size1 && j < size2){
            if (str1[i] != str2[j]){
                if (size1 > size2){++i;}
                else { ++j;}
                return str1.substr(i) == str2.substr(j);
            }
            ++i; ++j;
        }
        return true;
    }
    return false;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word){
        error(begin_word, end_word, "Begin word same as end word (for calling generate_word_ladder)");
    }
    
    if (word_list.find(end_word) == word_list.end()){
        error(end_word, end_word, end_word + " is not contained in the word_list");
    }

    queue<vector<string>> word_ladder;
    word_ladder.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while(!word_ladder.empty()){
        vector<string> ladder = word_ladder.front();
        word_ladder.pop();
        string last_word = ladder.back();
        for (string word: word_list){
            // std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
            //     return std::tolower(c);
            // });
            //cout << word << " " << last_word;
            if (is_adjacent(word, last_word)){
                //cout << word << " is adjacent to " << last_word << endl;
                if (visited.find(word) == visited.end()){
                    //cout << word << " ";
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word){
                        //cout << "target word find";
                        return new_ladder;
                    }
                    word_ladder.push(new_ladder);
                }
            }
        }
    }
    error(begin_word, end_word, "Now word ladder found.\n");
    //return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    if (!in) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }

    string word;
    while (in >> word){
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder){
    for (string word: ladder){
        cout << word << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    vector<string> result = generate_word_ladder("cat", "dog", word_list);
    for  (string x:result){
        cout << x;
    }
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
