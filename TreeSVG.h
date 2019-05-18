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
const int VERTICAL_GAP = 50;
const int BLOCK_HEIGHT = 100;
const int _BLOCK_WIDTH = 200;
const int _PADDING_X = 20;
const int _PADDING_Y = 20;
const int _FONT_SIZE = 14;

template <class T>
struct NodeSVG
{
    int id;
    Point origin;
    std::string valueStr;
    int parentId;
    bool leftChild;

    NodeSVG(Point origin, NodeData<T> const * node): id(node->id), origin(origin), valueStr(to_string(node->value)), parentId(node->parentID), leftChild(node->leftChild) {}
};

template<class type>
inline std::string to_string(const type & value);

template <class T>
NodeSVG<T> ** createRow(TreeData<T> * data, int rowLevel, int width);

template <class T>
void deleteRow(NodeSVG<T> ** row, int len);

template <class T>
Point getParentOrigin(NodeSVG<T> * child, NodeSVG<T> ** above, int aboveLen);

template <class T>
void DrawConnections(Document doc, NodeSVG<T> ** row, NodeSVG<T> ** above, int rowLen, int aboveLen);

template <class T>
void DrawRow(Document &doc, NodeSVG<T> ** row, int rowLen);

template <class T>
void drawTreeSVG(TreeData<T> * data);

#endif //WORKBENCH_TREESVG_H
