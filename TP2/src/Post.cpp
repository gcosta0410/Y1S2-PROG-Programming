//T02_G10
#include "./include/Post.h"
// Post class constructor using it's position and char representation
Post::Post(int row, int col, char symbol){
    this->row = row;
    this->col = col;
    this->symbol = symbol;
    if(symbol == '*'){
        this->state = ALIVE;
    }
    else{
        this->state = DEAD;
    }
}
// Returns the row of a post
int Post::getRow() const{
    return this->row;
}
// Returns the column of a post
int Post::getCol() const{
    return this->col;
}
//Returns the char representation of a post
char Post::getSymbol() const{
    return this->symbol;
}
// Returns true if post is electrified (Alive = '*'), false otherwise
bool Post::isElectrified() const{
    return (this->state == ALIVE) ? true : false;
}
// "Kills" an electrified post
void Post::changeState(){
    this->state = DEAD;
    this->symbol = '+';
}
