#ifndef PROJEKT_TABLICA_H
#define PROJEKT_TABLICA_H

#include "fstream"

class Tablica {
private:
    unsigned int arrSize;
    int *arr;

    bool isEmpty();

    // Funkcje pomocnicze używane do dynamicznego alokowania tablicy
    bool resize(bool add);
    void alignToRight(int index);
    void alignToLeft(int index);

public:
    Tablica();
    ~Tablica();
    void fillFromFile(const char* name);
    void show();
    int* search(int value);
    bool addBeginning(int value);
    bool removeBeginning();
    bool addEnd(int value);
    bool removeEnd();
    bool addIndex(int index, int value);
    bool removeIndex(int index);
    void clear();
};

#endif