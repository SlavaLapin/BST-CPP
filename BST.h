//
// Created by slava on 24.04.19.
//
// todo balance (AVL Tree)
// todo Menus can become structs arr of Opt{label, ControlModule(submenu obj)}, then menus are composed of a list of them, menu starts a new menu
// ControlModule => Menu class, ControlModule => Tree functor class, Menus call the chosen functor;
// TreeFunctors execute simple commands like add(Tree* root, value)
// TreeFunctors need to be template functions to accept different types

#ifndef WORKBENCH_BST_H
#define WORKBENCH_BST_H

#include <vector>
#include <string>
#include <iostream>
#include "NodeData.h"
#include "TreeSVG.h"

using namespace std;

template <class T>
class Node
{
    bool empty;
    T value_;
    int weightLeft;
    int weightRight;
    Node* parent;

    void _parentWeightDecrease()
    {
        if (this->parent == NULL) return; // reached root

        if (this->parent->left == this) this->parent->weightLeft--;
        else this->parent->weightRight--;

        this->parent->_parentWeightDecrease();
    }

public:

    Node* left;
    Node* right;

    ~Node()
    {
        delete this->left;
        delete this->right;
    }

    explicit Node(const T& value, Node * parent) : empty(false), value_(value), weightLeft(0), weightRight(0), parent(parent), left(NULL), right(NULL) {} //new node

    Node() {empty = true; left = NULL; right = NULL; weightLeft = 0; weightRight = 0; parent = NULL;} // root creation

    Node(const Node& original)
    {
        this->value_ = original.value_;
        this->left = original.left;
        this->right = original.right;

        this->parent = original.parent;
        this->weightLeft = original.weightLeft;
        this->weightRight = original.weightRight;
    }

