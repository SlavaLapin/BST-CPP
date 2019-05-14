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
    int weightLeft;
    int weightRight;
    Node* parent;

public:

    Node* left;
    Node* right;

    explicit Node(const T& value, Node * parent) : empty(false), value_(value), weightLeft(0), weightRight(0), parent(parent), left(NULL), right(NULL) {} //new node

    Node() {empty = true; left = NULL; right = NULL; parent = NULL;} // root creation

    Node(const Node& original)
    {
        this->value_ = original.value_;
        this->left = original.left;
        this->right = original.right;

        this->parent = original.parent;
        this->weightLeft = original.weightLeft;
        this->weightRight = original.weightRight;
    }

    Node operator=(const Node& original)
    {
        this->value_ = original.value_;
        this->left = original.left;
        this->right = original.right;
        this->weightLeft = original.weightLeft;
        this->weightRight = original.weightRight;
        this->parent = original.parent;
        this->empty = original.empty;
        return *this;
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
                // ++weightRight;
                return this; //this node has just gave birth to a child
            }
            else return right->addNode(value);
        }
        else
        {
            if(left==NULL)
            {
                left = new Node(value, this);
                // ++weightLeft;
                return this; //this node has just gave birth to a child
            }
            else return left->addNode(value);
        }
    }

    Node* hangNodes(Node * migrant)
    {
        if (migrant->value_ > this->value_)
        {
            this->weightRight+=migrant->weightLeft;
            this->weightRight+=migrant->weightRight;
            if(this->right == NULL)
            {
                this->right = migrant;
                migrant->parent = this;
                return this;
            }else
            {
                return this->right->hangNodes(migrant);
            }
        }else
        {
            this->weightLeft+=weightLeft;
            this->weightLeft+=weightRight;
            if(this->left == NULL)
            {
                this->left = migrant;
                migrant->parent = this;
                return this;
            }else
            {
                return this->left->hangNodes(migrant);
            }
        }
    }
    
    void rm(const T& value)
    {
        Node *toDelete = this->findNode(value);
        if(toDelete == NULL) return;

        if (toDelete->parent == NULL) // sudo rm / (Deleting root)
        {
            Node * tmp = toDelete;
            if (toDelete->weightRight > toDelete->weightLeft)
            {
                *toDelete = *(tmp->right);
                toDelete->hangNodes(tmp->left);
            }else
            {
                *toDelete = *(tmp->left);
                toDelete->hangNodes(tmp->right);
            }
            tmp->left = NULL;
            tmp->right = NULL;
            delete tmp;
            toDelete->balance();
            return;
        }

        bool leftChild = false;
        if (toDelete->parent->left == toDelete) leftChild = true;

        if (leftChild) toDelete->parent->weightLeft--;
        else toDelete->parent->weightRight--;

        Node* balancingPoint = NULL;
        if (toDelete->weightRight > toDelete->weightLeft)
        {
            if (leftChild)
            {
                toDelete->parent->left = toDelete->right;
                balancingPoint = toDelete->parent->left->hangNodes(toDelete->left);
            } else
            {
                toDelete->parent->right = toDelete->right;
                balancingPoint = toDelete->parent->right->hangNodes(toDelete->left);
            }
        }else
        {
            if (leftChild)
            {
                toDelete->parent->left = toDelete->left;
                balancingPoint = toDelete->parent->left->hangNodes(toDelete->right);
            } else
            {
                toDelete->parent->right = toDelete->left;
                balancingPoint = toDelete->parent->right->hangNodes(toDelete->left);
            }
        }

        toDelete->left = NULL;
        toDelete->right = NULL;
        delete toDelete;
        if (balancingPoint != NULL) balancingPoint->balance();
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

    void balance()
    {
        cout<<"Just pretending for now, value: "<<this->value_<<endl;
        if (this->parent != NULL) this->parent->balance();
    }
};

#endif //WORKBENCH_BST_H
