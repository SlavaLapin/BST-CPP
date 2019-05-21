#include <iostream>
#include "BST.h"

using namespace std;

// !!! TODO NULL-protect rotation functions!!!!
// TODO Double-rotations?
// TODO Determine rotation criteria?
// TODO test trees of different types
// TODO findmax(), findmin()
// TODO splitOn()
// TODO print study, walk through with highlights

int splashMainMenu()
{
    int inp = -1;
    cout<<endl;
    cout<<"-- This is TreeInterface --"<<endl<< "Select an option:"<<endl;
    cout<<"1. Add value to the tree."<<endl;
    cout<<"2. Remove a value from the tree."<<endl;
    cout<<"3. Check if a value is already in the tree."<<endl;
    cout<<"4. Walk the tree."<<endl;
    cout<<"5. Generate an SVG file."<<endl;
    cout<<"------Type 1, 2, 3 or 4 and press Enter------"<<endl;
    cin >> inp;
    cout<<endl;
    return inp;
}

template <typename T>
void menu(Node<T> * root)
{
    T val;
    short userMenuSelection = 0;
    while(userMenuSelection != -1)
    {
        userMenuSelection = splashMainMenu();
        switch(userMenuSelection)
        {
            case 1:
                cout<<"What value do you want to add?"<<endl;
                cin>>val;
                root->addNode(val);
                cout<<"Done!";
                break;
            case 2:
                cout<<"What value do you want to delete?"<<endl;
                cin>>val;
                root->rm(val);
                cout<<"Done!";
                break;
            case 3:
                cout<<"What value are you trying to find?"<<endl;
                cin>>val;
                cout<<root->doesNodeExist(val)<<endl;
                cout<<"Done!";
                break;
            case 4:
                cout<<"What way?"<<endl;
                char c;
                cin>>c;
                root->print(c);
                cout<<"Done!";
                break;
            case 5:
                root->drawTree();
                break;
            default:
                cout<<endl;
        }
    }
    cout<<"FIN.";
}

void test_1(Node<int> * root)
{
    root->addNode(2);
    root->addNode(5);
    root->addNode(4);
    root->addNode(1);
    root->addNode(6);
    root->addNode(10);
    root->addNode(8);
    root->addNode(9);
    root->addNode(7);
    root->addNode(12);
    root->addNode(14);
    root->addNode(3);
    root->addNode(100);
    root->addNode(90);
    root->addNode(88);
    root->addNode(82);
    root->addNode(64);
    root->addNode(50);
    root->addNode(102);
    root->addNode(56);
    root->drawTree();
}

int main() {
    auto * root = new Node<int>;

    //test_1(root);
    menu(root);

    delete root;
    return 0;
}