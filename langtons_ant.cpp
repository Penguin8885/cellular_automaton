#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class bool_map {
private:
    int size_x;
    int size_y;
    vector< vector<bool> > data;

public:
    bool_map(int size_x, int size_y): size_x(size_x), size_y(size_y) {
        data.resize(size_x);
        for(int i = 0; i < size_x; i++){
            data[i].resize(size_y, false);
        }
    }

public:
    int get_size_x(){
        return size_x;
    }
    int get_size_y(){
        return size_y;
    }
    vector<bool>& operator[](int x){
        return data[x];
    }

public:
    void print(){
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
};

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
