#ifndef _BOOL_MAP_H
#define _BOOL_MAP_H

#include <vector>

class bool_map {
private:
    int size_x;
    int size_y;
    std::vector< std::vector<bool> > data;

public:
    bool_map(int size_x, int size_y);

public:
    int get_size_x();
    int get_size_y();
    std::vector<bool>& operator[](int x);

public:
    void print();
};

#endif
