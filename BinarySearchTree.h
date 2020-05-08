#include <iostream>
using namespace std;
#include "BinaryTreeNode.h"

class BinarySearchTree {
 private:
  BinaryTreeNode<int> *root;

 public:
  BinarySearchTree() { root = NULL; }

  BinarySearchTree(int data) { root = new BinaryTreeNode<int>(data); }

  ~BinarySearchTree() { delete root; }

  bool hasData(int data) { return hasData(root, data); }

  void insert(int data) { root = insert(root, data); }

  void deleteData(int data) { root = deleteData(root, data); }

  void printTree() { printTree(root); }

 private:
  bool hasData(BinaryTreeNode<int> *node, int data) {
    if (node == NULL) return false;
    if (data == node->data) return true;
    if (data < node->data) return hasData(node->left, data);
    if (data > node->data) return hasData(node->right, data);
    return false;
  }

  BinaryTreeNode<int> *insert(BinaryTreeNode<int> *node, int data) {
    if (root == NULL) return new BinaryTreeNode<int>(data);
    if (data > root->data) node->right = insert(root->right, data);
    if (data < root->data) node->left = insert(root->left, data);
    return node;
  }

  BinaryTreeNode<int> *deleteData(BinaryTreeNode<int> *node, int data) {
    if (node == NULL) return NULL;
    if (node->data == data) {
      // Leaf Node
      if (!node->left && !node->right) {
        delete node;
        return NULL;
      }
      // Only right node exists
      if (node->left && !node->right) {
        BinaryTreeNode<int> *temp = node->left;
        node->left = NULL;
        delete node;
        return temp;
      }
      // Only right node exists
      if (node->right && !node->left) {
        BinaryTreeNode<int> *temp = node->right;
        node->right = NULL;
        delete node;
        return temp;
      }
      // Both exists
      int smallest = minNode(node->right);
      node->data = smallest;
      node->right = deleteData(node->right, smallest);
      return node;
    } else if (data < node->data) {
      node->left = deleteData(node->left, data);
    } else {
      node->right = deleteData(node->right, data);
    }
    return node;
  }

  int maxNode(BinaryTreeNode<int> *node) {
    if (node == NULL) return INT_MIN;
    return max(node->data, max(maxNode(node->left), maxNode(node->right)));
  }

  int minNode(BinaryTreeNode<int> *node) {
    if (node == NULL) return INT_MAX;
    return min(node->data, min(minNode(node->left), minNode(node->right)));
  }

  void printTree(BinaryTreeNode<int> *root) {
    if (root == NULL) {
      return;
    }
    cout << root->data << ':';
    if (root->left != NULL) {
      cout << "L:" << root->left->data << ',';
    }
    if (root->right != NULL) {
      cout << "R:" << root->right->data;
    }
    cout << endl;
    printTree(root->left);
    printTree(root->right);
  }
};