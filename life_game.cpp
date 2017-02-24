#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "bool_map.h"

using namespace std;

class life_game {
private:
    int size_x;
    int size_y;
    bool_map* game_map = NULL;
    vector< vector<int> > count_map;

public:
    life_game(string file_name){
        ifstream fin(file_name.c_str(), ios::in | ios::binary);
        if(!fin){
            cout << "error : cannot open the file";
            exit(EXIT_FAILURE);
        }

        int buf[2];

        fin.read((char*)buf, sizeof(int)*2);
        size_x = buf[0];
        size_y = buf[1];
        game_map = new bool_map(size_x, size_y);
        count_map.resize(size_x);
        for(int i = 0; i < size_x; i++){
            count_map[i].resize(size_y);
        }

        while(!fin.eof()){
            fin.read((char*)buf, sizeof(int)*2);
            (*game_map)[(char)buf[0]][(char)buf[1]] = true;
        }
    }

    life_game(int init_x, int init_y): size_x(init_x), size_y(init_y) {
        game_map = new bool_map(init_x, init_y);
        count_map.resize(init_x);
        for(int i = 0; i < init_x; i++){
            count_map[i].resize(init_y);
        }

        /* random initialize */
        srand(time(NULL));
        for(int i = 0; i < init_x; i++){
            for(int j = 0; j < init_y; j++){
                double t = (double)rand() / RAND_MAX;
                if(t < 0.5)
                    (*game_map)[i][j] = true;
                else
                    (*game_map)[i][j] = false;
            }
        }
    }

public:
    void update(){
        for(int i = 0; i < size_x; i++){
            for(int j = 0; j < size_y; j++){
                int im = (i + size_x) % size_x;
                int jm = (j + size_y) % size_y;
                int ip = (i + 1) % size_x;
                int jp = (j + 1) % size_y;

                count_map[i][j] = 0;

                if((*game_map)[im][jm] == true) count_map[i][j]++;
                if((*game_map)[im][j] == true) count_map[i][j]++;
                if((*game_map)[im][jp] == true) count_map[i][j]++;

                if((*game_map)[i][jm] == true) count_map[i][j]++;
                if((*game_map)[i][jp] == true) count_map[i][j]++;

                if((*game_map)[ip][jm] == true) count_map[i][j]++;
                if((*game_map)[ip][j] == true) count_map[i][j]++;
                if((*game_map)[ip][jp] == true) count_map[i][j]++;
            }
        }

        for(int i = 0; i < size_x; i++){
            for(int j = 0; j < size_y; j++){
                if((*game_map)[i][j] == true){
                    switch(count_map[i][j]){
                        case 0:
                        case 1:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                            (*game_map)[i][j] = false;
                            break;
                        default:
                            break;
                    }
                }
                else{
                    switch(count_map[i][j]){
                        case 3:
                            (*game_map)[i][j] = true;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    void print(){
        game_map->print_to_gnuplot();
    }
};

int main(){
    life_game lg("sample3.dat");

    for(int i = 0; ; i++){
        lg.print();
        lg.update();
        for(int i = 0; i < 10000000; i++); //sleep
    }

    return 0;
}
