#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class ParentsTree; // forward declaration
class ConcatStringTree {
// Forward declaration of Node
public:
    class Node;
// Declare attributes and methods for ConcatStringTree
protected:
    Node *root;

protected:
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
    protected:
        char *data;
        int length;
        int leftLength;
        Node *left;
        Node *right;
        ParentsTree *parTree;
        bool checkRootOfSubRev;

        friend class ConcatStringTree;
        friend class ReducedConcatStringTree;
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
public:
    HashConfig(int p, double c1, double c2, double lambda, double alpha, int initSize);
    HashConfig();
    HashConfig &operator=(const HashConfig &otherH);
};

enum STATUS {NIL, DELETED, NON_EMPTY};
class LitStringHash {
public:
    class LitString; // forward declaration
private:
    HashConfig hashConfig;
    int table_size;
    LitString **table;
    STATUS *status;
    int count;
    int last_inserted;

    friend class ReducedConcatStringTree;
private:
    int hash(const char *s);
    int hp(int hashed, int i);
    void rehash();
    void insertRehash(LitString *lit);
    bool strcomp(const char *s1, const char *s2);
    int search(const char *s);
    void insert(const char *s);
    void remove(const char *s);
    void initialize();
    void clear();
public:
    LitStringHash(const HashConfig & hashConfig);
    int getLastInsertedIndex() const;
    string toString() const;

    ~LitStringHash();
public:
    class LitString {
    private:
        char *data;
        int count_link;

    friend class LitStringHash;
    friend class ReducedConcatStringTree;
    public:
        LitString(const char *s);
        ~LitString();
    };
};

class ReducedConcatStringTree : public ConcatStringTree {
public:
    LitStringHash *litStringHash;

    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash);
    ReducedConcatStringTree();
    void clear(Node *node);
    ~ReducedConcatStringTree();
    ReducedConcatStringTree concat(const ReducedConcatStringTree & otherS) const;
    void subString(int from, int to) const;
    void reverse() const;
    // Reuse methods:
    // int length() const;
    // char get(int index) const;
    // int indexOf(char c) const;
    // string toStringPreOrder() const;
    // string toString() const;
    
    // int getParTreeSize(const string & query) const;
    // string getParTreeStringPreOrder(const string & query) const;
};

#endif // __CONCAT_STRING_TREE_H__