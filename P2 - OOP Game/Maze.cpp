//T02_G10
#include "Maze.h"
#include <vector>
// Default Maze class constructor, not used
Maze::Maze(){}
// Maze class constructor using maze dimensions
Maze::Maze(int numRows, int numCols){
    this->numRows = numRows;
    this->numCols = numCols;
}
// Returns the number of rows in the maze
int Maze::getnumRows() const{
    return numRows;
}
// Returns the number of columns in the maze
int Maze::getnumCols() const{
    return numCols;
}
// Adds an object of Post class to the maze
void Maze::addPost(Post post){
    Posts.push_back(post);
}
// Returns all the posts in the maze
std::vector<Post> Maze::getPosts() const {
    return this->Posts;
}
