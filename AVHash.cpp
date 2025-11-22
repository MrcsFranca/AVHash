#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "libAVL.h"
#include "picosha2.h"

using namespace std;

node *loadDataBase(node *T, string fileToLoad);
string calculateFileHash(string filePath);
void updateDataBase();

int main(int argc, char *argv[]) {
    if(argc < 2) {
        cerr << "Uso: " << argv[0] << " <arquivo para escanear>" << endl;
        return 1;
    }
    node *T = NULL;
    bool exists;
    string hashToSearch;
    string file = argv[1];

    updateDataBase();

    T = loadDataBase(T, "signatures.txt");

    hashToSearch = calculateFileHash(file);
    cout << "hash do arquivo: " << hashToSearch << endl; 

    exists = search(T, hashToSearch);
    
    if(exists) {
        cout << "AVISO: Possível malware detectado -> Desconecte-se da internet e exclua o arquivo" << endl;
    } else {
        cout << "O arquivo não aparenta ser malicioso" << endl;
    }
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
        if(line.empty()) {
            continue;
        }
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

void updateDataBase() {
    cout << "Começando a atualização do banco de dados..." << endl;

    int result = system("python3 downloadDb.py");

    if(result == 0) {
        cout << "Banco de dados atualizado com sucesso!" << endl; 
    } else {
        cerr << "Erro ao atualizar banco de dados" << endl;
    }
}
