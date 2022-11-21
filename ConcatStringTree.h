#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class ParentsTree; // forward declaration
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
    void clearBinaryTree(Node *node);
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
        ParentsTree *parTree;
        bool checkRootOfSubRev;

        friend class ConcatStringTree;
    public:
        Node();
        Node(const char *s);
        Node(string s);
        ~Node();
        void addIDForChildren(Node *node);
    };
};

class ParentsTree {
// Forward declaration of AVLNode and static member id_max
public:
    class AVLNode;
    static int id_max;
// Declare attributes and methods for ParentsTree
private:
    AVLNode *root;
    int id_node;
    int count;
private:
    int height(AVLNode *node);
    int diff(AVLNode *node);
    AVLNode *rotateRight(AVLNode *node);
    AVLNode *rotateLeft(AVLNode *node);
    void rebalance(AVLNode * & node);
    bool searchRec(AVLNode *node, const int &id) const;
    AVLNode *insertRec(AVLNode *&node, const int &id);
    AVLNode *removeRec(AVLNode *&node, const int &id);
    void clearRec(AVLNode *node);
    string toStringRec(AVLNode *node) const;
public:
    ParentsTree();
    ~ParentsTree();
    void insert(const int &id);
    void remove(const int &id);
    int getId() const;
    bool isEmpty() const;

    int size() const;
    string toStringPreOrder() const;

public:
    class AVLNode {
    private:
        int id;
        AVLNode *left;
        AVLNode *right;
        int height;

        friend class ParentsTree;
    public:
        AVLNode();
        AVLNode(int id_of_par_node);
    };
};

class ReducedConcatStringTree; // forward declaration
class LitStringHash; // forward declaration

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
    LitStringHash(const HashConfig & hashConfig) {};
    int getLastInsertedIndex() const {return -1;};
    string toString() const {return "";};
};

class ReducedConcatStringTree /* */ {
public:
    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash) {};
    LitStringHash *litStringHash;
};

#endif // __CONCAT_STRING_TREE_H__