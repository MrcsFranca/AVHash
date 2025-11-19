#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "libAVL.h"
#include "picosha2.h"

using namespace std;

node *loadDataBase(node *T, string fileToLoad);
string calculateFileHash(string filePath);

int main() {
    node *T = NULL;
    bool exists;
    string hashToSearch;

    T = loadDataBase(T, "signatures.txt");

    hashToSearch = calculateFileHash("hashTeste.txt");
    cout << "hash do arquivo: " << hashToSearch << endl; 

    exists = search(T, hashToSearch);
    cout << exists << endl;
}

node *loadDataBase(node *T, string fileToLoad) {
    string filename(fileToLoad);
    vector<string> lines;
    string line;

    ifstream inputFile(filename);
    if(!inputFile.is_open()) {
        cerr << "Não foi possível abrir o arquivo: " << filename << endl;
        return NULL;
    }

    while(getline(inputFile, line)) {
        //lines.push_back(line);
        T = insertAVL(T, line);
    }

    //for(const auto &i : lines) cout << i << endl;

    inputFile.close();

    return T;
}

string calculateFileHash(string filePath) {
    ifstream file(filePath, ios::binary | ios::ate);

    if(!file.is_open()) {
        cerr << "Não foi possível abrir o arquivo: " << filePath << endl;
    }

    ifstream::pos_type pos = file.tellg();

    if(pos == 0) {
        return picosha2::hash256_hex_string(string(""));
    }

    vector<char> buffer(pos);
    file.seekg(0, ios::beg);
    file.read(&buffer[0], pos);
    file.close();

    string fileHash;
    picosha2::hash256_hex_string(buffer, fileHash);
    return fileHash;
}