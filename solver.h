#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <vector>
#include <iomanip>
#include "generator.h"

using namespace std;

enum FACING {
    RIGHT,
    UP,
    LEFT,
    DOWN
};

int IndexOf(vector<int> haystack, int needle) {
    for (int i = 0, s = haystack.size(); i < s; ++i) {
        if (haystack[i] == needle) {
            return i;
        }
    }

     return -1;
}

bool Contains(vector<tile*> haystack, tile* needle) {
    for (tile* item : haystack) {
        if (item == needle) {
            return true;
        }
    }

    return false;
}

class solver {
public:

    generator* map;
    int x, y;
    FACING dir;

    solver(generator* _map) {
        map = _map;
        dir = FACING::UP;
        x = map->startX;
        y = map->startY;

        PrintMap();
        Solve();
    }

    // Right: 1, Up: 2, Left: 4, Down: 8 --> F
    void PrintMap() {
        for (int i = 0; i < map->h; ++i) {
            for (int j = 0; j < map->w; ++j) {
                tile* curr = map->maze.at(i).at(j);
                if (curr->parent == nullptr) {
                    cout << 0;
                    continue;
                }
                int diff = curr->hash - curr->parent->hash;

                if (!Contains(curr->children, curr->parent)) {
                    curr->children.push_back(curr->parent);
                }

                if (diff == -1) {
                    cout << 1;
                } else if (diff == map->w) {
                    cout << 2;
                } else if (diff == 1) {
                    cout << 4;
                } else if (diff == -map->w) {
                    cout << 8;
                } else {
                    cout << 0;
                }
            }

            cout << endl;
        }

        cout << "Goal: (" << map->endX << ", " << map->endY << ")" << endl;
    }

    void Solve() {
        tile* curr;
        while (!(x == map->endX && y == map->endY)) {
            cout << "Moved! (" << x << ", " << y << ")" << endl;
            curr = map->maze.at(y).at(x);

            vector<int> neighbors;

            for (tile* t : curr->children) {
                neighbors.push_back(curr->hash - t->hash);
            }

            switch (dir) {
                case FACING::UP:
                    if (IndexOf(neighbors, -1) != -1) {
                        dir = FACING::RIGHT;
                        ++x;
                    } else if (IndexOf(neighbors, map->w) != -1) {
                        --y;
                    } else if (IndexOf(neighbors, 1) != -1) {
                        dir = FACING::LEFT;
                        --x;
                    } else {
                        ++y;
                        dir = FACING::DOWN;
                    }
                    break;
                case FACING::RIGHT:
                    if (IndexOf(neighbors, -map->w) != -1) {
                        dir = FACING::DOWN;
                        ++y;
                    } else if (IndexOf(neighbors, -1) != -1) {
                        ++x;
                    } else if (IndexOf(neighbors, map->w) != -1) {
                        dir = FACING::UP;
                        --y;
                    } else {
                        dir = FACING::LEFT;
                        --x;
                    }
                    break;
                case FACING::DOWN:
                    if (IndexOf(neighbors, 1) != -1) {
                        dir = FACING::LEFT;
                        --x;
                    } else if (IndexOf(neighbors, -map->w) != -1) {
                        ++y;
                    } else if (IndexOf(neighbors, -1) != -1) {
                        dir = FACING::RIGHT;
                        ++x;
                    } else {
                        dir = FACING::UP;
                        --y;
                    }
                    break;
                case FACING::LEFT:
                    if (IndexOf(neighbors, map->w) != -1) {
                        dir = FACING::UP;
                        --y;
                    } else if (IndexOf(neighbors, 1) != -1) {
                        --x;
                    } else if (IndexOf(neighbors, -map->w) != -1) {
                        dir = FACING::DOWN;
                        ++y;
                    } else {
                        dir = FACING::RIGHT;
                        ++x;
                    }
                    break;
            }

        }

        DisplayResult();
    }

    void DisplayResult() {
        cout << "Completed the solve: (" << x << ", " << y << ")" << endl;
    }

};
#endif