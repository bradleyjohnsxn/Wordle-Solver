#include "5letters.h";


int main() {
    vector<string> words = get_5s("english3.txt");
    out_5s(words, "9letterwords.txt");

    return 0;
}



vector<string> get_5s(string filepath) {
    ifstream infile;
    infile.open(filepath);
    string holder = "";
    vector<string> res;

    while (!infile.eof()) {
        getline(infile, holder);
        if (holder.size() != 9) {
            continue;
        }
        else if (lower_alpha(holder)) {
            res.push_back(holder);
        }
    }
    infile.close();
    return res;
}

bool lower_alpha(string s) {
    for (unsigned int i = 0; i < s.length(); i++) {
        if (!isalpha(s[i]) || isupper(s[i])) {
            return false;
        }
    }
    return true;
}

void out_5s(vector<string> v, string filepath) {
    ofstream outfile;
    outfile.open(filepath);
    for (unsigned int i = 0; i < v.size(); i++) {
        outfile << v[i] << endl;
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