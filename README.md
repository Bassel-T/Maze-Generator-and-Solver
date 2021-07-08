# Maze Generation and Solver

## Introduction

The purpose of this project is to independently generate a random maze and solve it. That means: The AI aiming to solve it will only know the layout of the map.

## Maze Generation

The maze will be a two-dimensional grid, likely in array form. My initial idea was to have a 2D array of bytes. Each byte would have a bit for each directional connector. The 1 digit would be left, 2 would be right, 4 for up, and 8 for down. Two adjacent tiles would have to have corresponding bits. That is to say: If a tile has a left connector, the tile to its left must have a right connector. Conversely, if a bit does not have a left connector, the tile to its left cannot have a right connector. However, that would be a convoluted nightmare that I don't want to deal with.

My second idea was to implement a variant of a noise-based algorithm I once used for a different game, but remaking it for C++ rather than the initial C#. While the algorithm is used to generate large, open rooms for dungeon-crawler style games, flipping a single boolean interestingly creates corridors. The issue with this algorithm, however, is that it can be slow, and it can create long hallways that don't turn, effectively creating a more "grid" based pattern. Furthermore, it can result in several "rooms," which I will define as "disjunct groups of tiles."

My third idea, which is also the most promising, is to implement a Depth-First Search (DFS) on a grid of nodes, each with a random weight. A node will keep track of its parent and children. The DFS will recurse backward when a wall is hit (checking for an out of bounds exception). The "backtracking" will happen via a stack, and the generation will terminate when the stack is empty.

Following the empty stack, two sets of coordinates will be chosen as the beginning and the ending. The solver will be placed at the start, with the task of reaching the end.

# Maze Solver

While it may be more efficient to use DFS for generation and solver, I want both parts to utilize different algorithms.

This solver will use a Simple Reflex Agent (SRA). An SRA looks at the location's current state, ignores its history, and makes a decision based on the decision. Because of how the DFS algorithm will work, there should be no loops in the system: Every node can be reached using exactly one path without back-tracking. Therefore, I'll be using a little trick I once learned for maze solving.

If you're ever placed in a simple, non-looping maze, if a right turn is possible, turn right and move forward one space. If a right turn is not possible but the agent can keep moving forward, continue forward. If neither statement is true but a left turn is possible, turn left and move forward one space. If a dead-end has been reached, turn around.

Therefore, the solver must also be given the ability to check its surroundings and know its orientation.