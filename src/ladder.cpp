#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <algorithms>
#include "ladder.h"
using namespace std;

void error(string word1, string word2, string msg){
    cout << "Error: " << msg;
    System.exit(0);
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (str1 == str2){
        error(str1, str2, "same words passed to edit_distance_within");
    }
    int size1 = str1.size();
    int size2 = str2.size();
    if (size1 == size2){
        for (int i = 0; i < size1; ++i){
            //find first not matched char
            if (str1[i] != str2[i]){
                for (int j = i; j < size1; ++j){ //check if rest char matched
                    if (str1[j] != str2[j]){return false;}
                }
                return true;
            }
        }
    } else if (size1 == size2 +1 || size1 == size2 -1){
        int min_size = min(size1, size2);
        string min_string = (size1 < size2)? str1:str2;
        string max_string = (size1 >= size2)? str2:str1;
        for (int i= 0; i <min_size; ++i){
            if (str1[i] != str2[i]){
                for (int j = i; j < min_size; ++j){
                    if (min_string[j] != max_string[j+1]){
                        return false;
                    }
                }
                return true;
            }
        }
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
    
    if (!word_list.contain(end_word)){
        error(end_word, end_word, end_word + " is not contained in the word_list");
    }

    queue<vector<string>> word_ladder;
    word_ladder.push({begin_word});
    // set<string> visited;
    // visited.insert(start_word);

    while(!word_ladder.empty()){
        vector<String> ladder = word_ladder.top();
        word_ladder.pop();
        string last_word = ladder.back();
        for (string word: word_list){
            if (is_adjacent(word, last_word) && find(ladder.begin(), ladder.end(), word) != ladder.end()){
                vec<string> new_ladder;
                for (string w: ladder){
                    new_ladder.push_back(w);
                }
                new_ladder.push_back(word);
                if (word == last_word){
                    return new_ladder;
                }
                word_ladder.push(word);
            }
        }
    }
    return {};
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
        cout << word << " -> ";
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
