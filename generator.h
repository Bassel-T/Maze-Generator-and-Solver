#ifndef GENERATOR_H
#define GENERATOR_H

#include "tile.h"
#include <queue>
#include <vector>
#include <algorithm>

struct CompareCost {
    bool operator() (tile const *t1, tile const *t2) {
        return t1->weight > t2->weight;
    }
};

class generator {
public:
    vector<vector<tile*>> maze;
    int startX, startY, endX, endY;
    int w, h;

    generator(int width, int height) {
        srand(time(NULL));
        w = width;
        h = height;
        // Generate the initial tiles
        for (int i = 0; i < height; ++i) {
            vector<tile*> temp;
            for (int j = 0; j < width; ++j) {
                temp.push_back(new tile(j + i * width));
            }

            maze.push_back(temp);
        }

        // Generate children
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (i > 0) {maze.at(i).at(j)->children.push_back(maze.at(i - 1).at(j));}
                if (i < height - 1) {maze.at(i).at(j)->children.push_back(maze.at(i + 1).at(j));}
                if (j > 0) {maze.at(i).at(j)->children.push_back(maze.at(i).at(j - 1));}
                if (j < width - 1) {maze.at(i).at(j)->children.push_back(maze.at(i).at(j + 1));}
            }
        }

        // Magic numbers
        int halfWidth = width / 2;
        int halfHeight = height / 2;

        // Generate start and end positions
        startX = rand() % halfWidth;
        startY = rand() % halfHeight;
        maze.at(startY).at(startX)->type = TILE_TYPE::START;

        endX = (rand() % halfWidth) + halfWidth + (width % 2);
        endY = (rand() % halfHeight) + halfHeight + (height % 2);
        maze.at(endY).at(endX)->type = TILE_TYPE::END;

        GenerateMaze();
    }

    void GenerateMaze() {
        // New node initial
        tile* start = maze.at(startY).at(startX);

        // Initialize Queue with the initial in element
        priority_queue<tile*, vector<tile*>, CompareCost> *queue = new priority_queue<tile*, vector<tile*>, CompareCost>();
        queue->push(start);

        // Initialize visited list
        vector<int> visited;
        visited.push_back(start->hash);

        tile* curr;

        // While not empty
        while (queue->size() > 0) {
            // Pop front
            curr = queue->top();
            queue->pop();

            // If not added, add it
            for (int i = 0; i < curr->children.size(); ++i) {
                if (!std::count(visited.begin(), visited.end(), curr->children[i]->hash)) {
                    curr->children[i]->parent = curr;
                    queue->push(curr->children[i]);
                    visited.push_back(curr->children[i]->hash);
                } else {
                    curr->children.erase(curr->children.begin() + i);
                    --i;
                }
            }
        }
            
    }
    
};

#endif