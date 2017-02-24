#include "bool_map.h"

using namespace std;

class langtons_ant {
private:
    int x;
    int y;
    int direction;
    bool_map game_map;

public:
    langtons_ant(int map_x, int map_y, int ant_x, int ant_y): game_map(map_x, map_y), x(ant_x), y(ant_y) {
        direction = 0;
    }

public:
    void move(){
        if(game_map[x][y]){
            game_map[x][y] = false;
            direction = (direction + 1) % 4;
        }
        else{
            game_map[x][y] = true;
            direction = (direction + 3) % 4;
        }
        switch(direction){
            case 0: //east
                x = (x + 1) % game_map.get_size_x();
                break;
            case 1: //north
                y = (y + 1) % game_map.get_size_y();
                break;
            case 2: //west
                x = (x + game_map.get_size_x() - 1) % game_map.get_size_x();
                break;
            case 3: //south
                y = (y + game_map.get_size_y() - 1) % game_map.get_size_y();
                break;
        }
    }

    void print(){
        game_map.print_to_gnuplot();
    }
};

int main(){
    langtons_ant lant(80, 20, 40, 10);

    for(int i = 0; ; i++){
        if(i%100 == 0) lant.print();
        lant.move();
        for(int i = 0; i < 100000; i++); //sleep
    }

    return 0;
}
