#include "ConcatStringTree.h"

// Section 3.2: class ConcatStringTree
// Implementation for Tree Node
ConcatStringTree::Node::Node() : data(NULL), length(0), leftLength(0), left(NULL), right(NULL), parTree(NULL), checkRootOfSubRev(false)
{
    parTree = new ParentsTree;
}
ConcatStringTree::Node::Node(const char *s) : leftLength(0), left(NULL), right(NULL), parTree(NULL), checkRootOfSubRev(false)
{
    length = 0;
    while (s[length] != '\0') length++;

    data = new char[length + 1];
    for (int i = 0; i < length; i++) data[i] = s[i];
    data[length] = '\0';

    parTree = new ParentsTree;
}
ConcatStringTree::Node::Node(string s) : leftLength(0), left(NULL), right(NULL), parTree(NULL), checkRootOfSubRev(false)
{
    length = s.size();

    data = new char[length + 1];
    for (int i = 0; i < length; i++) data[i] = s[i];
    data[length] = '\0';

    parTree = new ParentsTree;
}
ConcatStringTree::Node::~Node()
{
    if (this->data != NULL) delete[] this->data;
    if (this->parTree != NULL) delete this->parTree;
    this->data = NULL;
    this->parTree = NULL;
}
void ConcatStringTree::Node::addIDForChildren(Node *node) {
    int id = node->parTree->getId();
    if (node->left != NULL) node->left->parTree->insert(id);
    if (node->right != NULL) node->right->parTree->insert(id);
}

// Implementation for ConcatStringTree (public and private functions)

