//
// Created by slava on 06.06.19.
//

#include "tests.h"
#include "BST.h"
#include <string>
#include "ExampleStruct.h"

void testString() {
    auto * root = new Node<std::string>;
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
    root->drawTree("TestResultString");
    delete root;
}

void testBalanceManyElements(int elements) {
    auto * root = new Node<int>;
    for(int i = 0; i < elements; ++i)
        root->add(i);
    root->drawTree("TestResultBalancing");
    delete root;
}

void testDouble() {
    auto * root = new Node<double>;
    root->add(3.14);
    root->add(3.3334);
    root->add(9.8);
    root->add(15.0);
    root->add(0.1);
    root->add(8.5);
    root->add(4.76);
    root->drawTree("TestResultDouble");
    delete root;
}

void testCustomStruct()
{
    auto * root = new Node<ExampleStructStudent>;
    root->add(ExampleStructStudent("Alice", 90.0));
    root->add(ExampleStructStudent("Bob", 74.6));
    root->add(ExampleStructStudent("Chris", 61.0));
    root->add(ExampleStructStudent("Bjarne", 34.4));
    root->add(ExampleStructStudent("Dennis", 19.70));
    root->drawTree("TestResultCustomStruct");
    delete root;
}