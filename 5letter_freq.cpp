#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

vector<pair<string, int>> get_5s(string filepath);
bool alpha(string s);
void out_5s(vector<pair<string, int>> v, string filepath);
string low_string(string s);

int main() {
    vector<pair<string, int>> v = get_5s("unigram_freq.csv");
    out_5s(v, "5letter_unigram_freq.csv");

	return 0;
}

vector<pair<string, int>> get_5s(string filepath) {
    ifstream infile;
    infile.open(filepath);
    string holder = "", word = "", number = "";
    vector<pair<string, int>> res;

    bool add = true;
    while (!infile.eof()) {
        pair<string, int> p;
        getline(infile, holder);

        word = "";
        number = "";
        add = true;

        for (char x : holder) {
            if (x == ',') {
                add = false;
            }
            else if(add) {
                word += x;
            }
            else {
                number += x;
            }
        }

        if (word.size() != 5) {
            continue;
        }
        else if (alpha(word)) {
            p.first = low_string(word);
            p.second = stoi(number);
            res.push_back(p);
        }
    }
    infile.close();
    return res;
}

bool alpha(string s) {
    for (unsigned int i = 0; i < s.length(); i++) {
        if (!isalpha(s[i])) {
            return false;
        }
    }
    return true;
}

void out_5s(vector<pair<string, int>> v, string filepath) {
    ofstream outfile;
    outfile.open(filepath);
    string holder = "";
    for (unsigned int i = 0; i < v.size(); i++) {
        holder = "";
        holder += v[i].first + ',' + to_string(v[i].second);
        outfile << holder << endl;
    }
    outfile.close();
}

string low_string(string s) {
    string res = "";
    for (unsigned int i = 0; i < s.length(); i++) {
        res += tolower(s[i]);
    }
    return res;
}