#include <iostream>
using namespace std;
#include <bits/stdc++.h>

#include "BinaryTreeNode.h"
#include "Node.h"

BinaryTreeNode<int> *searchNode(BinaryTreeNode<int> *root, int searchTerm) {
  if (root == NULL || root->data == searchTerm) return root;
  if (searchTerm > root->data) return searchNode(root->right, searchTerm);
  return searchNode(root->left, searchTerm);
}

BinaryTreeNode<int> *takeInputLevelWise() {
  int rootData;
  cout << "Enter root data" << endl;
  cin >> rootData;

  if (rootData == -1) {
    return NULL;
  }

  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
  queue<BinaryTreeNode<int> *> q;
  q.push(root);
  while (!q.empty()) {
    BinaryTreeNode<int> *front = q.front();
    q.pop();
    int left, right;
    cout << "Enter left child of " << front->data << endl;
    cin >> left;
    cout << "Enter right child of " << front->data << endl;
    cin >> right;
    if (left != -1) {
      BinaryTreeNode<int> *leftNode = new BinaryTreeNode<int>(left);
      front->left = leftNode;
      q.push(leftNode);
    }
    if (right != -1) {
      BinaryTreeNode<int> *rightNode = new BinaryTreeNode<int>(right);
      front->right = rightNode;
      q.push(rightNode);
    }
  }
  return root;
}

void printLevelWise(BinaryTreeNode<int> *root) {
  if (root == NULL) {
    return;
  }
  queue<BinaryTreeNode<int> *> q;
  q.push(root);
  while (!q.empty()) {
    BinaryTreeNode<int> *front = q.front();
    q.pop();
    cout << front->data << ':';
    if (front->left != NULL) {
      cout << "L:" << front->left->data << ',';
      q.push(front->left);
    } else {
      cout << "L:" << -1 << ',';
    }
    if (front->right != NULL) {
      cout << "R:" << front->right->data;
      q.push(front->right);
    } else {
      cout << "R:" << -1;
    }
    cout << endl;
  }
}

bool isLeaf(BinaryTreeNode<int> *root) { return !root->left && !root->right; }

void elementsInRangeK1K2(BinaryTreeNode<int> *root, int k1, int k2) {
  if (root == NULL) return;
  if (k2 > root->data) elementsInRangeK1K2(root->right, k1, k2);
  if (k1 < root->data) elementsInRangeK1K2(root->left, k1, k2);
  if (root->data >= k1 && root->data <= k2) cout << root->data << ' ';
}

int maxNode(BinaryTreeNode<int> *root) {
  if (root == NULL) return INT_MIN;
  return max(root->data, max(maxNode(root->left), maxNode(root->right)));
}

int minNode(BinaryTreeNode<int> *root) {
  if (root == NULL) return INT_MAX;
  return min(root->data, min(minNode(root->left), minNode(root->right)));
}

void getInorder(BinaryTreeNode<int> *root, vector<int> &inorder) {
  if (!root) return;
  getInorder(root->left, inorder);
  inorder.push_back(root->data);
  getInorder(root->right, inorder);
}

// MARK:- Naive Approach
// **************************************************************************************
bool isBST(BinaryTreeNode<int> *root) {
  if (root == NULL) return true;
  return isBST(root->left) && isBST(root->right) &&
         maxNode(root->left) < root->data && minNode(root->right) >= root->data;
}
// **************************************************************************************

// MARK:- Better Approach
// **************************************************************************************
class IsBSTReturn {
 public:
  bool isBST;
  int min;
  int max;
  IsBSTReturn() {
    isBST = true;
    min = INT_MAX;
    max = INT_MIN;
  }
  IsBSTReturn(bool isBST, int min, int max) {
    this->isBST = isBST;
    this->min = min;
    this->max = max;
  }
};
IsBSTReturn isBSTBetter(BinaryTreeNode<int> *root) {
  if (root == NULL) return IsBSTReturn();
  IsBSTReturn leftAns = isBSTBetter(root->left);
  IsBSTReturn rightAns = isBSTBetter(root->right);
  int minimum = min(root->data, min(leftAns.min, rightAns.min));
  int maximum = max(root->data, max(leftAns.max, rightAns.max));
  bool isBST = (root->data > leftAns.max) && (root->data <= rightAns.min) &&
               leftAns.isBST && rightAns.isBST;
  return IsBSTReturn(isBST, minimum, maximum);
}
// **************************************************************************************

// MARK:- Best Approach
// **************************************************************************************
bool isBSTBestHelper(BinaryTreeNode<int> *root, int from, int to) {
  if (root == NULL) return true;
  if (root->data < from && root->data > to) return false;
  bool leftAns = isBSTBestHelper(root->left, from, root->data - 1);
  bool rightAns = isBSTBestHelper(root->right, root->data, to);
  return leftAns && rightAns;
}

bool isBSTBest(BinaryTreeNode<int> *root) {
  return isBSTBestHelper(root, INT_MIN, INT_MAX);
}
// **************************************************************************************

