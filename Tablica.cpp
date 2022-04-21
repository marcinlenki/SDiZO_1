#include <iostream>
#include "Tablica.h"
using namespace std;

Tablica::Tablica() {
        this->arrSize = 0;
        arr = nullptr;
}

Tablica::~Tablica() {
    clear();
}

void Tablica::fillFromFile(const char* name) {
    ifstream inFile;
    inFile.open(name);

    if (!inFile.is_open()) {
        cout<<"Otwarcie pliku nie powiodło się."<<endl;
        return;
    }

    if(!isEmpty()) {
        clear();
    }

    inFile >> arrSize;
    if (arrSize <= 0) {
        cout<<"W pliku wykryto błędne dane [ROZMIAR STRUKTURY]."<<endl;
        return;
    }

    arr = new int[arrSize];
    int index = 0, value;

    while(inFile >> value) {
        arr[index++] = value;
    }

    if (inFile.eof()) {
//        cout<<"Wczytywanie danych zakończone."<<endl;
    } else if(inFile.fail()) {
        cout<<"Wczytywanie danych przerwane, nie udało się wczytać pliku."<<endl;
    } else {
        cout<<"Wczytywanie danych przerwane."<<endl;
    }

    inFile.close();
}

void Tablica::show() {
    if (isEmpty()) {
        cout<<"Tablica jest pusta."<<endl;
        return;
    }

    cout<<"=============================="<<endl;
    cout<<"\t  Rozmiar tablicy: "<<arrSize<<endl;
    cout<<"=============================="<<endl;
    for(int i = 0; i < arrSize; i++) {
        cout<<"Element "<< i+1 << ": "<<arr[i]<<endl;
    }
    cout<<"=============================="<<endl;
}

int *Tablica::search(int value) {
    for (int i = 0; i < arrSize; i++) {
        if (arr[i] == value) {
            return (arr + i);
        }
    }

    return nullptr;
}

bool Tablica::addBeginning(int value) {
    if (!isEmpty()) {
        resize(true);
        alignToRight(0);
        arr[0] = value;
    } else {
        arrSize++;
        arr = new int [arrSize];
        arr[0] = value;
    }

    return true;
}

bool Tablica::removeBeginning() {
    if(!isEmpty()) {
        int *temp = new int[arrSize - 1];
        memcpy(temp, arr + 1, (arrSize - 1) * sizeof(int));
        delete[] arr;
        arr = temp;
        arrSize--;
        if (isEmpty()) {
            delete[] arr;
            arr = nullptr;
        }
        return true;
    }

    return false;
}

bool Tablica::addEnd(int value) {
    if (!isEmpty()) {
        resize(true);
        arr[arrSize - 1] = value;
    } else {
        arrSize++;
        arr = new int [arrSize];
        arr[0] = value;
    }

    return true;
}

bool Tablica::removeEnd() {
    if(!isEmpty()) {
        resize(false);
        if (isEmpty()) {
            delete[] arr;
            arr = nullptr;
        }
        return true;
    }
    return false;
}

bool Tablica::addIndex(int index, int value) {
    if (index < 0 || index >= arrSize + 1)
        return false;

    if (!isEmpty()) {
        resize(true);
        alignToRight(index);
        arr[index] = value;
    } else {
        arrSize++;
        arr = new int [arrSize];
        arr[0] = value;
    }

    return true;
}

bool Tablica::removeIndex(int index) {
    if (index < 0 || index >= arrSize)
        return false;

    alignToLeft(index);
    resize(false);
    if(isEmpty()) {
        delete[] arr;
        arr = nullptr;
    }

    return true;
}

bool Tablica::isEmpty() {
    return arrSize == 0;
}

bool Tablica::resize(bool add) {
    int *temp;

    if (add) {
        temp = new int[arrSize + 1];
        memcpy(temp, arr, arrSize * sizeof(int));
        delete[] arr;
        arr = temp;
        arrSize++;
    } else {
        temp = new int[arrSize - 1];
        memcpy(temp, arr, (arrSize - 1) * sizeof(int));
        delete[] arr;
        arr = temp;
        arrSize--;
    }

    return true;
}

void Tablica::alignToRight(int index) {
    for(int i = (int)arrSize - 1; i > index; i--) {
        arr[i] = arr[i-1];
    }
}

void Tablica::alignToLeft(int index) {
    for (int i = index; i < arrSize; i++) {
        arr[i] = arr[i + 1];
    }
}

void Tablica::clear() {
    delete [] arr;
    arr = nullptr;
    arrSize = 0;
}
