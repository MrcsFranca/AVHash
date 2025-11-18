#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "libAVL.h"

using namespace std;

node *loadDataBase(node *T, string fileToLoad);

int main() {
    node *T = NULL;

    T = loadDataBase(T, "signatures.txt");

    bool hash;
    hash = search(T, "fdf483f9a4489655ac803d2ff23294da3eef6bab35340298dac2d7f3889c7724");
    cout << hash << endl;
}

node *loadDataBase(node *T, string fileToLoad) {
    string filename(fileToLoad);
    vector<string> lines;
    string line;

    ifstream input_file(filename);
    if(!input_file.is_open()) {
        cerr << "Não foi possível abrir o arquivo: " << filename << endl;
        return NULL;
    }

    while(getline(input_file, line)) {
        //lines.push_back(line);
        T = insertAVL(T, line);
    }

    //for(const auto &i : lines) cout << i << endl;

    input_file.close();

    return T;
}