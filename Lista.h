#ifndef PROJEKT_LISTA_H
#define PROJEKT_LISTA_H
#include <windows.h>

class Lista {
public:
    struct Node {
        int value;
        Node *prev, *next;
    };

    unsigned int listSize;
    Node *head, *tail;

    bool isEmpty();
    void deleteNode(Node* le);

public:
    Lista();
    ~Lista();
    void fillFromFile(const char* name);
    void show();
    Node* search(int value);
    bool addBeginning(int value);
    bool removeBeginning();
    bool addEnd(int value);
    bool removeEnd();
    Node* get(int index);
    bool addIndex(int index, int value);
    bool removeIndex(int index);
    void clear();
};

#endif
