# def_helper
A Macro based c++ structure def helper. 


By simple macro, you can have a data structure which come with
1) get/set or director
2) POD (optional)
3) to_json support
4) a lock for each function (optional) or
5) a embeded global luck (optional)
6) an update package.
7) support standard container


#usage

in c++ head file define a package like the 

#define PLAIN_STRUCTURE_NAME SampleType


#define PLAIN_STRUCTURE_FIELD_DECLARATION(X)                            \
    PLAIN_STRUCTURE_FIELD_DEF (char,            char_variable,         'A')          DEF_SEP(X) \
    PLAIN_STRUCTURE_FIELD_DEF (int,             int_variable,           0)           DEF_SEP(X) \
    PLAIN_STRUCTURE_FIELD_DEF (std::set<int>,   set_variable,           std::set<int>())


#include "../def_helper/plain_structure.h"

It will automaticlly create the corresponding class.


# examples
examples can be find in test/t1.cpp

build it with

gcc t1.cpp  -g -std=c++11  -lstdc++ -o t

