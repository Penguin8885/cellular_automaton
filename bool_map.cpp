#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "bool_map.h"

using namespace std;

bool_map::bool_map(int size_x, int size_y): size_x(size_x), size_y(size_y) {
    data.resize(size_x);
    for(int i = 0; i < size_x; i++){
        data[i].resize(size_y, false);
    }

    FILE *gp = popen("gnuplot -persist", "w");  //-persistはgnuplotで連続で描画するためのもの
}

bool_map::~bool_map(){
    if(gp != NULL){
        pclose(gp);
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
        cout << str << endl;
    }
}

void bool_map::print_to_gnuplot(){
    if(gp == NULL){
        cout << "error : cannot open gnuplot" << endl;
        exit(EXIT_FAILURE);
    }

    /* send the data to gnuplot */
    fprintf(gp, "set terminal wxt\n");
    fprintf(gp, "set xrange[0:%d]\n", size_x);
    fprintf(gp, "set yrange[0:%d]\n", size_y);
    fprintf(gp, "plot '-' with points pointtype 4\n");
    for (int i = 0; i < size_x; i++){
        for (int j = 0; j < size_y; j++){
            if (data[i][j] == true){
                fprintf(gp, "%d %d\n", i, j);
            }
        }
    }
    fprintf(gp, "e\n");
}
