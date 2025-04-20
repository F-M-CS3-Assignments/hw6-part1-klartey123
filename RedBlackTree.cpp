#include <iostream>
# include "RedBlackTree.h"
#include <cassert>
#include <random>


using namespace std;


RedBlackTree::RedBlackTree() {
    root = nullptr;
    numItems = 0;
}

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
        return;
    }
    RBTNode* current = root;
    while(current != nullptr){
        if (newData< current -> data){
            if (current->left == nullptr){
                left;
            }
            else{
                current = current->left;
            }
        }
        
    }



}

