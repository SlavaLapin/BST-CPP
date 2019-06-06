//
// Created by slava on 24.04.19.
//
// todo balance (weight-balanced Tree)

#ifndef WORKBENCH_BST_H
#define WORKBENCH_BST_H

#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include "NodeData.h"
#include "TreeSVG.h"


using namespace std;

const double DELTA = 1 + sqrt(2);
const double GAMMA = sqrt(2);

template <class T>
class Node
{
    bool empty;
    T value_;
    int weightLeft;
    int weightRight;
    Node* parent;
    Node* left;
    Node* right;

    Node* addNode(const T& value)
    {
        if(empty) {value_ = value; empty = false; return NULL;} // root. for now
        if (value == value_){ std::cout<<"Value already in the tree!"<<std::endl; this->_parentWeightDecrease(); return NULL; }
        if (value > value_)
        {
            this->weightRight++;
            if (right == NULL)
            {
                right = new Node(value, this);
                return this->parent; //this node has just gave birth to a child
            }
            else return right->addNode(value);
        }
        else
        {
            this->weightLeft++;
            if(left==NULL)
            {
                left = new Node(value, this);
                return this->parent; //this node has just gave birth to a child
            }
            else return left->addNode(value);
        }
    }

    void _parentWeightDecrease()
    {
        if (this->parent == NULL) return; // reached root

        if (this->parent->left == this) this->parent->weightLeft--;
        else this->parent->weightRight--;

        this->parent->_parentWeightDecrease();
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

    Node* hangNodes(Node * migrant)
    {
        if (migrant == NULL) return NULL;
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

    Node * const findNode(const T& value)
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

    void balance()
    {
        cout<<"Not pretending now, value: "<<this->value_<<", wl: "<<this->weightLeft<<", wr: "<<this->weightRight<<endl;
        if( (weightLeft + 1)  > ((weightRight + 1) * DELTA) ) //left-heavy
        {
            if ( ((this->left->weightLeft + 1) * GAMMA) < (this->left->weightRight + 1) )
                this->rotateRL();
            else
                this->rotateRight();
        } else if ( (weightRight + 1)  > ((weightLeft + 1) * DELTA) ){
        { // right-heavy
            if ( ((this->right->weightRight + 1) * GAMMA) < (this->right->weightLeft + 1) )
                this->rotateLR();
            else
                this->rotateLeft();
        }}
        if (this->parent != NULL) this->parent->balance();
    }

    TreeData<T> * survey() const
    {
        if (empty){ return nullptr;} //empty tree

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
        //cout<<"Calling all nodes. - "<<endl;
        this->submitData(allNodes, counter, 0, -1, false);
        //cout<<" All nodes responded"<<endl;

        //cout<<"got to the point of creating TreeData";
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
        //cout<<"Trying to submit data for node "<<*counter<<" value: "<<this->value_<<" on level: "<<myLevel<<" wl:"<<weightLeft<<" wr:"<<weightRight<<" - ";
        allNodes[*counter] = NodeData<T>(value_, *counter, myParent, amILeft, myLevel);
        //cout<<"done"<<endl;
        int myId = *counter;

        if (left != NULL)
        {
            left->submitData(allNodes, counter, myLevel+1, myId, true);
        }
        if(right != NULL)
        {
            right->submitData(allNodes, counter, myLevel+1, myId, false);
        }
        //cout<<" - recursion exit - I'm node: "<<myId<<endl;
    }

    void rotateLeft()
    {
        cout<<"left rot"<<endl;
        Node<T> * pivot = this->right;
        if ( pivot == NULL ) return;
        Node<T> * pivotRightChild = pivot->right;
        Node<T> * pivotLeftChild = pivot->left;
        Node<T> * oldRootLeftChild = this->left;

        // 1
        T tmp = this->value_;
        this->value_ = pivot->value_;
        pivot->value_ = tmp;

        // 2
        this->left = this->right;
        int tmp_w = this->weightLeft;
        this->weightLeft = this->weightRight;
        if (this->left != NULL) this->left->weightRight = pivot->weightLeft;

        // 3
        this->right = pivot->right;
        if (this->right != NULL) this->right->parent = this; // not NULL safe
        this->weightRight = pivot->weightRight;
        this->weightLeft -= this->weightRight;

        // 4
        pivot->right = pivot->left;
        pivot->weightRight = pivot->weightLeft;

        // 5
        pivot->left = oldRootLeftChild;
        if (pivot->left != NULL){ pivot->left->parent = pivot; this->weightRight+=tmp_w;} // not NULL safe
        pivot->weightLeft = tmp_w;

    }

    void rotateRight()
    {
        cout<<"right rot"<<endl;
        Node<T> * pivot = this->left;
        if ( pivot == NULL ) return;
        Node<T> * pivotRightChild = pivot->right;
        Node<T> * pivotLeftChild = pivot->left;
        Node<T> * oldRootRightChild = this->right;

        // 1
        T tmp = this->value_;
        this->value_ = pivot->value_;
        pivot->value_ = tmp;

        // 2
        this->right = this->left;
        int tmp_w = this->weightRight;
        this->weightRight = this->weightLeft;
        if (this->right != NULL) this->right->weightLeft = pivot->weightRight;

        // 3
        this->left = pivot->left;
        if (this->left != NULL) this->left->parent = this; // not NULL safe
        this->weightLeft = pivot->weightLeft;
        this->weightRight -= this->weightLeft;

        // 4
        pivot->left = pivot->right;
        pivot->weightLeft = pivot->weightRight;

        // 5
        pivot->right = oldRootRightChild;
        if (pivot->right != NULL){ pivot->right->parent = pivot; this->weightLeft+=tmp_w;} // not NULL safe
        pivot->weightRight = tmp_w;
    }

    void rotateLR()
    {
        //cout<<"LR rot";
        this->right->rotateRight();
        this->rotateLeft();
    }

    void rotateRL()
    {
        //cout<<"RL rot";
        this->left->rotateLeft();
        this->rotateRight();
    }

public:

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
        this->empty = original.empty;
    }

    Node& operator=(const Node& original)
    {
        std::cout<<"OPERATOR= Trying to change node "<<this->value_<<" into "<<original.value_<<" node."<<std::endl;
        this->value_ = original.value_;
        this->left = original.left;
        this->right = original.right;
        this->weightLeft = original.weightLeft;
        this->weightRight = original.weightRight;
        this->parent = original.parent;
        this->empty = original.empty;
        return *this;
    }

    void add(const T& value)
    {
        cout<<"Adding "<<value<<endl;
        Node<T> * changePoint = addNode(value);
        if (changePoint != NULL) changePoint->balance();
    }
    
    void rm(const T& value)
    {
        Node *toDelete = this->findNode(value);
        if(toDelete == NULL) return;

        if (toDelete->parent == NULL) // sudo rm / (Deleting  a root with children)
        {
            if ((toDelete->weightRight == 0) && (toDelete->weightLeft == 0)) // Deleting a lonely root
            {
                //this->value_ = 0;
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

        if ((toDelete->weightRight == NULL) && (toDelete->weightLeft == NULL)) // leaf
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

    bool doesNodeExist(const T& value)
    {
        const Node * const n = this->findNode(value);
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

    void print(const char& mode) const // l - leftside(inorder), r - rightside(postorder), c - center(preorder)
    {
        if(empty) return;
        switch (mode)
        {
            case 'l':
            case'i':
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

    void drawTree(std::string filename) const
    {
        //std::cout<<"Drawing a tree method"<<std::endl;
        TreeData<T> * data = this->survey();
        if(data == NULL){ std::cout<<"An empty tree cannot be drawn"<<std::endl; return; }

        drawTreeDEBUG(data);
        //drawTreeSVG(data, filename);
        //std::cout<<"Drawing done. Deleting data"<<std::endl;

        delete data;
        std::cout<<"SVG created successfully."<<std::endl;
    }

};

#endif //WORKBENCH_BST_H
