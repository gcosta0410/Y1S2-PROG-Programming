//T02_G10
#include "./include/Exit.h"  

// Exit class constructor
Exit::Exit(int row, int col){
	this->row = row;
    this->col = col;
}
// Returns the row of an exit
int Exit::getRow() const{
    return this->row;
}
// Returns the column of an exit
int Exit::getCol() const{
    return this->col;
}