// Constructors (3.2.1)
ConcatStringTree::ConcatStringTree() : root(NULL) {}
ConcatStringTree::ConcatStringTree(const char * s)
{
    root = new Node(s);
}
// 3.2.2
int ConcatStringTree::length() const
{
    return root->length;
}
// 3.2.3
char ConcatStringTree::get(int index) const
{
    if (index < 0 || index > root->length-1) throw out_of_range("Index of string is invalid!");
    Node *p = root;
    while (p != NULL) {
        if (index < p->leftLength) {
            // When p->left == NULL, p has no left sub tree --> p->leftLength=0 --> index >= p->leftLength
            p = p->left;
        }
        else {
            index -= p->leftLength;
            if (p->right == NULL) return p->data[index];
            p = p->right;
        }
    }
    return '\0';
}
// 3.2.4
int ConcatStringTree::indexOfRec(Node *node, char c) const
{
    if (node == NULL) return -1;
    if (node->left == nullptr && node->right == nullptr) {
        // Leaf nodes: no sub trees, only contain data
        for (int i = 0; i < node->length; i++) {
            if (node->data[i] == c) return i;
        }
        return -1;
    }
    int index_left = indexOfRec(node->left, c);
    if (index_left != -1) {
        return index_left;
    }
    int index_right = indexOfRec(node->right, c);
    if (index_right != -1) {
        return index_right + node->leftLength;
    }
    return -1;
}
int ConcatStringTree::indexOf(char c) const
{
    return indexOfRec(root, c);
}
// 3.2.5
string ConcatStringTree::preOrderRec(Node *node) const
{
    if (node == NULL) return "";
    string res = ";(LL=" + to_string(node->leftLength) + ",L=" + to_string(node->length) + ",";
    if (node->data == NULL) {
        res += "<NULL>)";
    }
    else {
        res += "\"";
        res += node->data;
        res += "\")";
    }
    res += preOrderRec(node->left);
    res += preOrderRec(node->right);
    return res;
}
string ConcatStringTree::toStringPreOrder() const
{
    if (root == NULL) return "";
    string res = "ConcatStringTree[(LL=" + to_string(root->leftLength) + ",L=" + to_string(root->length) + ",";
    if (root->data == NULL) {
        res += "<NULL>)";
    }
    else {
        res += "\"";
        res += root->data;
        res += "\")";
    }
    res += preOrderRec(root->left);
    res += preOrderRec(root->right);
    res += "]";
    return res;
}
// 3.2.6
string ConcatStringTree::toStringRec(Node *node) const
{
    if (node == NULL) return "";
    string res = "";
    if (node->left == NULL && node->right == NULL) {
        // Leaf nodes: no sub trees, only contain data
        res = node->data;
        return res;
    }
    res += toStringRec(node->left);
    res += toStringRec(node->right);
    return res;
}
string ConcatStringTree::toString() const
{
    string res = "ConcatStringTree[\"";
    res += toStringRec(root);
    res += "\"]";
    return res;
}
// 3.2.7
ConcatStringTree ConcatStringTree::concat(const ConcatStringTree &otherS) const
{
    ConcatStringTree res;
    res.root = new Node();

    (res.root)->left = this->root;
    (res.root)->right = otherS.root;
    (res.root)->data = NULL;
    (res.root)->length = this->root->length + otherS.root->length;
    (res.root)->leftLength = this->root->length;

    (res.root)->addIDForChildren(res.root);
    return res;
}
// 3.2.8
ConcatStringTree::Node *ConcatStringTree::subRec(Node *node, int from, int to) const
{
    if (node == NULL || from < 0 || from > node->length-1 || to < 0 || to > node->length || from >= to)
        return NULL;
    if (node->left == NULL && node->right == NULL) {
        // Leaf nodes: no sub trees, only contain data
        string tmp(node->data);
        tmp = tmp.substr(from, to-from);
        Node *res_node = new Node(tmp);
        return res_node;
    }
    Node *res_node = new Node;

    if (node->leftLength <= from) {
        res_node->left = NULL;
        res_node->right = subRec(node->right, from - node->leftLength, to - node->leftLength);
    }
    else if (node->leftLength >= to) {
        res_node->left = subRec(node->left, from, to);
        res_node->right = NULL;
    }
    else {
        res_node->left = subRec(node->left, from, node->leftLength);
        res_node->right = subRec(node->right, 0, to - node->leftLength);
    }
    res_node->data = NULL;
    res_node->leftLength = ((res_node->left == NULL) ? 0 : res_node->left->length);
    res_node->length = res_node->leftLength + ((res_node->right == NULL) ? 0 : res_node->right->length);

    res_node->addIDForChildren(res_node);
    return res_node;
}
ConcatStringTree ConcatStringTree::subString(int from, int to) const
{
    if (from < 0 || from > root->length-1) throw out_of_range("Index of string is invalid!");
    if (to   < 0 || to   > root->length)   throw out_of_range("Index of string is invalid!");
    if (from >= to) throw logic_error("Invalid range!");

    ConcatStringTree res;
    res.root = subRec(root, from, to);
    (res.root)->checkRootOfSubRev = true;
    return res;
}
// 3.2.9
void ConcatStringTree::invertRec(Node *node) const
{
    if (node == NULL) return;
    if (node->left == NULL && node->right == NULL) {
        // Leaf nodes: no sub trees, only contain data
        // Reverse the string data in leaf nodes
        string tmp(node->data);
        string tmp_rev(tmp.rbegin(), tmp.rend());
        for (int i = 0; i < node->length; i++) node->data[i] = tmp_rev[i];
        return;
    }
    swap(node->left, node->right);
    invertRec(node->left);
    invertRec(node->right);
    node->leftLength = ((node->left == NULL) ? 0 : node->left->length);
    node->length = node->leftLength + ((node->right == NULL) ? 0 : node->right->length);
}
ConcatStringTree ConcatStringTree::reverse() const
{
    ConcatStringTree res = subString(0, root->length);
    invertRec(res.root);
    return res;
}
// Destructor (3.2.10)
void ConcatStringTree::clearBinaryTree(Node *node)
{
    if (node == NULL) return;
    clearBinaryTree(node->left);
    clearBinaryTree(node->right);
    delete node;
}
void ConcatStringTree::clear(Node *node)
{
    // If node's parTree is empty:
    //   If the node is the root of the tree created by subString or reverse:
    //     Delete this node like deleting a normal binary tree
    //   Else:
    //     Go on to delete the node's id in its children and recursively check for its children's parTree and finally delete this node
    // Else stop the deletion
    if (node == NULL) return;
    if (node->parTree->isEmpty()) {
        if (node->checkRootOfSubRev) {
            clearBinaryTree(node);
            return;
        }
        int id = node->parTree->getId();
        if (node->left != NULL) {
            node->left->parTree->remove(id);
            clear(node->left);
        }
        if (node->right != NULL) {
            node->right->parTree->remove(id);
            clear(node->right);
        }
        delete node;
    }
}
ConcatStringTree::~ConcatStringTree()
{
    // Delete root's id in its parTree
    // Clear the root (above)
    int id = root->parTree->getId();
    root->parTree->remove(id);
    clear(root);
}

