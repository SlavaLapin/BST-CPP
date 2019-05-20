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
        std::cout<<"!!!!! - TreeData Constructor started"<<std::endl;
        nodeCount = total;
        std::cout<<"Supplied nodes total: "<<nodeCount<<std::endl;
        levels = _findMaxLevel(list);
        std::cout<<"Max level found: "<<levels<<std::endl;
        nodesByLevel = _countByLevel(list);
        std::cout<<"Level-NodesCount array created"<<std::endl;
        mostNodesOnLevel = _findLargestRow();
        std::cout<<"Largest Row found"<<std::endl;
        nodeDataArray = _orderByLevel(list);
        std::cout<<"Level-Nodes array created"<<std::endl;
        delete [] list;
        std::cout<<"Original list deleted. Constructor DONE!"<<std::endl;
    }

    ~TreeData()
    {
        std::cout<<"TreeData destructor"<<std::endl;
        if (nodeDataArray != NULL) {
            for (int i = 0; i < levels; ++i)
            {
                std::cout<<"Destroying an array of NodeData structs forming level "<<i<<std::endl;
                delete[] nodeDataArray[i];
            }
        } else{
            std::cout<<"This TreeData was sent for deletion without its nodeDataArray **. I wonder where it has gone!"<<std::endl;
        }
        std::cout<<"Destroying an array of NodeData * - it held arrays for levels "<<std::endl;
        delete [] nodeDataArray;

        std::cout<<"Destroying an array of ints"<<std::endl;
        delete[] nodesByLevel;
        std::cout<<"All memory freed. Nothing left to delete"<<std::endl;
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
        int *countByLevel = NULL;

        try {
            countByLevel =  new int[this->levels];
        }
        catch(std::bad_alloc &ba){
            std::cout<<"!!! - Failed allocating space for an array of "<<this->levels<<" ints to be used as individual level counters"<<std::endl;
            return countByLevel;
        }

        for (int i = 0; i < this->nodeCount; ++i)
        {
            countByLevel[i] = 0;
        }

        for (int i = 0; i < this->nodeCount; ++i)
        {
            std::cout<<"Node ID: "<<i<<"/"<<this->nodeCount<<" Level: "<<list[i].level<<" ";
            (countByLevel[list[i].level])++;
        }

        return countByLevel;
    }

    int _findLargestRow()
    {
        int max = 0;
        for(int i = 0; i < this->levels; ++i)
        {
            std::cout<<"On level "<<i<<" there are "<<nodesByLevel[i]<<" nodes"<<std::endl;
            if (this->nodesByLevel[i] > max) max = nodesByLevel[i];
        }
        std::cout<<"Largest level contains "<<max<<" nodes"<<std::endl;
        return max;
    }

    NodeData<T> ** _orderByLevel(NodeData<T> * list)
    {
        // this function does something which causes bad alloc
        NodeData<T> ** nodeRows = new NodeData<T> * [levels];
        std::cout<<"NodeData<T> ** nodeRows allocated"<<std::endl;
        for(int i = 0; i < levels; ++i)
        {
            try {
                nodeRows[i] = new NodeData<T>[nodesByLevel[i]];
            }
            catch (std::bad_alloc &ba){
                std::cout<<"!!! - Failed allocating NodeData<T> ["<<i<<"] of length "<<nodesByLevel[i]<<", levels:"<<levels<<std::endl<<ba.what()<<std::endl;
            }
        }
        std::cout<<"Each NodeData<T> [] allocated"<<std::endl;

        int * rowCounter = new int[levels];
        for (int i = 0; i < levels; ++i)
        {
            rowCounter[i] = 0;
        }
        std::cout<<"Array of counters created and initialised"<<std::endl;
        for(int i = 0; i < nodeCount; ++i)
        {
            NodeData<T> & tmp = list[i];
            nodeRows[tmp.level][rowCounter[tmp.level]]=NodeData<T>(tmp.value, tmp.id, tmp.parentId, tmp.leftChild, tmp.level);
            rowCounter[tmp.level]++;
        }
        std::cout<<"NodeData s created"<<std::endl;

        return nodeRows;
    }
};

#endif //WORKBENCH_NODEDATA_H
