#include <iostream>
#include <fstream>
#include "DrzewoCC.h"

using namespace std;

DrzewoCC::DrzewoCC() {
    NIL = new Node;
    this->NIL->color = BLACK;
    this->NIL->value = -1;
    this->NIL->left = nullptr;
    this->NIL->right = nullptr;
    this->NIL->parent = nullptr;
    this->root = NIL;
    this->treeSize = 0;
}

DrzewoCC::~DrzewoCC() {
    clear();
    delete NIL;
}

void DrzewoCC::fillFromFile(const char *name) {
    ifstream inFile;
    inFile.open(name);

    if (!inFile.is_open()) {
        cout<<"Otwarcie pliku nie powiodło się."<<endl;
        return;
    }

    if(!isEmpty())
        clear();

    int tempListSize;
    inFile >> tempListSize;
    if (tempListSize <= 0) {
        cout<<"W pliku wykryto błędne dane [ROZMIAR STRUKTURY]."<<endl;
        return;
    }

    int value;

    while(inFile >> value) {
        add(value);
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

void DrzewoCC::show() {
    if(isEmpty()) {
        cout<<"Drzewo jest puste."<<endl;
        return;
    }

    Node *te = root;
    bool left = true;

    for(int i = 0; i<treeSize; i++) {
        cout<<output(te)<<", lewe dziecko: "<<output(te->left)<<", prawe dziecko: "<<output(te->right)<<endl;
    }

}

void DrzewoCC::showInOrder(DrzewoCC::Node *te) {
    if (te != NIL) {
        showInOrder(te->left);
        cout<<output(te)<<", lewe dziecko: "<<output(te->left)<<", prawe dziecko: "<<output(te->right)<<endl;
        showInOrder(te->right);
    }
}

void DrzewoCC::showInOrder() {
    if(isEmpty()) {
        cout<<"Drzewo jest puste."<<endl;
        return;
    }
    cout<<"Korzen: "<<output(root)<<endl;
    showInOrder(root);
}

DrzewoCC::Node *DrzewoCC::search(int value) {
    Node *te = root;

    while(te != NIL && te->value != value) {
        if(value < te->value)
            te = te->left;
        else
            te = te->right;
    }

    return te;
}

bool DrzewoCC::add(int value) {
    Node *newNode = new Node;
    newNode->value = value;

    Node *x = root;
    Node *y = NIL;

    while(x != NIL) {
        y = x;
        if(value < x->value)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;

    if (y == NIL) {
        root = newNode;
    } else if(value < y->value) {
        y->left = newNode;
    } else
        y->right = newNode;

    newNode->left = NIL;
    newNode->right = NIL;
    newNode->color = RED;

    treeSize++;

    addFix(newNode);
    return false;
}

bool DrzewoCC::remove(int value) {
    return false;
}

void DrzewoCC::clear() {
    clear(root);
    treeSize = 0;
    root = NIL;
}

void DrzewoCC::clear(DrzewoCC::Node *te) {
    Node *tempLeft = te->left;
    Node *tempRight = te->right;


    if (te != NIL) {
        te->parent = nullptr;
        te->left = nullptr;
        te->right = nullptr;

        clear(tempLeft);
        delete te;
        clear(tempRight);
    }
}

bool DrzewoCC::rotateRight(DrzewoCC::Node *te) {
    if(te->left == NIL)
        return false;

    Node *n = te->left;

    te->left = n->right;
    if(n->right != NIL)
        n->right->parent = te;

    n->parent = te->parent;
    if(te->parent == NIL)
        root = n;
    else if(te == te->parent->right)
        te->parent->right = n;
    else
        te->parent->left = n;

    n->right = te;
    te->parent = n;

    return true;
}

bool DrzewoCC::rotateLeft(DrzewoCC::Node *te) {
    if(te->right == NIL)
        return false;

    Node *n = te->right;

    te->right = n->left;
    if(n->left != NIL)
        n->left->parent = te;

    n->parent = te->parent;
    if(te->parent == NIL)
        root = n;
    else if(te == te->parent->left)
        te->parent->left = n;
    else
        te->parent->right = n;

    n->left = te;
    te->parent = n;

    return true;
}

bool DrzewoCC::addFix(DrzewoCC::Node *te) {
    Node *y;

    while(te->parent->color == RED) {
        if(te->parent == te->parent->parent->left) {
            y = te->parent->parent->right;
            if(y->color == RED) {
                te->parent->color = BLACK;
                y->color = BLACK;
                te->parent->parent->color = RED;
                te = te->parent->parent;
            } else {
                if (te == te->parent->right) {
                    te = te->parent;
                    rotateLeft(te);
                }
                te->parent->color = BLACK;
                te->parent->parent->color = RED;
                rotateRight(te->parent->parent);
            }
        }
        else {
            y = te->parent->parent->left;
            if(y->color == RED) {
                te->parent->color = BLACK;
                y->color = BLACK;
                te->parent->parent->color = RED;
                te = te->parent->parent;
            } else {
                if(te == te->parent->left) {
                    te = te->parent;
                    rotateLeft(te);
                }
                te->parent->color = BLACK;
                te->parent->parent->color = RED;
                rotateRight(te->parent->parent);
            }
        }
    }

    root->color = BLACK;
    return true;
}

bool DrzewoCC::isEmpty() {
    return treeSize == 0;
}

string DrzewoCC::output(DrzewoCC::Node *te) {
    string color, output;

    if(te->color == BLACK)
        color = "B";
    else
        color = "R";

    return to_string(te->value) + color;
}