#include <iostream>
#include "BST.h"

#include <string>
#include <time.h>
#include "tests.h"

using namespace std;

// TODO fix bugs (some deletions cause crashes)

short splashMainMenu()
{
    short inp = -1;
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
    int t = time(NULL);
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
                root->drawTree(std::to_string(t));
                break;
            default:
                cout<<endl;
        }
    }
    cout<<"FIN.";
}

void runTests()
{
    //testDouble();
    //testString();
    //testBalanceManyElements(30);
    testCustomStruct();
}

int main() {

    runTests();

    auto * r = new Node<int>;
    menu(r);

    delete r;
    return 0;
}