#include "bool_map.h"

using namespace std;

class langtons_ant {
private:
    int x;
    int y;
    int direction;

public:
    langtons_ant(int init_x, int init_y): x(init_x), y(init_y) {
        direction = 0;
    }

public:
    void move(bool_map &map){
        if(map[x][y]){
            map[x][y] = false;
            direction = (direction + 1) % 4;
        }
        else{
            map[x][y] = true;
            direction = (direction + 3) % 4;
        }
        switch(direction){
            case 0: //east
                x = (x + 1) % map.get_size_x();
                break;
            case 1: //north
                y = (y + 1) % map.get_size_y();
                break;
            case 2: //west
                x = (x + map.get_size_x() - 1) % map.get_size_x();
                break;
            case 3: //south
                y = (y + map.get_size_y() - 1) % map.get_size_y();
                break;
        }
  }
};

int main(){
    bool_map map(80, 20);
    langtons_ant ant(40, 10);

    for(int i = 0; ; i++){
        if(i%100 == 0) map.print();
        ant.move(map);
        for(int i = 0; i < 100000; i++); //sleep
    }

    return 0;
}
