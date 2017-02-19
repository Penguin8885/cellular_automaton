#include <iostream>
#include <cstdlib>
#include <vector>
#include "bool_map.h"

using namespace std;

bool_map::bool_map(int size_x, int size_y): size_x(size_x), size_y(size_y) {
        data.resize(size_x);
        for(int i = 0; i < size_x; i++){
            data[i].resize(size_y, false);
        }
    }

int bool_map::get_size_x(){
    return size_x;
}

int bool_map::get_size_y(){
    return size_y;
}

vector<bool>& bool_map::operator[](int x){
    return data[x];
}

void bool_map::print(){
    system("cls");
    for(int i = 0; i < size_y; i++){
        string str("");
        for(int j = 0; j < size_x; j++){
            if(data[j][i])
                str += "#";
            else
                str += " ";
        }
        cout << str << '\n';
    }
}