BinaryTreeNode<int> *constructTreeHelper(int *input, int start, int end) {
  if (start > end) return NULL;
  int mid = (start + end) / 2;
  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(input[mid]);
  root->left = constructTreeHelper(input, start, mid - 1);
  root->right = constructTreeHelper(input, mid + 1, end);
  return root;
}

BinaryTreeNode<int> *constructTree(int *input, int n) {
  return constructTreeHelper(input, 0, n - 1);
}

// Function to create a sorted linked list using a BST
pair<Node<int> *, Node<int> *> helper(BinaryTreeNode<int> *root) {
  if (root == NULL) return pair<Node<int> *, Node<int> *>(NULL, NULL);

  Node<int> *node = new Node<int>(root->data);

  pair<Node<int> *, Node<int> *> leftPair = helper(root->left);
  pair<Node<int> *, Node<int> *> rightPair = helper(root->right);

  pair<Node<int> *, Node<int> *> pair;
  pair.first = node;
  pair.second = node;

  if (leftPair.first != NULL && leftPair.second != NULL) {
    pair.first = leftPair.first;
    leftPair.second->next = node;
  }

  if (rightPair.first != NULL && rightPair.second != NULL) {
    pair.second->next = rightPair.first;
    pair.second = rightPair.second;
  }
  return pair;
}

Node<int> *constructBST(BinaryTreeNode<int> *root) {
  return helper(root).first;
}

vector<int> *findPath(BinaryTreeNode<int> *root, int data) {
  if (root == NULL) return NULL;
  if (root->data == data) {
    vector<int> *ans = new vector<int>();
    ans->push_back(root->data);
    return ans;
  }
  if (root->data > data) {
    vector<int> *leftAns = findPath(root->left, data);
    if (leftAns) {
      leftAns->push_back(root->data);
      return leftAns;
    }
    return NULL;
  } else {
    vector<int> *righAns = findPath(root->right, data);
    if (righAns) {
      righAns->push_back(root->data);
      return righAns;
    }
    return NULL;
  }
}

void insertElements(BinaryTreeNode<int> *root, vector<int> *v) {
  if (root == NULL) return;
  insertElements(root->left, v);
  v->push_back(root->data);
  insertElements(root->right, v);
}

void nodesSumToS(BinaryTreeNode<int> *root, int sum) {
  vector<int> *v = new vector<int>();
  insertElements(root, v);
  int i = 0, j = v->size() - 1;
  while (i < j) {
    int res = v->at(i) + v->at(j);
    if (res > sum) {
      j--;
    } else if (res < sum) {
      i++;
    } else {
      cout << v->at(i) << " " << v->at(j) << endl;
      i++;
      j--;
    }
  }
}

// **************************************************************************************
// Given the root node of a binary search tree, return the sum of values of all
// nodes with value between L and R (inclusive).

// The binary search tree is guaranteed to have unique values.

// Example 1:

// Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
// Output: 32

int rangeSumBST(BinaryTreeNode<int> *root, int L, int R) {
  if (root == NULL) return 0;
  int sum = 0;
  if (root->data >= L && root->data <= R) {
    sum += root->data;
  }
  if (L < root->data) {
    sum += rangeSumBST(root->left, L, R);
  }
  if (R > root->data) {
    sum += rangeSumBST(root->right, L, R);
  }
  return sum;
}
// **************************************************************************************

// **************************************************************************************
// Given a binary search tree (BST), find the lowest common ancestor (LCA) of
// two given nodes in the BST.

// According to the definition of LCA on Wikipedia: “The lowest common ancestor
// is defined between two nodes p and q as the lowest node in T that has both p
// and q as descendants (where we allow a node to be a descendant of itself).”

// Given binary search tree:  root = [6,2,8,0,4,7,9,null,null,3,5]
// Example 1:

// Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
// Output: 6
// Explanation: The LCA of nodes 2 and 8 is 6.

int lcaInBST(BinaryTreeNode<int> *root, int val1, int val2) {
  if (root == NULL) return -1;
  if (root->data == val1 || root->data == val2) {
    return root->data;
  }
  int left = -1, right = -1;
  if (val1 < root->data && val2 < root->data) {
    left = lcaInBST(root->left, val1, val2);
  } else if (val1 > root->data && val2 > root->data) {
    right = lcaInBST(root->right, val1, val2);
  } else {
    left = lcaInBST(root->left, val1, val2);
    right = lcaInBST(root->right, val1, val2);
  }
  if (left != -1 && right != -1) {
    return root->data;
  } else if (left != -1 && right == -1) {
    return left;
  } else if (left == -1 && right != -1) {
    return right;
  } else {
    return -1;
  }
}
// **************************************************************************************

// **************************************************************************************
// Given preorder traversal of a binary search tree, construct the BST.

// For example, if the given traversal is {10, 5, 1, 7, 40, 50}, then the output
// should be root of following tree.
//      10
//    /   \
//   5     40
//  /  \      \
// 1    7      50

