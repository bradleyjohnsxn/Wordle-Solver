#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <map>
using namespace std;

vector<string> get_5s(string filepath, string filepath2);
vector<string> get_9s(string filepath);
map<string, long> get_freqs(string filepath);
string get_greens();
bool valid_yellow(string y, int num_lets);
void get_yellows(vector<string>& y, int num_lets);
void get_used(vector<char>& used);

bool match_g(string word, string green);
bool pass_y(string word, string y);
bool leave_y(string word, vector<string>& yellow);
bool contains_used(string word, vector<char>& used);
vector<string> sift(vector<string>& words, string greens, vector<string>& yellows, vector<char>& used);
vector<string> sift_g(vector<string>& words, string greens);
vector<string> sift_y(vector<string>& words, vector<string> yellows);
vector<string> sift_used(vector<string>& words, vector<char>& used, string& g, vector<string>& yellows);

void print(vector<string>& pos);
vector<string> string_sort(vector<string> words, map<string, long>& freqs);
vector<string> merge_sort(vector<string> words, int left, int right, map<string, long>& freqs);
vector<string> merge(vector<string> left, vector<string> right, map<string, long>& freqs);

int main() {
    map<string, long> freqs = get_freqs("5letter_unigram_freq.csv");
    vector<string> words5 = get_5s("5letterwords.txt", "5letterwords2.txt");
    vector < string> words9 = get_9s("9letterwords.txt");
    string g;
    
    bool cont = true;
    string con = "", num="";
    while (cont) {
        cout << "Number of letters: " << endl;
        std::getline(cin, num);

        con = "";
        vector<string> yellows, possible;
        if (num == "5") {
            possible = words5;
        }
        else if (num == "9") {
            possible = words9;
        }
        vector<char> used;

        string holder = "";
        bool end = false;
        while (!end) {
            g = get_greens();
            get_yellows(yellows, stoi(num));
            get_used(used);

            possible = sift(possible, g, yellows, used);
            possible = string_sort(possible, freqs);

            print(possible);

            cout << "Continue? (y/n)" << endl;
            std::getline(cin, holder);
            if (holder == "y") {
                end = false;
            }
            else {
                end = true;
            }
        }
        cout << "Another word? (y/n)" << endl;
        std::getline(cin, con);
        if (con == "y") {
            con = true;
        }
        else {
            cont = false;
        }
    }

	return 0;
}

vector<string> get_5s(string filepath, string filepath2) {
    string holder = "";
    vector<string> v;
    
    ifstream infile;
    infile.open(filepath2);

    while (!infile.eof()) {
        std::getline(infile, holder);
        v.push_back(holder);
    }
    infile.close();

    /*ifstream infile2;
    infile.open(filepath2);

    while (!infile2.eof()) {
        std::getline(infile2, holder);
        res.insert(holder);
    }
    infile.close();
    
    vector<string> v;
    for (string s : res) {
        v.push_back(s);
    }*/
    return v;
}

vector<string> get_9s(string filepath) {
    string holder = "";
    vector<string> v;

    ifstream infile;
    infile.open(filepath);

    while (!infile.eof()) {
        std::getline(infile, holder);
        v.push_back(holder);
    }
    infile.close();

    return v;
}

map<string, long> get_freqs(string filepath) {
    ifstream infile;
    infile.open(filepath);
    string holder = "", word = "", number="";
    map<string, long> res;
    bool add = true;

    while (!infile.eof()) {
       
        std::getline(infile, holder);
        add = true;
        word = "";
        number = "";
        for (char x : holder) {
            if (x == ',') {
                add = false;
            }
            else if (add) {
                word += x;
            }
            else {
                number += x;
            }
        }

        if (word != "" && number != "")
            res[word] = stol(number);
    }
    infile.close();
    return res;
}

string get_greens() {
    cout << "Enter greens: " << endl;
    string holder = "";
    std::getline(cin, holder);
    return holder;
}

bool valid_yellow(string y, int num_lets) {
    if (y.length() == num_lets) {
        for (unsigned int i = 0; i < y.length(); i++) {
            if (!(isalpha(y[i]) || y[i] == '-')) {
                return false;
            }
        }
    }
    else {
        return false;
    }
    return true;
}

void get_yellows(vector<string>& y, int num_lets) {
    
    string holder = "", temp="";
    while (holder != "end") {
        cout << "Enter yellows (type 'end' to exit): " << endl;
        std::getline(cin, holder);
        if (holder != "end" && valid_yellow(holder, num_lets)) {
            bool enter = false;
            for (unsigned int i = 0; i < holder.size(); i++) {
                temp = "";
                enter = false;
                for (unsigned int j = 0; j < holder.size(); j++) {
                    if (j != i) {
                        temp += "-";
                    }
                    else {
                        temp += holder[i];
                        if (isalpha(holder[i]))
                            enter = true;
                    }
                }
                if (enter) {
                    y.push_back(temp);
                }
            }
        }
    }
    
}

