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

    NodeData():
    value(-1), id(-1), parentId(-1), leftChild(false), level(-1) {};

    NodeData(T val, int id, int parent, bool left, int level):
    value(val), id(id), parentId(parent), leftChild(left), level(level) {};

    NodeData &operator=(NodeData<T> const & original)
    {
        this->value=original.value;
        this->id=original.id;
        this->parentId=original.parentId;
        this->leftChild=original.leftChild;
        this->level=original.level;
        return *this;
    }
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
        nodesByLevel = _countByLevel(list);
        mostNodesOnLevel = _findLargestRow();
        nodeDataArray = _orderByLevel(list);
        delete [] list;
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

        delete[] nodesByLevel;
    }

private:

    int _findMaxLevel(NodeData<T> * list)
    {
        int maxLevel = 0;
        for (int i = 0; i < this->nodeCount; ++i)
        {
            if (list[i].level > maxLevel) maxLevel = list[i].level;
        }
        return maxLevel+1;
    }

    int * _countByLevel(NodeData<T> * list)
    {
        int * countByLevel = new int [this->levels];
        for (int i = 0; i < this->nodeCount; ++i)
        {
            countByLevel[list[i].level]++;
        }

        return countByLevel;
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
        NodeData<T> ** nodeRows = new NodeData<T> * [levels];
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
            NodeData<T> & tmp = list[i];
            nodeRows[tmp.level][rowCounter[tmp.level]]=NodeData<T>(tmp.value, tmp.id, tmp.parentId, tmp.leftChild, tmp.level);
            rowCounter[tmp.level]++;
        }

        return nodeRows;
    }
};

#endif //WORKBENCH_NODEDATA_H
