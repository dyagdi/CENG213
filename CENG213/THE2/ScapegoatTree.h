#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    void removeAllNodes(Node<T>* node);
    int getHeight(Node<T>* node) const;
    int getSize(Node<T>* node) const;
    const T &get(const T &element, Node<T>* r) const;
    /*bool getElement(const T &element, Node<T>* r) const;*/
    void insert(const T &element, Node<T>* &r);
    const T &getMax(Node<T>* node) const;
    const T &getMin(Node<T>* node) const;
    void remove(Node<T>* &node, const T &element);
    void preOrder(Node<T> *node);
    Node<T>* deep_copy(Node<T>* rhs);
    int storeInArray(Node<T>* &ptr, Node<T>* arr[], int i)const;
    Node<T>* searchforparentnode(Node<T>* pRoot, const T &value)const;
    Node<T>* buildBalancedFromArray(Node<T> **a, int i, int n);
    void rebuildTree(Node<T> *&u);
    int findMax(int l, int r) const;
    Node<T>* getCeiling(Node<T> *node, const T &element) const;
    Node<T>* getFloor(Node<T> *node, const T &element) const;
    Node<T> * getNext(Node<T> *node, const T &element) const;
    bool contains(Node<T>* node, T element);
   Node<T> *copyConstructor(const Node<T> *node);
private: // DO NOT CHANGE THIS PART.
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    /* TODO */
    root = NULL;
    upperBound = 0;
}


template <class T>
Node<T> *ScapegoatTree<T>::copyConstructor(const Node<T> *node)

{
/*
    if (base == NULL)
    {
        root = NULL;
    }
    else
    {

        this->insert(base->element);
        if (base->left)
        {
            copyConstructor(root, base->left);
        }
        if (base->right)
        {
            copyConstructor(root, base->right);
        }
    }
    */
    if (node != NULL) 
    {
        return new Node<T>(node->element, this->copyConstructor(node->left), this->copyConstructor(node->right)   );
    }

    return NULL;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    this->root = this->copyConstructor(obj.root);
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    /* TODO */
    removeAllNodes();
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    /* TODO */
    if (root == NULL) return true;
   
    return false;
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    /* TODO */
    int n = getHeight(root);
    return n;
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    /* TODO */
    int n = getSize(root);
    return n;
}


static float const log32(int n) {
  double const log23 = 2.4663034623764317;
  return (float)(log23 * log(n));
}


template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    /* TODO */
    if (contains(root, element)){
        return false;
    }
    insert(element, root);
    int h = getHeight(root);
    if (h > log32(upperBound))
    {
        Node<T> *p = searchforparentnode(root, element);
        Node<T>* p_parent = searchforparentnode(root, p->element);
        while (3*getSize(p) <= 2*getSize(p_parent)){
            p = searchforparentnode(root, p->element);
            p_parent = searchforparentnode(root, p->element);
        }
        Node<T>* temp = searchforparentnode(root, p->element);
        rebuildTree(temp);
    }
    return true;
}

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    /* TODO */
    if (!contains(root, element)){
        return false;
    }
    remove(root, element);
    float half_upper = (float)(upperBound/(float)2);
    if (half_upper <= getSize(root) && upperBound >= getSize(root)){
        return true;
    }
    else {
        balance();
        upperBound = getSize(root);
    }
    return true;
}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    /* TODO */
    removeAllNodes(root);
    root=NULL;
    upperBound=0;
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    /* TODO */
    return get(element, root);
}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == inorder) {
        if (isEmpty()) {
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (node == NULL) return;
        std::cout << "\t" << node->element;
       
       
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
       
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
       
    } else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
          return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == postorder) {
        /* TODO */
        if (node == NULL) return;
       
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
       
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
       
       
        std::cout << "\t" << node->element;
    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    if(this != &rhs)
    {
        if (rhs.root != NULL){
            removeAllNodes();
            Node<T> *node = rhs.root;
            preOrder(node);
        }
        else {
            root = NULL;
        }
    }
    upperBound = rhs.upperBound;
    return *this;
}

template<class T>
void ScapegoatTree<T>::balance() {
    /* TODO */
    rebuildTree(root);
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    /* TODO */
    if (getCeiling(root, element))
    return getCeiling(root, element) -> element;
   
    throw NoSuchItemException();
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    /* TODO */
    if (getFloor(root, element))
    return getFloor(root, element) -> element;
   
    throw NoSuchItemException();
}

