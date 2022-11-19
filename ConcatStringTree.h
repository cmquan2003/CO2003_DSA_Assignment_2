#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class ParentsTree;
class ConcatStringTree {
// Forward declaration of Node
public:
    class Node;
// Declare attributes and methods for ConcatStringTree
private:
    Node *root;

private:
    ConcatStringTree();
    int indexOfRec(Node *node, char c) const;
    string preOrderRec(Node *node) const;
    string toStringRec(Node *node) const;
    Node *subRec(Node *node, int from, int to) const;
    void invertRec(Node *node) const;
    void clear(Node *node);
public:
    ConcatStringTree(const char * s);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    string toStringPreOrder() const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree & otherS) const;
    ConcatStringTree subString(int from, int to) const;
    ConcatStringTree reverse() const;
    ~ConcatStringTree();

    int getParTreeSize(const string & query) const;
    string getParTreeStringPreOrder(const string & query) const;

public:
    class Node {
    private:
        char *data;
        int length;
        int leftLength;
        Node *left;
        Node *right;

        friend class ConcatStringTree;
    public:
        Node();
        Node(const char *s);
        Node(string s);
        ~Node();
    };
};

class ReducedConcatStringTree; // forward declaration
class LitStringHash;

class HashConfig {
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    friend class ReducedConcatStringTree;
    friend class LitStringHash;
// public:
//     HashConfig() {};
//     HashConfig(int p, double c1, double c2, double lambda, int alpha, int initSize) {};
};

class LitStringHash {
public:
    LitStringHash(const HashConfig & hashConfig);
    int getLastInsertedIndex() const;
    string toString() const;
};

class ReducedConcatStringTree /* */ {
public:
    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash);
    LitStringHash *litStringHash;
};

#endif // __CONCAT_STRING_TREE_H__