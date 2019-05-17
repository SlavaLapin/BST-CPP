#include <string>
#include <sstream>
#include "simple_svg_1.0.0.hpp"
#include "NodeData.h"
using namespace svg;

// Demo page shows sample usage of the Simple SVG library.

int MINIMAL_GAP;
int VERTICAL_GAP;
int BLOCK_HEIGHT;
int BLOCK_WIDTH;
int PADDING_X;
int PADDING_Y;
int FONT_SIZE = 14;

template<class type>
inline std::string to_string(const type & value)
{
    std::ostringstream streamOut;
    streamOut << value;
    return streamOut.str();
}

struct NodeSVG
{
        int id;
        Point origin;
        string valueStr;
        int parentId;
        bool leftChild;

        NodeSVG(Point origin, NodeData<T> const * node): id(node->id), origin(origin), valueStr(to_string(node->value)), parentId(node->parentID), leftChild(node->leftChild) {}
};

NodeSVG ** createRow(TreeData<T> * data, int rowLevel)
{
    int rowNodes = data->nodesByLevel[rowLevel];
    NodeSVG ** row = new * NodeSVG[data->nodesByLevel[rowLevel]];
    int gapHorForRow = (width - BLOCK_WIDTH * rowNodes) / (rowNodes + 1);

    for (int i =  0; i < data->nodesByLevel[data->levels-1]; i++)
    {
        Point bottomLeftCorner = Point( (gapHorForRow*(i+1)+BLOCK_WIDTH*i), (100 + VERTICAL_GAP * (data->levels - rowLevel) + BLOCK_HEIGHT * (data->levels - rowLevel - 1)) );
        row[i] = new NodeSVG(bottomLeftCorner, data->nodeDataArray[rowLevel][i]);
    }

    return row;
}

void deleteRow(NodeSVG ** row, int len)
{
    for (int j = 0; j < len; j++)
    {
        delete row[j];
    }
    delete [] row;
}

Point& getParentOrigin(NodeSVG * child, NodeSVG ** above, int aboveLen)
{
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

void DrawConnections(Document doc, NodeSVG ** row, NodeSVG ** above, int rowLen, int aboveLen)
{
    for (int i = 0; i < rowLen; ++i)
    {
        Point a = row[i]->origin;
        a.x += BLOCK_WIDTH / 2;
        a.x += BLOCK_HEIGHT;
        Point b = getParentOrigin(row[i], above, aboveLen);
        b.x += BLOCK_WIDTH / 2;

        Polygon line(Stroke(10, (row[i]->leftChild ? Color::Blue : Color::Red)));
        border << a << b;
        doc << line;
    }
};

void DrawRow(Document doc, NodeSVG ** row, int rowLen)
{
    for (int i = 0; i < len; ++i)
    {
        doc << Rectangle(row[i]->origin, BLOCK_WIDTH, BLOCK_HEIGHT, Color::White);
        doc << Text(row[i]->origin, row[i]->valueStr, Color::Black, Font(FONT_SIZE, "Verdana")).offset(PADDING_X, PADDING_Y);
    }
        //maybe a border
};




void drawTreeSVG(TreeData<T> * data)
{
    // set canvas size
    int height = ((data->levels + 1)) * VERTICAL_GAP) + (data->levels * BLOCK_HEIGHT);
    int width = ((data->mostNodesOnLevel + 1) * MINIMAL_GAP) + (data->mostNodesOnLevel * BLOCK_WIDTH);
    Dimensions dimensions(width, height);
    Document doc("BST.svg", Layout(dimensions));

    // create a row of ** data
    NodeSVG ** above = NULL;
    int rowLevel = data->levels-1; // last level
    NodeSVG ** row = createRow(data, rowLevel); // enough pointers to pointers for all nodes of last row

    for (int i = rowLevel; i >= 0; --i)
    {
        if ((i - 1) >= 0)
        {
            above = createRow(data, i-1);
            drawConnections(doc, row, above, data->nodesByLevel[i], data->nodesByLevel[i-1]);
        }
        drawRow(doc, row, data->nodesByLevel[i]);

        deleteRow(row, data->nodesByLevel[i]);
        row = above;
    }

    deleteRow(row, 1); // top row always consists of 1 node

    doc.save();

}


int main()
{
    Dimensions dimensions(1000, 1000);
    Document doc("my_svg.svg", Layout(dimensions, Layout::BottomLeft));

    // Red image border.
    Polygon border(Stroke(10, Color::Red));
    border << Point(0, 0) << Point(dimensions.width, 0)
        << Point(dimensions.width, dimensions.height) << Point(0, dimensions.height);
    doc << border;

    // Long notation.  Local variable is created, children are added to varaible.
    //LineChart chart(5.0);
    //Polyline polyline_a(Stroke(.5, Color::Blue));
    //Polyline polyline_b(Stroke(.5, Color::Aqua));
    //Polyline polyline_c(Stroke(.5, Color::Fuchsia));
    //polyline_a << Point(0, 0) << Point(10, 30)
    //    << Point(20, 40) << Point(30, 45) << Point(40, 44);
    //polyline_b << Point(0, 10) << Point(10, 22)
    //    << Point(20, 30) << Point(30, 32) << Point(40, 30);
    //polyline_c << Point(0, 12) << Point(10, 15)
    //    << Point(20, 14) << Point(30, 10) << Point(40, 2);
    //chart << polyline_a << polyline_b << polyline_c;
    //doc << chart;

    // Condensed notation, parenthesis isolate temporaries that are inserted into parents.
    //doc << (LineChart(Dimensions(65, 5))
    //    << (Polyline(Stroke(.5, Color::Blue)) << Point(0, 0) << Point(10, 8) << Point(20, 13))
    //    << (Polyline(Stroke(.5, Color::Orange)) << Point(0, 10) << Point(10, 16) << Point(20, 20))
    //    << (Polyline(Stroke(.5, Color::Cyan)) << Point(0, 5) << Point(10, 13) << Point(20, 16)));

    //doc << Circle(Point(80, 80), 20, Fill(Color(100, 200, 120)), Stroke(1, Color(200, 250, 150)));

    doc << Text(Point(0, 0), "Simple SVG", Color::Silver, Font(10, "Verdana"));

    //doc << (Polygon(Color(200, 160, 220), Stroke(.5, Color(150, 160, 200))) << Point(20, 70)
    //    << Point(25, 72) << Point(33, 70) << Point(35, 60) << Point(25, 55) << Point(18, 63));

    doc << Rectangle(Point(100, 150), 200, 100, Color::Blue); //three blocks - max, mingap - 100
    doc << Rectangle(Point(400, 150), 200, 100, Color::Red);
    doc << Rectangle(Point(700, 150), 200, 100, Color::Blue);

    doc << Rectangle(Point(200, 300), 200, 100, Color::Blue); //height acts weird
    doc << Rectangle(Point(600, 300), 200, 100, Color::Red);

    doc.save();
}
