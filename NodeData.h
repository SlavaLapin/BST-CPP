//
// Created by slava on 15.05.19.
//

#ifndef WORKBENCH_NODEDATA_H
#define WORKBENCH_NODEDATA_H

#include <iostream>

template <class T>
struct NodeData{
    T value;

    int id;
    int parentId;
    bool leftChild;

    int level;

    NodeData()
    {
        id = -1;
        parentId = -1;
        level = -1;
        leftChild = false;
    };

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
        if (nodesByLevel == NULL){std::cout<<"Internal error"<<std::endl; return;}
        mostNodesOnLevel = _findLargestRow();
        nodeDataArray = _orderByLevel(list);
        if (nodeDataArray == NULL){std::cout<<"Internal error"<<std::endl; return;}

        delete [] list;
    }

    ~TreeData()
    {
        if (nodeDataArray != NULL) {
            for (int i = 0; i < levels; ++i)
            {
                delete[] nodeDataArray[i];
            }
        } else{
            std::cout<<"This TreeData was sent for deletion without its nodeDataArray **. I wonder where it has gone!"<<std::endl;
        }
        delete [] nodeDataArray;

        delete[] nodesByLevel;
    }

private:

    int _findMaxLevel (NodeData<T> const * list) const
    {
        int maxLevel = 0;
        for (int i = 0; i < this->nodeCount; ++i)
        {
            if (list[i].level > maxLevel) maxLevel = list[i].level;
        }
        return maxLevel+1;
    }

    int * _countByLevel(NodeData<T> const * list) const
    {
        int *countByLevel = nullptr;

        try {
            countByLevel =  new int[this->levels];
        }
        catch(std::bad_alloc &ba){
            std::cout<<"Failed allocating space for an array of "<<this->levels<<" ints to be used as individual level counters"<<std::endl;
            return countByLevel;
        }

        for (int i = 0; i < this->levels; ++i)
        {
            countByLevel[i] = 0;
        }

        for (int i = 0; i < this->nodeCount; ++i)
        {
            (countByLevel[list[i].level])++;
        }

        return countByLevel;
    }

    int _findLargestRow () const
    {
        int max = 0;
        for(int i = 0; i < this->levels; ++i)
        {
            if (this->nodesByLevel[i] > max) max = nodesByLevel[i];
        }
        return max;
    }

    NodeData<T> ** _orderByLevel(NodeData<T> const * list) const
    {
        // this function does something which causes bad alloc
        NodeData<T> **nodeRows = NULL;
        try {
            nodeRows = new NodeData<T> * [levels];
        }
        catch (std::bad_alloc &ba)
        {
            std::cout<<"Failed allocating NodeData<T> ** of size "<<levels<<std::endl<<ba.what()<<std::endl;
            return nodeRows;
        }
        for(int i = 0; i < levels; ++i)
        {
            try {
                nodeRows[i] = new NodeData<T>[nodesByLevel[i]];
            }
            catch (std::bad_alloc &ba){
                std::cout<<"!!! - Failed allocating NodeData<T> ["<<i<<"] of length "<<nodesByLevel[i]<<", levels:"<<levels<<std::endl<<ba.what()<<std::endl;
            }
        }

        int * rowCounter = new int[levels];
        for (int i = 0; i < levels; ++i)
        {
            rowCounter[i] = 0;
        }

        for(int i = 0; i < nodeCount; ++i)
        {
            const NodeData<T> & tmp = list[i];
            nodeRows[tmp.level][rowCounter[tmp.level]]=NodeData<T>(tmp.value, tmp.id, tmp.parentId, tmp.leftChild, tmp.level);
            rowCounter[tmp.level]++;
        }

        return nodeRows;
    }
};

#endif //WORKBENCH_NODEDATA_H