    Node& operator=(const Node& original)
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
            this->weightRight++;
            if (right == NULL)
            {
                right = new Node(value, this);
                return this; //this node has just gave birth to a child
            }
            else return right->addNode(value);
        }
        else
        {
            this->weightLeft++;
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
        if (migrant->value_ > this->value_) // to be hanged on the right
        {
            this->weightRight+=migrant->weightLeft;
            this->weightRight+=migrant->weightRight+1;
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
            this->weightLeft+=migrant->weightLeft;
            this->weightLeft+=migrant->weightRight+1;
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

        if (toDelete->parent == NULL) // sudo rm / (Deleting  a root with children)
        {
            if ((toDelete->weightRight == 0) && (toDelete->weightLeft == 0)) // Deleting a lonely root
            {
                this->value_ = 0;
                this->empty = true;
                return;
            }

            Node * rl = toDelete->left;
            Node * rr = toDelete->right;
            if (toDelete->weightRight > toDelete->weightLeft)
            {
                *toDelete = *(rr);
                toDelete->hangNodes(rl);
                rr->right = NULL;
                rr->left = NULL;
                delete rr;
            }else
            {
                *toDelete = *(rl);
                toDelete->hangNodes(rr);
                rl->right = NULL;
                rl->left = NULL;
                delete rl;
            }
            toDelete->parent = NULL;
            toDelete->balance();
            return;
        }

        // not root
        bool leftChild = false;
        if (toDelete->parent->left == toDelete) leftChild = true;

        toDelete->_parentWeightDecrease();

        Node* balancingPoint = NULL;

        if ((toDelete->weightRight == 0) && (toDelete->weightLeft == 0)) // leaf
        {
            if (leftChild)
            {
                toDelete->parent->left = NULL;
            }
            else
            {
                toDelete->parent->right = NULL;
            }
            delete toDelete;
            return;
        }

        // has children
        if (toDelete->weightRight > toDelete->weightLeft) // right-heavy
        {
            toDelete->right->parent = toDelete->parent;
            if (leftChild)
            {
                toDelete->parent->left = toDelete->right;
                balancingPoint = toDelete->parent->left->hangNodes(toDelete->left);
            } else
            {
                toDelete->parent->right = toDelete->right;
                balancingPoint = toDelete->parent->right->hangNodes(toDelete->left);
            }
        }else                                             // left-heavy or BALANCED (default)
        {
            toDelete->left->parent = toDelete->parent;
            if (leftChild)
            {
                toDelete->parent->left = toDelete->left;
                balancingPoint = toDelete->parent->left->hangNodes(toDelete->right);
            } else
            {
                toDelete->parent->right = toDelete->left;
                balancingPoint = toDelete->parent->right->hangNodes(toDelete->right);
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
        Node * n = this->findNode(value);
        if (n == NULL)
        {
            cout<<"This value is not contained in the tree!"<<endl;
            return false;
        }
        else
        {
            cout<<"Value: "<<n->value_<<", wl: "<<n->weightLeft<<", wr: "<<n->weightRight<<", parent: ";
            if (n->parent != NULL) cout << n->parent->value_;
            else cout << "None";
            cout << ", empty:"<<n->empty<<endl;
            return true;
        }
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
        int nothing;
        cout<<"Just pretending for now, value: "<<this->value_<<", wl: "<<this->weightLeft<<", wr: "<<this->weightRight<<endl;
        cin>>nothing;
        if (this->parent != NULL) this->parent->balance();
    }

    void leftTurn(){}

    void rightTurn(){}

    TreeData<T> * survey() const
    {
        int size = weightLeft + weightRight + 1;
        NodeData<T> * allNodes = NULL;
        try {
            allNodes = new NodeData<T> [size];
        }
        catch(std::bad_alloc &ba)
        {
            std::cout<<ba.what();
            return NULL;
        }
        int count = -1;
        int * counter = &count;
        this->submitData(allNodes, counter, 0, -1, false);

        TreeData<T> * data = NULL;
        try
        {
            data = new TreeData<T>(allNodes, size);
        }
        catch(std::bad_alloc &ba)
        {
            cout<<"new TreeData failed"<<std::endl;
        }
        return data;
    }

    void submitData(NodeData<T> * allNodes, int * const counter, const int myLevel, const int myParent, const bool amILeft) const
    {
        ++(*counter);
        allNodes[*counter] = NodeData<T>(value_, *counter, myParent, amILeft, myLevel);
        int myId = *counter;

        if (left != NULL)
        {
            left->submitData(allNodes, counter, myLevel+1, myId, true);
        }
        if(right != NULL)
        {
            right->submitData(allNodes, counter, myLevel+1, myId, false);
        }
    }

    void drawTreeDEBUG(TreeData<T> const * data) const
    {
        if (data == NULL) { std::cout<<"Empty TreeData pointer!"<<std::endl; return;}
        cout<<"_*+*+*+*+*+*_TREE_*+*+*+*+*+*_"<<endl;
        cout<<"Total: "<<data->nodeCount<<endl;
        cout<<"Levels: "<<data->levels<<" (Largest row consists of "<<data->mostNodesOnLevel<<" nodes)"<<endl;

        for (int i = 0; i < data->levels; ++i)
        {
            cout<<"  "<<data->nodesByLevel[i]<<": [ ";
            NodeData<T> * lvl_ptr = data->nodeDataArray[i];
            for(int j = 0; j < data->nodesByLevel[i]; ++j)
            {
                NodeData<T> elem = lvl_ptr[j];
                cout<<"(ID: "<<elem.id;
                cout<<" V: "<<elem.value;
                cout<<" PID: "<<elem.parentId;
                cout<<" LEV: "<<elem.level;
                cout<<" R: "<<!(elem.leftChild)<< ") ";
            }
            cout<<" ]"<<endl;
        }

        cout<<"_*+*+*+*+_END_OF_TREE_+*+*+*+*_"<<endl;
    }

    void drawTree() const
    {
        std::cout<<"Drawing a tree method"<<std::endl;
        TreeData<T> * data = this->survey();
        if(data == NULL) return;

        drawTreeDEBUG(data);
        drawTreeSVG(data);
        std::cout<<"Drawing done. Deleting data"<<std::endl;

        delete data;
        std::cout<<"drawTree method done its job"<<std::endl;
    }
};

#endif //WORKBENCH_BST_H
