//
// Created by Slava on 18.05.2019.
//

#ifndef WORKBENCH_TREESVG_H
#define WORKBENCH_TREESVG_H

#include <string>
#include <sstream>
#include "gfx.hpp"
#include "NodeData.h"

using namespace svg;


const int MINIMAL_GAP = 100;
const int VERTICAL_GAP = 100;
const int BLOCK_HEIGHT = 100;
const int _BLOCK_WIDTH = 200;
const int _PADDING_X = 15;
const int _PADDING_Y = -57;
const int _FONT_SIZE = 26;
const int LINE_WIDTH = 5;

template<class type>
std::string to_string(const type &value)
{
    std::ostringstream streamOut;
    streamOut << value;
    return streamOut.str();
}

template <class T>
struct NodeSVG
{
    int id;
    Point origin;
    std::string valueStr;
    int parentId;
    bool leftChild;

    NodeSVG(Point origin, NodeData<T> const& node): id(node.id), origin(origin), valueStr(to_string(node.value)), parentId(node.parentId), leftChild(node.leftChild) {}
};

template<class T>
NodeSVG <T> **createRow(TreeData<T> *data, int rowLevel, int width) {
    std::cout<<"Creating visual data for row: "<<rowLevel<<std::endl;
    int rowNodes = data->nodesByLevel[rowLevel];
    NodeSVG<T> ** row;
    try{
        row = new NodeSVG<T> * [data->nodesByLevel[rowLevel]];
    }
    catch(std::bad_alloc &ba)
    {
        std::cout<<ba.what()<<std::endl;
    }
    int gapHorForRow = (width - _BLOCK_WIDTH * rowNodes) / (rowNodes + 1);

    for (int i =  0; i < data->nodesByLevel[data->levels-1]; i++)
    {
        Point bottomLeftCorner = Point( (gapHorForRow*(i+1)+_BLOCK_WIDTH*i), (100 + VERTICAL_GAP * (data->levels - rowLevel) + BLOCK_HEIGHT * (data->levels - rowLevel - 1)) );
        row[i] = new NodeSVG<T>(bottomLeftCorner, data->nodeDataArray[rowLevel][i]);
    }
    std::cout<<"Created succesfully"<<std::endl;
    return row;
}

template<class T>
void deleteRow(NodeSVG<T> **row, int len) {
    for (int j = 0; j < len; j++)
    {
        delete row[j];
    }
    delete [] row;
}

template<class T>
Point getParentOrigin(NodeSVG<T> *child, NodeSVG<T> **above, int aboveLen) {
    for (int i = 0; i < aboveLen; ++i)
    {
        if(child->parentId == above[i]->id)
        {
            return above[i]->origin;
        }
    }
    std::cout<<"failed finding parent: "<<child->parentId;
    return Point(0, 0);
}

template<class T>
void DrawConnections(Document &doc, NodeSVG<T> **row, NodeSVG<T> **above, int rowLen, int aboveLen) {
    for (int i = 0; i < rowLen; ++i)
    {
        Point a = row[i]->origin;
        a.x += _BLOCK_WIDTH / 2;
        a.y += - (BLOCK_HEIGHT / 2);
        Point b = getParentOrigin(row[i], above, aboveLen);
        b.x += _BLOCK_WIDTH / 2;
        b.y += -(BLOCK_HEIGHT / 2);

        Polygon line(Stroke(LINE_WIDTH, (row[i]->leftChild ? Color::Lime : Color::Red)));
        line << a << b;
        doc << line;
    }
}

template<class T>
void DrawRow(Document &doc, NodeSVG<T> **row, int rowLen) {
    for (int i = 0; i < rowLen; ++i)
    {
        doc << Rectangle(row[i]->origin, _BLOCK_WIDTH, BLOCK_HEIGHT, Color::Silver);
        Text str = Text(row[i]->origin, row[i]->valueStr, Color::Fuchsia, Font(_FONT_SIZE, "Verdana"));
        str.offset(Point(_PADDING_X, _PADDING_Y));
        doc << str;
    }
    //maybe a border
}

template<typename T>
static void drawTreeSVG(TreeData<T> * data) {
    if (data == NULL) { std::cout<<"Empty TreeData pointer!"<<std::endl; return;}
    if (data->levels < 1) {std::cout<<"An empty tree cannot be drawn"<<std::endl; return;}
    // set canvas size
    int height = ((data->levels + 1) * VERTICAL_GAP) + (data->levels * BLOCK_HEIGHT);
    int width = ((data->mostNodesOnLevel + 1) * MINIMAL_GAP) + (data->mostNodesOnLevel * _BLOCK_WIDTH);
    Dimensions dimensions(width, height);
    Document doc("BST.svg", Layout(dimensions));
    std::cout<<"Document has been created"<<std::endl;

    Polygon border(Stroke(5, Color::Black));
    border << Point(0, 0) << Point (0, height) << Point(width, height) << Point(width, 0) << Point (0,0);
    doc << border;
    std::cout<<"border drawn"<<std::endl;

    // create a row of ** data
    NodeSVG<T> ** above = NULL;
    int rowLevel = data->levels-1; // last level
    NodeSVG<T> ** row = createRow(data, rowLevel, width); // enough pointers to pointers for all nodes of last row

    for (int i = rowLevel; i >= 0; --i)
    {
        if ((i - 1) >= 0)
        {
            above = createRow(data, i-1, width);
            std::cout<<"Drawing connections for rows "<<i<<" and "<<i-1<<std::endl;
            DrawConnections(doc, row, above, data->nodesByLevel[i], data->nodesByLevel[i-1]);
        }
        std::cout<<"Drawing row "<<i<<std::endl;
        DrawRow(doc, row, data->nodesByLevel[i]);

        deleteRow(row, data->nodesByLevel[i]);
        row = above;
    }
    //deleteRow(row, 1); // top row always consists of 1 node

    std::cout<<"saving..."<<std::endl;
    doc.save();
}

#endif //WORKBENCH_TREESVG_H
