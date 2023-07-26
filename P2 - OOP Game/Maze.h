//T02_G10
#ifndef MAZE_H
#define MAZE_H

#include "Post.h"
#include <vector>

class Maze {
    public:
        Maze(); // Default Maze class constructor, not used
        Maze(int numRows, int numCols); // Maze class constructor using maze dimensions
        int getnumRows() const; // Returns the number of rows in the maze
        int getnumCols() const; // Returns the number of columns in the maze
        void addPost(Post post); // Adds an object of Post class to the maze
        std::vector<Post> getPosts() const; // Returns all the posts in the maze

    private:
        int numRows, numCols;
        std::vector<Post> Posts;

};

#endif //MAZE_H
