#include "ConcatStringTree.h"

// Section 3.2: class ConcatStringTree
// Implementation for Tree Node
ConcatStringTree::Node::Node() : data(NULL), length(0), leftLength(0), left(NULL), right(NULL) {}
ConcatStringTree::Node::Node(const char *s) : leftLength(0), left(NULL), right(NULL)
{
    length = 0;
    while (s[length] != '\0') length++;

    data = new char[length + 1];
    for (int i = 0; i < length; i++) data[i] = s[i];
    data[length] = '\0';
}
ConcatStringTree::Node::Node(string s) : leftLength(0), left(NULL), right(NULL)
{
    length = s.size();

    data = new char[length + 1];
    for (int i = 0; i < length; i++) data[i] = s[i];
    data[length] = '\0';
}
ConcatStringTree::Node::~Node()
{
    if (this->data != NULL) delete[] this->data;
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

    return res_node;
}
ConcatStringTree ConcatStringTree::subString(int from, int to) const
{
    if (from < 0 || from > root->length-1) throw out_of_range("Index of string is invalid!");
    if (to   < 0 || to   > root->length)   throw out_of_range("Index of string is invalid!");
    if (from >= to) throw logic_error("Invalid range!");

    ConcatStringTree res;
    res.root = subRec(root, from, to);
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
void ConcatStringTree::clear(Node *node)
{
    if (node == NULL) return;
    clear(node->left);
    clear(node->right);
    delete node;
}
ConcatStringTree::~ConcatStringTree()
{
    // this->clear(root);
}
// 3.3.1
int ConcatStringTree::getParTreeSize(const string &query) const
{
    return -1;
}
// 3.3.2
string ConcatStringTree::getParTreeStringPreOrder(const string &query) const
{
    return "";
}