vector<string> sift(vector<string>& words, string greens, vector<string>& yellows, vector<char>& used) {
    vector<string> possible = words;
    possible = sift_g(possible, greens);
    possible = sift_y(possible, yellows);
    possible = sift_used(possible, used, greens, yellows);
    return possible;
}

bool match_g(string word, string green) {
    for (unsigned int i = 0; i < word.length(); i++) {
        if (green[i] != '-') {
            if (word[i] != green[i]) {
                return false;
            }
        }
    }
    return true;
}

vector<string> sift_g(vector<string>& words, string greens) {
    vector<string> res;
    for (unsigned int i = 0; i < words.size(); i++) {
        if (match_g(words[i], greens))
            res.push_back(words[i]);
    }
    return res;
}

void get_used(vector<char>& used) {
    set<char> s;
    for (char x : used) {
        s.insert(x);
    }

    string holder = "";
    cout << "Enter used letters: " << endl;
    std::getline(cin, holder);
    for (char x : holder) {
        if (isalpha(x)) {
            s.insert(x);
        }
    }
    
    vector<char> res;
    for (char x : s) {
        res.push_back(x);
    }
    used = res;
}

bool pass_y(string word, string y) {
    char l = '1';
    for (char x : y) {
        if (x != '-') {
            l = x;
            break;
        }
    }

    bool contains = false, omits = true;
    for (unsigned int i = 0; i < word.length(); i++) {
        if (y[i] == '-') {
            if (word[i] == l) {
                contains = true;
            }
        }
        else {
            if (word[i] == l) {
                omits = false;
            }
        }
    }
    if (contains == true && omits == true) {
        return false;
    }
    else {
        return true;
    }
}

bool leave_y(string word, vector<string>& yellows) {
    bool res = false;
    for (unsigned int i = 0; i < yellows.size(); i++) {
        if (pass_y(word, yellows[i])) {
            res = true;
        }
    }
    return res;
}

vector<string> sift_y(vector<string>& words, vector<string> yellows) {
    vector<string> res;
    for (unsigned int i = 0; i < words.size(); i++) {
        
        if (!leave_y(words[i], yellows))
            res.push_back(words[i]);
    }
    return res;
}

bool contains_used(string word, vector<char>& used) {

    for (unsigned int i = 0; i < word.size(); i++) {
        for (unsigned int j = 0; j < used.size(); j++){
            if (word[i] == used[j]) {
                return true;
            }
        }
    }
    return false;
}

void clean_used(vector<char>& used, string& g, vector<string>& yellows) {
    set<char> keep;
    for (char x : g) {
        if (x != '-')
            keep.insert(x);
    }
    for (string s : yellows) {
        for (char x : s) {
            if (x != '-') {
                keep.insert(x);
            }
        }
    }

    set<char> use;
    for (char x : used) {
        use.insert(x);
    }

    for (char x : keep) {
        use.erase(x);
    }

    vector<char> res;
    for (char x : use) {
        res.push_back(x);
    }
    used = res;
}

vector<string> sift_used(vector<string>& words, vector<char>& used, string& g, vector<string>& yellows) {

    vector<string> res;
    clean_used(used, g, yellows);

    for (unsigned int i = 0; i < words.size(); i++) {
        if (!contains_used(words[i], used))
            res.push_back(words[i]);
    }
    return res;
}

void print(vector<string>& pos) {
    cout << pos.size() << " possible word(s): " << endl;
    for (unsigned int i = pos.size(); i >0; i--) {
        cout << pos[i-1] << endl;
    }
}

vector<string> string_sort(vector<string> words, map<string, long>& freqs) {
    if (words.size() == 0)
        return words;
    else
        return merge_sort(words, 0, words.size() - 1, freqs);
}

vector<string> merge_sort(vector<string> words, int left, int right, map<string, long>& freqs) {
    if (right > left) {
        int middle = left + (right - left) / 2;
        vector<string> one = merge_sort(words, left, middle, freqs);
        vector<string> two = merge_sort(words, middle + 1, right, freqs);
        return merge(one, two, freqs);

    }
    else {
        vector<string> hold;
        hold.push_back(words[left]);
        return hold;
    }

}

vector<string> merge(vector<string> left, vector<string> right, map<string, long>& freqs) {
    vector<string> res;
    unsigned int i = 0, j = 0;
    while (i < left.size() || j < right.size()) {
        if (i < left.size() && j < right.size()) {

            
            if (freqs[left[i]] < freqs[right[j]]) {
                res.push_back(left[i]);
                i++;
            }
            else {
                res.push_back(right[j]);
                j++;
            }
            
        }
        else if (i < left.size()) {
            res.push_back(left[i]);
            i++;
        }
        else {
            res.push_back(right[j]);
            j++;
        }
    }
    return res;
}