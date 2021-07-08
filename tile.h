#ifndef TILE_H
#define TILE_H

#include <iostream> // Debugging
#include <vector>
using namespace std;

enum TILE_TYPE {
    NONE,
    START,
    END
};

class tile {
public:
    int weight;
    TILE_TYPE type;
    tile* parent;
    vector<tile*> children;
    int hash;

    tile(int _coords) {
        weight = rand();
        type = NONE;
        hash = _coords;
    }
};

#endif