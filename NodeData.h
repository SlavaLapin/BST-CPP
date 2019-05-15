//
// Created by slava on 15.05.19.
//

#ifndef WORKBENCH_NODEDATA_H
#define WORKBENCH_NODEDATA_H

template <class T>
struct NodeData{
    T value;

    int id;
    int parentId;
    bool leftChild;

    int level;

    NodeData(T val, int id, int parent, bool left, int level):
    value(val), id(id), parentId(parent), leftChild(left), level(level) {}
};

template <class T>
struct TreeData{
    NodeData<T> ** nodeDataArray; // array of arrays of levels of NodeData
    int * nodesByLevel; // array of lengths of individual rows
    int nodeCount;
    int levels;
    int mostNodesOnLevel;

    TreeData(NodeData<T> * list, int total)
    {
        nodeCount = total;
        levels = _findMaxLevel(list);
        nodesByLevel = _countByLevel(list, nodeCount, levels);
        mostNodesOnLevel = _findLargestRow(nodesByLevel, levels);
        nodeDataArray = _orderByLevel(list);
    }

    ~TreeData()
    {
        for(int i = 0; i < levels; ++i)
        {
            for(int j = 0; j < nodesByLevel[i]; ++j)
            {
                delete nodeDataArray[i][j];
            }
        }
    }

private:

    int _findMaxLevel(NodeData<T> * list)
    {
        int maxLevel = 0;
        for (int i = 0; i < this->nodeCount; ++i)
        {
            if (list[i].level > maxLevel) maxLevel = list[i].level;
        }
        return maxLevel;
    }

    int * _countByLevel(NodeData<T> * list)
    {
        int * countByLevel = new int [this->levels];
        for (int i = 0; i < this->nodeCount; ++i)
        {
            countByLevel[list[i].level]++;
        }
    }

    int _findLargestRow()
    {
        int max = 0;
        for(int i = 0; i < this->levels; ++i)
        {
            if (this->nodesByLevel[i] > max) max = nodesByLevel[i];
        }
        return max;
    }

    NodeData<T> ** _orderByLevel(NodeData<T> * list)
    {
        auto ** nodeRows = new NodeData<T> * [levels];
        for(int i = 0; i < levels; ++i)
        {
            nodeRows[i] = new NodeData<T> [nodesByLevel[i]];
        }

        int * rowCounter = new int[levels];
        for (int i = 0; i < levels; ++i)
        {
            rowCounter[i] = 0;
        }
        for(int i = 0; i < nodeCount; ++i)
        {
            nodeRows[list[i].level][rowCounter[list[i].level]]++;
            rowCounter[list[i].level]++;
        }

        return nodeRows;
    }
};

#endif //WORKBENCH_NODEDATA_H
