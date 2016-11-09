#ifndef _TYPE_H
#define _TYPE_H
#include <string>
#include <map>
#include <vector>


struct Node
{
    std::string         name_;
    std::string         value_;
    std::vector<Node>   child_;
};

#endif
