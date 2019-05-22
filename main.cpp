#include <iostream>
#include "BST.h"

#include <string>

using namespace std;

// TODO Determine rotation criteria?
// TODO findmax(), findmin()
// TODO splitOn()
// TODO print study, walk through with highlights

int splashMainMenu()
{
    int inp = -1;
    cout<<endl;
    cout<<"-- TreeInterface --"<<endl<< "Select an option:"<<endl;
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
                root->add(val);
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
    root->add(2);
    root->add(5);
    root->add(4);
    root->add(1);
    root->add(6);
    root->add(10);
    root->add(8);
    root->add(9);
    root->add(7);
    root->add(12);
    root->add(14);
    root->add(3);
    root->add(100);
    root->add(90);
    root->add(88);
    root->add(82);
    root->add(64);
    root->add(50);
    root->add(102);
    root->add(56);
    root->drawTree();
}

int main() {
    auto * root = new Node<string>;

    menu(root);

    delete root;
    return 0;
}