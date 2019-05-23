#include <iostream>
#include "BST.h"

#include <string>

using namespace std;

// TODO findmax(), findmin()
// TODO splitOn()
// TODO fix bugs (some deletions cause crashes)

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
    root->drawTree();
    int i;
    cin >> i;
    root->add(9);
    root->drawTree();
    // it fails at the above point. No rotations before it. After rotating total is 12, not 8 as supposed to be.
    root->add(7);
    root->drawTree();
    root->add(12);
    root->add(14);
    root->add(3);
    root->drawTree();
    root->add(100);
    root->add(90);
    root->add(88);
    root->drawTree();
    root->add(82);
    root->add(64);
    root->add(50);
    root->drawTree();
    root->add(102);
    root->add(56);
    root->print('l');
    root->drawTree();
}

void test_2(Node<int> * root)
{
    for(int i = 0; i < 100; ++i)
        root->add(i);
    root->drawTree();
}

void test_3(Node<string> * root)
{
    root->add("Somebody");
    root->add("once");
    root->add("told");
    root->add("me");
    root->add("the");
    root->add("world");
    root->add("is");
    root->add("gonna");
    root->add("roll");
    root->add("me");
    root->drawTree();
}

int main() {
    auto * r = new Node<int>;

    //test_1(r);
    test_2(r);
    //test_3(r);
    menu(r);

    delete r;
    return 0;
}