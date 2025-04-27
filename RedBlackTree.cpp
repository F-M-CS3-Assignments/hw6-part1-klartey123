#include <iostream>
# include "RedBlackTree.h"
#include <cassert>
#include <random>


using namespace std;

RedBlackTree::RedBlackTree() {
    root = nullptr;
    numItems = 0;
}

RedBlackTree::RedBlackTree(int newData) {
    root = nullptr;
    numItems = 0;
    Insert(newData);  
    
}
// Travasel
// Infix travasel.
string RedBlackTree:: ToInfixString(const RBTNode *n){
    if (n == nullptr || n->IsNullNode ){
        return "";
    }

    // left subtree travsel
    string leftSub = ToInfixString(n->left);
    // get the apporiate colour for the current node. 
    string currentSub = " " + GetColorString(n) + to_string(n-> data)+ " ";
    // right travesal. 
    string rightSub = ToInfixString(n->right);

    return leftSub + currentSub + rightSub;
}
// prefix 
string RedBlackTree:: ToPrefixString(const RBTNode *n){
    if (n == nullptr || n->IsNullNode ){
        return "";
    }

    // root node first. 
    string root = " " + GetColorString(n) + to_string(n->data) + " ";
    // now travesal to the left
    string left = ToPrefixString(n->left);
    // right travesal. 
    string right = ToPrefixString(n->right);

    return root + left + right;
}
// post fix.

string RedBlackTree:: ToPostfixString(const RBTNode *n){
    if (n == nullptr || n->IsNullNode ){
        return "";
    }
    string left = ToPostfixString(n->left);
    string right = ToPostfixString(n->right);
    string root = " " + GetColorString(n) + to_string(n->data) + " ";

    return left +  right + root;

}

// what colour should the node contain. 
string RedBlackTree::GetColorString(const RBTNode *n) {
    if (n == nullptr || n->IsNullNode){
        return "";
    }
    if (n->color == COLOR_RED) {
        return "R";
    } 
    else {
        return "B";
    }
}

// Inserting a new node.
void RedBlackTree:: Insert(int newData){
    // rule 1; when there is no node and the new node is the first one
    if (root == nullptr){
        // make a new node. 
        RBTNode* newNode = new RBTNode;
        newNode ->data = newData;
        // set it to black since it would be the root node.
        newNode ->color = COLOR_BLACK;
        // there is no left, right and parent node yet. well there is no parent node for the root. 
        newNode -> left = nullptr;
        newNode -> right = nullptr;
        newNode -> parent= nullptr;
        // this null would not be node. 
        newNode -> IsNullNode =false;
        // now my root node;
        root = newNode;
        // increase the number of nodes in the tree
        numItems ++;
        InsertFixUp(newNode);
        return;
    }
    RBTNode* current = root;
    while(current != nullptr){
        if (newData < current -> data){
            if (current->left == nullptr){

            // same structure as the root node.
            // new node
            RBTNode* newNode = new RBTNode;
            newNode ->data = newData;
            // colour it red,it is a laf new node. 
            newNode ->color = COLOR_RED;
            // left node and right node are null but the parent would be the current. 
            newNode -> left = nullptr;
            newNode -> right = nullptr;
            newNode -> parent = current;
            // not empty. 
            newNode -> IsNullNode =false;
            current->left = newNode;
            numItems++;
            InsertFixUp(newNode);
            return;

            }
            else{
                current = current->left;
            }
        }
        else if (newData > current -> data){
            if (current -> right ==nullptr){

                RBTNode* newNode = new RBTNode;
                newNode -> data = newData;
                newNode -> right = COLOR_RED;
                newNode -> left = nullptr;
                newNode -> right = nullptr;
                newNode -> parent = current;
                newNode -> IsNullNode =false;
                current -> right = newNode;
                numItems++;
                InsertFixUp(newNode);
                return;
            }
            else{
                current = current -> right;
            }
        }// what if there is a duplicate value that is implemented. 
        else {
            throw std::invalid_argument("Duplicate value insertion is not allowed.");
        }
    }
}
// Rotation. 
void RedBlackTree::InsertFixUp(RBTNode *node) {
    // first check if it is the root node or not. And then is the parent red. 
    while(node != root && node -> parent-> color == COLOR_RED){
        // Okay now is this parent left or right
        if (IsLeftChild(node->parent)){
            // if left lets check the node that would be the uncle or aunt that would be the right node. 
            RBTNode* uncle = node->parent->parent->right;
            // if the uncle is red then move to the next step of recolouring
            if (uncle != nullptr && uncle->color == COLOR_RED){
                // parent and uncle is black then the grdnparent would be red.
                node -> parent-> color = COLOR_BLACK;
                uncle-> color= COLOR_BLACK;
                // grandmama is red. 
                node -> parent->parent-> color = COLOR_RED;
                // what if our tree is really big, go in deeper and make sure everyhting is fixed
                node = node->parent->parent;
            }
            else{
                // 
                if (IsRightChild(node)){
                    // rotate case 2. 
                    node =node -> parent;
                    LeftRotate(node);
                }
                node->parent->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                RightRotate(node->parent->parent);

            }
            
        } // What if the parent is the right child instead of left. Mirror implementation. 
        else{
            RBTNode* uncle = node->parent->parent->left;
            if(uncle != nullptr && uncle->color == COLOR_RED){
                node -> parent-> color = COLOR_BLACK;
                uncle -> color = COLOR_BLACK;
                node -> parent->parent-> color = COLOR_RED;
                node = node->parent ->parent;
            }
            else{
                if (IsLeftChild(node)){
                    node =node -> parent;
                    RightRotate(node);
                }
                node ->parent ->color = COLOR_BLACK;
                node -> parent -> parent->color = COLOR_RED;
                LeftRotate(node -> parent -> parent);
            }

        }
    }
    // root node is always black. 
    root->color = COLOR_BLACK;
}