BinaryTreeNode<int> *constructFromPreorder(int *preorder, int size) {
  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(preorder[0]);
  stack<BinaryTreeNode<int> *> nodes;
  nodes.push(root);
  for (int i = 1; i < size; i++) {
    BinaryTreeNode<int> *temp = NULL;
    while (!nodes.empty() && preorder[i] > nodes.top()->data) {
      temp = nodes.top();
      nodes.pop();
    }
    BinaryTreeNode<int> *node = new BinaryTreeNode<int>(preorder[i]);
    if (temp) {
      temp->right = node;
    } else {
      nodes.top()->left = node;
    }
    nodes.push(node);
  }
  return root;
}
// **************************************************************************************

// **************************************************************************************
// Given a Binary Tree, convert it to a Binary Search Tree. The conversion must
// be done in such a way that keeps the original structure of Binary Tree.

// Example:
// Input:
//           10
//          /  \
//         2    7
//        / \
//       8   4
// Output:
//           8
//          /  \
//         4    10
//        / \
//       2   7

void buildBST(BinaryTreeNode<int> *root, vector<int> &inorder, int &start) {
  if (!root) return;
  buildBST(root->left, inorder, start);
  root->data = inorder[start];
  start++;
  buildBST(root->right, inorder, start);
}
void convertBinaryToBSTSameStructure(BinaryTreeNode<int> *root) {
  if (!root) return;
  vector<int> inorder;
  getInorder(root, inorder);
  sort(inorder.begin(), inorder.end());
  int start = 0;
  buildBST(root, inorder, start);
}
// **************************************************************************************

// **************************************************************************************
// Given a binary tree and a sum, determine if the tree has a root-to-leaf
// path such that adding up all the values along the path equals the given sum.
// Example:

// Given the below binary tree and sum = 22,

//       5
//      / \
//     4   8
//    /   / \
//   11  13  4
//  /  \      \
// 7    2      1
// return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.

bool hasPathSum(BinaryTreeNode<int> *root, int sum) {
  if (!root) return false;
  if (isLeaf(root) && sum - root->data == 0) return true;
  return hasPathSum(root->left, sum - root->data) ||
         hasPathSum(root->right, sum - root->data);
}
// **************************************************************************************

// **************************************************************************************
// Given a Binary Search Tree (BST), convert it to a Greater Tree such that
// every key of the original BST is changed to the original key plus sum of all
// keys greater than the original key in BST.

// Example:

// Input: The root of a Binary Search Tree like this:
//               5
//             /   \
//            2     13

// Output: The root of a Greater Tree like this:
//              18
//             /   \
//           20     13

BinaryTreeNode<int> *convertBSTGreater(BinaryTreeNode<int> *root, int &sum) {
  if (!root) return nullptr;
  root->right = convertBSTGreater(root->right, sum);
  sum += root->data;
  root->data = sum;
  root->left = convertBSTGreater(root->left, sum);
  return root;
}
BinaryTreeNode<int> *convertBSTGreater(BinaryTreeNode<int> *root) {
  if (!root) return nullptr;
  int sum = 0;
  return convertBSTGreater(root, sum);
}
// **************************************************************************************

// **************************************************************************************
//  Given a binary search tree and the lowest and highest boundaries as L and R,
//  trim the tree so that all its elements lies in [L, R] (R >= L). You might
//  need to change the root of the tree, so the result should return the new
//  root of the trimmed binary search tree.
// Example:

// Input:
//     1
//    / \
//   0   2

//   L = 1
//   R = 2

// Output:
//     1
//       \
//        2

BinaryTreeNode<int> *trimBST(BinaryTreeNode<int> *root, int L, int R) {
  if (!root) return nullptr;
  BinaryTreeNode<int> *left = trimBST(root->left, L, R);
  BinaryTreeNode<int> *right = trimBST(root->right, L, R);
  BinaryTreeNode<int> *newRoot;
  if (root->data >= L && root->data <= R) {
    newRoot = root;
    newRoot->left = left;
    newRoot->right = right;
  } else {
    newRoot = left ? left : right;
  }
  return newRoot;
}
// **************************************************************************************

void reversePathFronRootToK(BinaryTreeNode<int> *root, int k,
                            queue<int> &path) {
  if (!root) return;
  path.push(root->data);
  if (k < root->data) {
    reversePathFronRootToK(root->left, k, path);
  } else if (k > root->data) {
    reversePathFronRootToK(root->right, k, path);
  }
  int data = path.front();
  root->data = data;
  path.pop();
}

void reversePathFronRootToK(BinaryTreeNode<int> *root, int k) {
  queue<int> path;
  reversePathFronRootToK(root, k, path);
}

int main() {
  BinaryTreeNode<int> *root = takeInputLevelWise();
  reversePathFronRootToK(root, 7);
  printLevelWise(root);
  delete root;
  return 0;
}

// BST