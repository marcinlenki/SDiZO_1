#ifndef PROJEKT_DRZEWOCC_H
#define PROJEKT_DRZEWOCC_H
using namespace std;
const int RED = 0;
const int BLACK = 1;

class DrzewoCC {
public:
    struct Node {
        int color;
        int value;
        Node *left, *right, *parent;
    };

    unsigned int treeSize;
    Node *NIL;
    Node *root;

    bool isEmpty();
    bool rotateRight(Node *te);
    bool rotateLeft(Node *te);
    bool addFix(Node *te);
    bool deleteFix(Node *te);
    void RBTransplant(Node *u, Node *v);
    void showInOrder(Node *te);
    void clear(Node *te);
    Node * treeMin(Node *te);

public:
    DrzewoCC();
    ~DrzewoCC();
    void fillFromFile(const char* name);
    void show();
    void showInOrder();
    Node* search(int value);
    bool add(int value);
    bool remove(int value);
    void clear();
    string output(Node *te);
};



#endif