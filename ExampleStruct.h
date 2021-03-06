//
// Created by slava on 06.06.19.
//

#ifndef WORKBENCH_EXAMPLESTRUCT_H
#define WORKBENCH_EXAMPLESTRUCT_H

#include <string>
#include <iostream>

struct ExampleStructStudent{
    std::string name;
    float points;
    ExampleStructStudent(std::string name = "nobody", float points = 0): name(name), points(points) {}

    ExampleStructStudent& operator= (const ExampleStructStudent& original)
    {
        this->name = original.name;
        this->points = original.points;
        return *this;
    }
};

bool operator< (const ExampleStructStudent& left, const ExampleStructStudent& right)
{
    return (left.name < right.name);
}

bool operator> (const ExampleStructStudent& left, const ExampleStructStudent& right)
{
    return !(left.name < right.name);
}

bool operator== (const ExampleStructStudent& left, const ExampleStructStudent& right)
{
    return !((left > right) || (left < right));
}

std::ostream & operator << (std::ostream &out, const ExampleStructStudent &s)
{
    out << s.name;
    out << ": " << s.points << std::endl;
    return out;
}


#endif //WORKBENCH_EXAMPLESTRUCT_H
