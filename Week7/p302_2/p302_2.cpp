#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAXWORDS = 100;

struct WordPair {
    string eng;
    string kor;
};

class MyDic {
private:
    WordPair words[MAXWORDS];
    int nWords;

public:
    MyDic() {
        nWords = 0;
    }

    inline void add(string eng, string kor) {
        if (nWords < MAXWORDS) {
            words[nWords].eng = eng;
            words[nWords].kor = kor;
            nWords++;
        }
    }

    inline void load(string filename) {
        ifstream fin(filename);
        if (!fin) {
            return;
        }
        nWords = 0;
        string e, k;
        while (fin >> e >> k) {
            if (nWords < MAXWORDS) {
                words[nWords].eng = e;
                words[nWords].kor = k;
                nWords++;
            }
        }
        fin.close();
    }

    inline void store(string filename) {
        ofstream fout(filename);
        if (!fout) {
            return;
        }
        for (int i = 0; i < nWords; i++) {
            fout << words[i].eng << ":" << words[i].kor << endl;
        }
        fout.close();
    }

    inline void print() {
        for (int i = 0; i < nWords; i++) {
            cout << words[i].eng << ":" << words[i].kor << endl;
        }
    }

    inline string getKor(int id) {
        if (id >= 0 && id < nWords) {
            return words[id].kor;
        }
        return "";
    }
};

int main() {
    MyDic myDict;

    myDict.add("Algorithm", "알고리즘");
    myDict.add("Pointer", "포인터");
    myDict.add("Reference", "참조자");

    myDict.store("words.txt");

    MyDic loadDict;
    loadDict.load("words.txt");

    cout << "---단어장 출력 ---" << endl;
    loadDict.print();

    return 0;
}