// Section 3.3: class ParentsTree
//// Part 1: Implementation for ParentsTree (AVLNodes and methods)
int ParentsTree::id_max = 1;
// AVLNode
ParentsTree::AVLNode::AVLNode() : left(NULL), right(NULL), height(1)
{
    if (id_max > 10000000) throw overflow_error("Id is overflow!");
    this->id = id_max++;
}
ParentsTree::AVLNode::AVLNode(int id_of_par_node) : id(id_of_par_node), left(NULL), right(NULL), height(1) {}
// Constructor
ParentsTree::ParentsTree() : count(1)
{
    root = new AVLNode();
    id_node = root->id;
}
// Destructor
void ParentsTree::clearRec(AVLNode *node) {
    if (node == NULL) return;
    clearRec(node->left);
    clearRec(node->right);
    delete node;
}
ParentsTree::~ParentsTree()
{
    clearRec(root);
}
// Get id
int ParentsTree::getId() const
{
    return id_node;
}
// Check empty
bool ParentsTree::isEmpty() const
{
    return (count == 0);
}
// Rebalancing AVL Tree
int ParentsTree::height(AVLNode *node)
{
    if (node == NULL) return 0;
    return (1 + max( height(node->left), height(node->right) ));
}
int ParentsTree::diff(AVLNode *node)
{
    if (node == NULL) return 0;
    int l = ((node->left == NULL) ? 0 : node->left->height);
    int r = ((node->right == NULL) ? 0 : node->right->height);
    return l - r;
}
ParentsTree::AVLNode *ParentsTree::rotateRight(AVLNode *node)
{
    AVLNode *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    node->height = height(node);
    tmp->height = height(tmp);
    return tmp;
}
ParentsTree::AVLNode *ParentsTree::rotateLeft(AVLNode *node)
{
    AVLNode *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    node->height = height(node);
    tmp->height = height(tmp);
    return tmp;
}
void ParentsTree::rebalance(AVLNode *& node)
{
    int balance = diff(node);
    if (balance > 1 && diff(node->left) >= 0) {
        // Left of left
        node = rotateRight(node);
        return;
    }
    if (balance > 1 && diff(node->left) == -1) {
        // Right of left
        node->left = rotateLeft(node->left);
        node = rotateRight(node);
        return;
    }
    if (balance < -1 && diff(node->right) == 1) {
        // Left of right
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
        return;
    }
    if (balance < -1 && diff(node->right) <= 0) {
        // Right of right
        node = rotateLeft(node);
        return;
    }
}
// Searching
bool ParentsTree::searchRec(AVLNode *node, const int &id) const
{
    if (node == NULL) return false;
    if (id < node->id) return searchRec(node->left, id);
    if (id > node->id) return searchRec(node->right, id);
    return true;
}
// Insertion
ParentsTree::AVLNode *ParentsTree::insertRec(AVLNode *&node, const int &id)
{
    if (node == NULL) {
        node = new AVLNode(id);
        return node;
    }
    if (id < node->id) {
        node->left = insertRec(node->left, id);
    }
    else {
        node->right = insertRec(node->right, id);
    }
    node->height = height(node);
    rebalance(node);
    return node;
}
void ParentsTree::insert(const int &id)
{
    if (root == NULL) {
        root = new AVLNode(id);
        return;
    }
    root = insertRec(root, id);
    ++count;
}
// Deletion
ParentsTree::AVLNode *ParentsTree::removeRec(AVLNode *&node, const int &id)
{
    if (node == NULL) return NULL;
    if (id < node->id) {
        node->left = removeRec(node->left, id);
    }
    else if (id > node->id) {
        node->right = removeRec(node->right, id);
    }
    else {
        if (node->right == NULL) {
            AVLNode *tmp = node;
            node = node->left;
            delete tmp;
            return node;
        }
        else if (node->left == NULL) {
            AVLNode *tmp = node;
            node = node->right;
            delete tmp;
            return node;
        }
        else {
            AVLNode *tmp = node->left;
            while (tmp->right != NULL) tmp = tmp->right;
            node->id = tmp->id;
            node->left = removeRec(node->left, tmp->id);
        }
    }
    node->height = height(node);
    rebalance(node);
    return node;
}
void ParentsTree::remove(const int &id)
{
    if (!searchRec(root, id)) return;
    root = removeRec(root, id);
    --count;
}
// Size (3.3.1.1)
int ParentsTree::size() const
{
    return this->count;
}
// ToString Pre Order (3.3.1.2)
string ParentsTree::toStringRec(AVLNode *node) const
{
    if (node == NULL) return "";
    string res = ";(id=" + to_string(node->id) + ")";
    res += toStringRec(node->left);
    res += toStringRec(node->right);
    return res;
}
string ParentsTree::toStringPreOrder() const
{
    string res = "ParentsTree[(id=" + to_string(root->id) + ")";
    res += toStringRec(root->left);
    res += toStringRec(root->right);
    res += "]";
    return res;
}
//// Part 2: Addition for methods of ConcatStringTree
// 3.3.2.1
int ConcatStringTree::getParTreeSize(const string &query) const
{
    int n = query.size();
    for (int i = 0; i < n; i++) {
        if (query[i] != 'l' && query[i] != 'r') throw runtime_error("Invalid character of query");
    }
    Node *p = this->root;
    if (p == NULL) throw runtime_error("Invalid query: reaching NULL");
    for (int i = 0; i < n; i++) {
        if (query[i] == 'l') p = p->left;
        else p = p->right;
        if (p == NULL) throw runtime_error("Invalid query: reaching NULL");
    }
    return p->parTree->size();
}
// 3.3.2.2
string ConcatStringTree::getParTreeStringPreOrder(const string &query) const
{
    int n = query.size();
    for (int i = 0; i < n; i++) {
        if (query[i] != 'l' && query[i] != 'r') throw runtime_error("Invalid character of query");
    }
    Node *p = this->root;
    if (p == NULL) throw runtime_error("Invalid query: reaching NULL");
    for (int i = 0; i < n; i++) {
        if (query[i] == 'l') p = p->left;
        else p = p->right;
        if (p == NULL) throw runtime_error("Invalid query: reaching NULL");
    }
    return p->parTree->toStringPreOrder();
}

// Section 3.4: class ReducedConcatStringTree and LitStringHash
//// Part 1:
//// Part 2: