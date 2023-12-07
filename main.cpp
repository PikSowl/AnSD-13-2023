#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::string;
using std::endl;
using std::vector;
using std::pair;

class HashTableWithLists {
public:

    HashTableWithLists(int size) : sz(size) {
        arr = new vector<pair<string, string>>[size];
    }
    HashTableWithLists(const HashTableWithLists& table) {
        sz = table.sz;
        arr = new vector<pair<string, string>>[sz];
        std::memcpy(arr, table.arr, sizeof(arr));
    }
    ~HashTableWithLists() {
        delete[] arr;
    }

    int size() {
        return sz;
    }

    vector<pair<string, string>>* data() {
        return arr;
    }

    string& operator [](const string& key) {
        for (auto& el : arr[hash(key)]) {
            if (el.first == key) return el.second;
        }

        arr[hash(key)].push_back({ key, "\0" });

        return arr[hash(key)].back().second;
    }

private:
    int hash(const string& str) {
        int hash = 0;
        for (char i : str) {
            hash += i;
        }
        if (hash < 0) hash *= -1;
        hash %= sz;
        return hash;
    }

    vector<pair<string, string>>* arr;
    int sz;
};

int main() {
    std::setlocale(LC_ALL, "RUS");
    cout << "lab14" << endl;
    std::ifstream f;
    f.open("input.txt");

    if (f.is_open()) {
        int len_of_words = 0;
        string str;
        vector<string> words;
        while (!f.eof()) {
            f >> str;
            words.push_back(str);
        }

        HashTableWithLists h_table(words.size() * 2);

        for (auto& word : words) {

            switch (word.back())
            {
            case '.':
                h_table["."] = ".";
                word.pop_back();
                break;
            case ',':
                h_table[","] = ",";
                word.pop_back();
                break;
            case ';':
                h_table[";"] = ";";
                word.pop_back();
                break;
            case ':':
                h_table[":"] = ":";
                word.pop_back();
                break;
            case '?':
                h_table["?"] = "?";
                word.pop_back();
                break;
            case '!':
                h_table["!"] = "!";
                word.pop_back();
                break;
            }
            h_table[word] = word;
        }
        h_table["keep"] = "Hello World!";


        std::ofstream out;
        out.open("table.txt");
        for (int i = 0; i < h_table.size(); i++) {
            out << i << " : { ";
            for (int j = 0; j < h_table.data()[i].size(); j++) {
                out << "\"" << h_table.data()[i][j].second << "\" ";
            }
            out << "}\n";
        }

        out.close();


    }

    f.close();

}