template<class T>
const T &ScapegoatTree<T>::getMin() const {
    /* TODO */
    return getMin(root);
}

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    /* TODO */
    return getMax(root);
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    /* TODO */
    if (getNext(root, element))
    return getNext(root, element) -> element;
   
    throw NoSuchItemException();
}

// My Helper Functions


template<class T>
void ScapegoatTree<T>::removeAllNodes(Node<T>* node){
    if (node == NULL) return;
   
    Node<T>* temp;
    temp = node;
    removeAllNodes(node->left);
    removeAllNodes(node->right);
    delete temp;
    node = NULL;
    upperBound = 0;
   
}

template<class T>
int ScapegoatTree<T>::getHeight(Node<T>* node) const {
    int h = -1;
    if (node){
        int lHeight = getHeight(node->left);
        int rHeight = getHeight(node->right);
        int maxHeight = findMax(lHeight+1, rHeight+1);
        h = maxHeight;
    }
    return h;
}

template<class T>
int ScapegoatTree<T>::getSize(Node<T>* node) const {
    if (node == NULL){
        return 0;
    }
    return (getSize(node->left) + 1 + getSize(node->right));
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element, Node<T>* r) const {
    if (r == NULL){
        throw NoSuchItemException();
    }
    else if (r != NULL && r->element == element){
        return r->element;
    }
    else if (r->element < element){
        return get(element, r->right);
    }
    else if (r->element > element){
        return get(element, r->left);
    }
}

/*template<class T>
bool ScapegoatTree<T>::getElement(const T &element, Node<T>* r) const {
    if (r == NULL)
        return false;
 
    if (r->element == element)
        return true;
 
   
    bool res1 = getElement(element, r->left);
   
    if(res1) return true;
 
   
    bool res2 = getElement(element, r->right);
 
    return res2;
   
}*/

template<class T>
bool ScapegoatTree<T>::contains(Node<T>* node, T element) {
  if (node == NULL) return false;
  else {
    if (element == node->element)
      return true;
    else if (element < node->element)
      return contains(node->left, element);
    else if (element > node->element)
      return contains(node->right, element);
  }
}

template<class T>
void ScapegoatTree<T>::insert(const T &element, Node<T>* &r) {
    if (r == NULL) {
        r = new Node<T>(element, NULL, NULL);
        upperBound++;
    }
    else if (element > r->element) {
        insert(element, r->right);
    }
    else if (element < r->element) {
        insert(element, r->left);
    }
}

template<class T>
const T &ScapegoatTree<T>::getMax(Node<T>* node) const {
    Node<T>* curr = node;
    if (node == NULL){
        throw NoSuchItemException();
    }
    while (curr -> right != NULL){
        curr = curr -> right;
    }
    return curr->element;
}

template<class T>
const T &ScapegoatTree<T>::getMin(Node<T>* node) const {
    Node<T>* curr = node;
    if (node == NULL){
        throw NoSuchItemException();
    }
    while (curr -> left != NULL){
        curr = curr -> left;
    }
    return curr->element;
}

template<class T>
void ScapegoatTree<T>::remove(Node<T>* &node, const T &element) {
    if (node == NULL){
        return;
    }
    if (element < node->element){
        remove(node->left, element);
    }
    else if (element > node->element){
        remove(node->right, element);
    }
    else {
        if (node->left == NULL && node->right == NULL){
            Node<T>* temp = node;
            delete temp;
            node = NULL;
        }
        else if (node->left == NULL && node->right != NULL){
            Node<T>* temp = node;
            node = node -> right;
            delete temp;
        }
        else if (node->right == NULL && node->left != NULL){
            Node<T>* temp = node;
            node = node->left;
            delete temp;
        }
        else if (node->right != NULL && node->left != NULL){
            Node<T>* temp = node->left;
            while (temp->right != NULL){
                temp = temp -> right;
            }
            node->element = temp->element;
            remove(node->left, node->element);
        }
        return;
    }
}

template<class T>
void ScapegoatTree<T>::preOrder(Node<T> *node) {
    insert(node->element);

    if(node->left != NULL)
        preOrder(node->left);
    if(node->right != NULL)
        preOrder(node->right);
}