// Left rotation; 
void RedBlackTree :: LeftRotate(RBTNode *node){
    // the right_node is the node on the right
    RBTNode* right_node = node -> right;
    // After rotation, the pointer points to the left child. 
    node -> right = right_node -> left;
    if (right_node->left != nullptr) {
        // deeper rotation algorithm. 
        right_node->left->parent = node;
    }
    
    right_node->parent = node->parent;

    if (node->parent == nullptr) {
        root = right_node;
    } else if (IsLeftChild(node)) {
        node->parent->left = right_node;
    } else {
        node->parent->right = right_node;
    }

    right_node->left = node;                     
    node->parent = right_node;
}

// right roation
void RedBlackTree :: RightRotate(RBTNode *node){
    // the left_node is the node on the left
    RBTNode* left_node = node -> left;
    // After rotation, the pointer points to the left child. 
    node -> left = left_node -> right;
    if (left_node->right != nullptr) {
        // deeper rotation algorithm. 
        left_node->right->parent = node;
    }
    left_node->parent = node->parent;          

    if (node->parent == nullptr) {
        root = left_node;
    } 
    else if (IsRightChild(node)) {
        node->parent->right = left_node;
    } else {
        node->parent->left = left_node;
    }

    left_node->right = node;                     
    node->parent = left_node;
}

// what is left child
bool RedBlackTree::IsLeftChild(RBTNode* node) const {
    return node->parent != nullptr && node->parent->left == node;
}

bool RedBlackTree::IsRightChild(RBTNode* node) const {
    return node->parent != nullptr && node->parent->right == node;
}

// Searching going in BST style. 
bool RedBlackTree:: Contains(int data) const{
    RBTNode* current = root;
    while(current != nullptr){
        if (current -> data == data){
            return true;
        }
        // left
        else if (data < current->data) {
            current = current->left;
        }
        //right
        else {
            current = current->right;
        }
    
    }
    return false;
}
// helper function for the copyconstructor

RBTNode* RedBlackTree::CopyTree(const RBTNode* locate, RBTNode* parent) {
    if (locate == nullptr || locate->IsNullNode) {
        return nullptr;
    }
    // create a new node then copy the data 
    RBTNode* newNode = new RBTNode;
    newNode->data = locate->data;
    newNode->color = locate->color;
    // just so that there is consientency. 
    newNode->IsNullNode = locate->IsNullNode;
    newNode->parent = parent;
    newNode->left = CopyTree(locate->left, newNode);
    newNode->right = CopyTree(locate->right, newNode);

    return newNode;

}
// copy everything 
RedBlackTree:: RedBlackTree(const RedBlackTree &rbt){
    root = CopyTree(rbt.root, nullptr);
    numItems = rbt.numItems;
}

// the min implementation
int RedBlackTree::GetMin() const {
    RBTNode* current = root;
    if (current == nullptr) {
        throw std::runtime_error("Tree is empty!");
    }
    while (current->left != nullptr && !current->left->IsNullNode) {
        current = current->left;
    }
    return current->data;
}
// max implementation
int RedBlackTree::GetMax() const {
    RBTNode* current = root;
    if (current == nullptr) {
        throw std::runtime_error("Tree is empty!");
    }
    while (current->right != nullptr && !current->right->IsNullNode) {
        current = current->right;
    }
    return current->data;
}
