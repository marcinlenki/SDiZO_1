#include <iostream>
#include <fstream>
#include "Kopiec.h"

using namespace std;

Kopiec::Kopiec() {
    this->heapSize = 0;
    this->arr = nullptr;
}

Kopiec::~Kopiec() {
    clear();
}

void Kopiec::fillFromFile(const char *name) {
    ifstream inFile;
    inFile.open(name);

    if (!inFile.is_open()) {
        cout<<"Otwarcie pliku nie powiodło się."<<endl;
        return;
    }

    if(!isEmpty()) {
        clear();
    }

    inFile >> heapSize;
    if (heapSize <= 0) {
        cout<<"W pliku wykryto błędne dane [ROZMIAR STRUKTURY]."<<endl;
        return;
    }

    arr = new int[heapSize];
    int index = 0, value;

    while(inFile >> value) {
        arr[index++] = value;
    }

    buildMaxHeap();

    if (inFile.eof()) {
//        cout<<"Wczytywanie danych zakończone."<<endl;
    } else if(inFile.fail()) {
        cout<<"Wczytywanie danych przerwane, nie udało się wczytać pliku."<<endl;
    } else {
        cout<<"Wczytywanie danych przerwane."<<endl;
    }

    inFile.close();
}

void Kopiec::show() {
    if(isEmpty()) {
        cout<<"Kopiec jest pusty."<<endl;
        return;
    }
    
    cout<<"[";
    for(int i = 0; i<heapSize; i++) {
        cout<<arr[i]<<" ";
    }
    cout<<"]"<<endl;
}

int *Kopiec::search(int value) {
    for(int i = 0; i<heapSize; i++) {
        if (arr[i] == value)
            return (arr + i);
    }

    return nullptr;
}

bool Kopiec::add(int value) {
    if (!isEmpty()) {
        resize(true);
        arr[heapSize - 1] = value;
        heapifyUp((int)heapSize - 1);
    } else {
        heapSize++;
        arr = new int [heapSize];
        arr[0] = value;
    }

    return true;
}

bool Kopiec::removeRoot() {
    if(isEmpty())
        return false;

    arr[0] = arr[heapSize - 1];
    resize(false);
    if(isEmpty()) {
        delete[] arr;
        arr = nullptr;
    } else
        heapify(0);

    return true;
}

void Kopiec::clear() {
    delete [] arr;
    arr = nullptr;
    heapSize = 0;
}

bool Kopiec::isEmpty() {
    return heapSize == 0;
}

bool Kopiec::resize(bool add) {
    int *temp;

    if (add) {
        temp = new int[heapSize + 1];
        memcpy(temp, arr, heapSize * sizeof(int));
        delete[] arr;
        arr = temp;
        heapSize++;
    } else {
        temp = new int[heapSize - 1];
        memcpy(temp, arr, (heapSize - 1) * sizeof(int));
        delete[] arr;
        arr = temp;
        heapSize--;
    }

    return true;
}

int Kopiec::parentIndex(int i) {
    return (i - 1)/2;
}

int Kopiec::leftChildIndex(int i) {
    return 2*i + 1;
}

int Kopiec::rightChildIndex(int i) {
    return 2*i + 2;
}

void Kopiec::heapify(int i) {
    int largest;
    int left = leftChildIndex(i);
    int right = rightChildIndex(i);

    if(left <= heapSize - 1 && arr[left] > arr[i])
        largest = left;
    else
        largest = i;

    if(right <= heapSize - 1 && arr[right] > arr[largest])
        largest = right;

    // ??
    if(largest != i) {
        swap(arr[i], arr[largest]);
        heapify(largest);
    }
}

void Kopiec::heapifyUp(int childIndex) {
    if (childIndex == 0)
        return;

    int parent = parentIndex(childIndex);

    if(arr[childIndex] > arr[parent]) {
        swap(arr[parent], arr[childIndex]);
        heapifyUp(parent);
    }
}

void Kopiec::buildMaxHeap() {
    int lastParentIndex = ((int)heapSize/2) - 1;
    for(int i = lastParentIndex; i >= 0; i--) {
        heapify(i);
    }
}