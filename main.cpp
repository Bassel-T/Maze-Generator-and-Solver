#include "generator.h"
#include "solver.h"

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Proper Usage:" << endl;
        cout << argv[0] << " [width] [height]";
        return 1;
    }

    int width = stoi(argv[1]);
    int height = stoi(argv[2]);

    generator *gen = new generator(width, height);
    solver *solve = new solver(gen);
    return 0;
}