template<class T>
Node<T>* ScapegoatTree<T>::deep_copy(Node<T>* rhs) {
    if (rhs)
    {
        Node<T>* lhs = new Node<T>();
        lhs->element = rhs->element;
        lhs->left = deep_copy(rhs->left);
        lhs->right = deep_copy(rhs->right);
        return lhs;
    }
    else
    {
        return NULL;
    }
}

template<class T>
int ScapegoatTree<T>::storeInArray(Node<T>* &ptr, Node<T>* arr[], int i) const{
  if (ptr == NULL)
    return i;
 
  i = storeInArray(ptr->left, arr, i);
  arr[i++] = ptr;
  return storeInArray(ptr->right, arr, i);
}

template<class T>
Node<T>* ScapegoatTree<T>::searchforparentnode(Node<T>* pRoot, const T &value) const{
    if (pRoot == NULL || pRoot->element == value)
       return NULL;

    if( (pRoot->left != NULL && pRoot->left->element == value)
        || (pRoot->right != NULL && pRoot->right->element == value))
       return pRoot;

    if(pRoot->element > value)
       return searchforparentnode(pRoot->left,value);

    if(pRoot->element < value)
       return searchforparentnode(pRoot->right,value);
}

template<class T>
Node<T>* ScapegoatTree<T>::buildBalancedFromArray(Node<T> **a, int i, int n) {
  if (n== 0)
    return NULL;
  int m = n / 2;
  if(n%2 == 0){
      m--;
  }
 
  a[i+m]->left = buildBalancedFromArray(a, i, m);
 
  if (a[i+m]->left != NULL){
      Node<T>* temp = searchforparentnode(root, a[i+m]->left->element);
      temp = a[i+m];
  }
 
  a[i+m]->right = buildBalancedFromArray(a, i+m+1, n-m-1);
  if (a[i+m]->right != NULL)
  {
      Node<T>* temp = searchforparentnode(root, a[i+m]->right->element);
      temp = a[i+m];
  }
 
  return a[i+m];
}

template<class T>
void ScapegoatTree<T>::rebuildTree(Node<T> *&u) {
  int n = getSize(u);
  Node<T> *p = searchforparentnode(root, u->element);
  Node<T> **a = new Node<T>* [n];
  storeInArray(u, a, 0);
  if (p == NULL)
  {
    root = buildBalancedFromArray(a, 0, n);
  }
  else if (p->right == u)
  {
    p->right = buildBalancedFromArray(a, 0, n);
  }
  else
  {
    p->left = buildBalancedFromArray(a, 0, n);
  }
  delete [] a;
}

template<class T>
int ScapegoatTree<T>::findMax(int l, int r) const{
    if (l > r){
        return l;
    }
    return r;
}

template<class T>
Node<T>* ScapegoatTree<T>::getCeiling(Node<T> *node, const T &element) const {
    if (node == NULL){
        return NULL;
    }
    if (node->element == element){
        return node;
    }
    if (node->element< element){
        getCeiling(node->right, element);
    }
    else {
        if (node->left == NULL){
            return node;
        }
        Node<T>* temp = getCeiling(node->left, element);
        if (temp == NULL){
            return node;
        }
        else if (temp->element< node->element){
            return temp;
        }
        else if (temp->element > node->element){
            return node;
        }
    }
}

template<class T>
Node<T>* ScapegoatTree<T>::getFloor(Node<T> *node, const T &element) const {
    if (node == NULL){
        return NULL;
    }
    if (node->element == element){
        return node;
    }
    if (node->element> element){
        getFloor(node->left, element);
    }
    else {
        if (node->right == NULL){
            return node;
        }
        Node<T>* temp = getFloor(node->right, element);
        if (temp == NULL){
            return node;
        }
        else if (temp->element< node->element){
            return node;
        }
        else if (temp->element > node->element){
            return temp;
        }
    }
}

template<class T>
Node<T> * ScapegoatTree<T>::getNext(Node<T> *node, const T &element) const {
    if (node == NULL){
        return NULL;
    }
    if (node->element <= element){
        return getNext(node->right, element);
    }
    else {
        if (node->left == NULL){
            return node;
        }
        Node<T>* temp = getNext(node->left, element);
        if (temp == NULL){
            return node;
        }
        else if (temp-> element > node->element){
            return node;
        }
        else if (temp-> element < node->element){
            return temp;
        }
    }
}


