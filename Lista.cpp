#include <iostream>
#include <fstream>
#include "Lista.h"

using namespace std;

Lista::Lista() {
    this->listSize = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

Lista::~Lista() {
    clear();
}

void Lista::fillFromFile(const char *name) {
    ifstream inFile;
    inFile.open(name);

    if (!inFile.is_open()) {
        cout<<"Otwarcie pliku nie powiodło się."<<endl;
        return;
    }

    clear();

    int tempListSize;
    inFile >> tempListSize;
    if (tempListSize <= 0) {
        cout<<"W pliku wykryto błędne dane [ROZMIAR STRUKTURY]."<<endl;
        return;
    }

    int value;

    while(inFile >> value) {
        addEnd(value);
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

void Lista::show() {
    if (isEmpty()) {
        cout<<"Lista jest pusta."<<endl;
        return;
    }

    Node* le = head;
    int index = 1;

    cout<<"=============================="<<endl;
    cout<<"\t   Rozmiar listy: "<<listSize<<endl;
    cout<<"=============================="<<endl;

    while (le != nullptr) {
        cout<<"Element "<<index++<<": "<<le->value<<endl;
        le = le->next;
    }
}

Lista::Node *Lista::search(int value) {
    Node *le = head;

    while (le != nullptr && le->value != value) {
        le = le->next;
    }

    return le;
}

bool Lista::addBeginning(int value) {
    Node *le = new Node;

    le->value = value;
    le->prev = nullptr;
    le->next = head;

    if (head != nullptr)
        head->prev = le;
    else
        tail = le;

    head = le;

    listSize++;

    return true;
}

bool Lista::removeBeginning() {
    if(head != nullptr) {
        if(head->next != nullptr) {
            head = head->next;
            deleteNode(head->prev);
            head->prev = nullptr;
        } else {
            deleteNode(head);
            head = nullptr;
            tail = nullptr;
        }

        listSize--;
        return true;
    }

    return false;
}

bool Lista::addEnd(int value) {
    Node *le = new Node;

    le->value = value;
    le->prev = tail;
    le->next = nullptr;


    if (head != nullptr)
        tail->next = le;
    else
        head = le;

    tail = le;

    listSize++;

    return true;
}

bool Lista::removeEnd() {
    if(head != nullptr) {
        if(head->next != nullptr) {
            tail = tail->prev;
            deleteNode(tail->next);
            tail->next = nullptr;
        } else {
            deleteNode(head);
            head = nullptr;
            tail = nullptr;
        }

        listSize--;
        return true;
    }

    return false;
}

Lista::Node *Lista::get(int index) {
    Node *le = head;

    while (le != nullptr && index-- != 0) {
        le = le->next;
    }

    return le;
}

bool Lista::addIndex(int index, int value) {
    if (index < 0 || index >= listSize + 1)
        return false;

    Node *newNode = new Node;
    Node *foundNode = get(index);

    newNode->value = value;

    if (foundNode == nullptr && !isEmpty()) {
        newNode->prev = tail;
        newNode->next = nullptr;

        tail->next = newNode;

        tail = newNode;

    } else if (!isEmpty()) {
        if (foundNode->prev != nullptr) {
            foundNode->prev->next = newNode;
        } else
            head = newNode;

        newNode->next = foundNode;
        foundNode->prev = newNode;

    } else {
        newNode->prev = nullptr;
        newNode->next = nullptr;
        head = newNode;
        tail = newNode;
    }

    listSize++;
    return true;
}

bool Lista::removeIndex(int index) {
    if (index < 0 || index >= listSize)
        return false;

    Node *foundNode = get(index);

    if (foundNode->prev != nullptr) {
        foundNode->prev->next = foundNode->next;
    } else
        head = foundNode->next;

    if (foundNode->next != nullptr) {
        foundNode->next->prev = foundNode->prev;

    } else {
        tail = foundNode->prev;
    }

    deleteNode(foundNode);
    listSize--;

    return true;
}

void Lista::clear() {
    Node *le = head;
    Node *nextNode;

    while(le != nullptr) {
        nextNode = le->next;
        deleteNode(le);
        listSize--;
        le = nextNode;
    }

    head = nullptr;
    tail = nullptr;
}

void Lista::deleteNode(Node* le) {
    le->prev = nullptr;
    le->next = nullptr;
    delete le;
}

bool Lista::isEmpty() {
    return listSize == 0;
}