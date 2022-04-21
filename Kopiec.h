#ifndef PROJEKT_KOPIEC_H
#define PROJEKT_KOPIEC_H


class Kopiec {
private:
    unsigned int heapSize;
    int *arr;

    bool isEmpty();
    bool resize(bool add);
    int parentIndex(int i);
    int leftChildIndex(int i);
    int rightChildIndex(int i);
    void heapify(int i);
    void heapifyUp(int childIndex);
    void buildMaxHeap();

public:
    Kopiec();
    ~Kopiec();
    void fillFromFile(const char* name);
    void show();
    int* search(int value);
    bool add(int value);
    bool removeRoot();
    void clear();
};


#endif