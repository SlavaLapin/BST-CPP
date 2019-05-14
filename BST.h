//
// Created by slava on 24.04.19.
//
// todo balance (AVL Tree)
// todo weight, parent
// todo Node* rm
// todo graphix,node data
// todo Menus can become structs arr of Opt{label, ControlModule(submenu obj)}, then menus are composed of a list of them, menu starts a new menu
// ControlModule => Menu class, ControlModule => Tree functor class, Menus call the chosen functor;
// TreeFunctors execute simple commands like add(Tree* root, value)
// TreeFunctors need to be template functions to accept different types

#ifndef WORKBENCH_BST_H
#define WORKBENCH_BST_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Node
{
    bool empty;
    T value_;
    int leftWeight;
    int rightWeight;
    Node* parent;

public:

    Node* left;
    Node* right;

    explicit Node(const T& value, Node * parent) : empty(false), value_(value), leftWeight(0), rightWeight(0), parent(parent), left(NULL), right(NULL) {} //new node

    Node() {empty = true; left = NULL; right = NULL; parent = NULL;} // root creation

    Node(const Node& original)
    {
        this->value_ = original.value_;
        this->left = original.left;
        this->right = original.right;

        this->parent = original.parent;
        this->leftWeight = original.leftWeight;
        this->rightWeight = original.rightWeight;
    }

    Node* addNode(const T& value)
    {
        if(empty) {value_ = value; empty = false; return this;} // root. for now
        if (value == value_) return NULL;
        if (value > value_)
        {
            if (right == NULL)
            {
                right = new Node(value, this);
                // ++rightWeight;
                return this; //this node has just gave birth to a child
            }
            else return right->addNode(value);
        }
        else
        {
            if(left==NULL)
            {
                left = new Node(value, this);
                // ++leftWeight;
                return this; //this node has just gave birth to a child
            }
            else return left->addNode(value);
        }
    }

    void rm(const T& value)
    {
        Node *_toDelete = this->findNode(value);

        cout<<"mock-up";
    }

    Node* findNode(const T& value)
    {
        if (value == value_) return this;
        if (value > value_)
        {
            if (right != NULL) return right->findNode(value);
            else return NULL;
        }
        else
        {
            if (left != NULL) return left->findNode(value);
            else return NULL;
        }
    }

    bool doesNodeExist(const T& value)
    {
        if ((this->findNode(value)) == NULL) return false;
        else return true;
    }

    void print(const char& mode) // l - leftside, r - rightside, c - center
    {
        if(empty) return;
        switch (mode)
        {
            case 'l':
                if (left != NULL) left->print(mode);
                cout<<value_<<" ";
                if (right != NULL) right->print(mode);
                break;
            case 'r':
                if (right != NULL) right->print(mode);
                cout<<value_<<" ";
                if (left != NULL) left->print(mode);
                break;
            case 'c':
                cout<<value_<<" ";
                if (left != NULL) left->print(mode);
                if (right != NULL) right->print(mode);
                break;
            default:
                cout<<"Print mode not specified"<<endl;
        }
    }
};

#endif //WORKBENCH_BST_H
