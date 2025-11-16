#include <iostream>
#include <string>
#include "libAVL.h"

using namespace std;

int main() {
    node *T = NULL;
    T = insertAVL(T, "teste1");
    T = insertAVL(T, "teste2");
    T = insertAVL(T, "teste3");
    T = insertAVL(T, "teste4");
    inOrderAVL(T);
    bool hash;
    hash = search(T, "teste6");
    cout << hash << endl;
}