//T02_G10
#include "./include/Robot.h"
#include "./include/Position.h"

int Robot::robotCounter = 0; // Initializing static int variable
// Default Robot class constructor, not used
Robot::Robot(){}
// Robot class constructor using it's position
Robot::Robot(int row, int col){
    this->row = row;
    this->col = col;
    this->alive = true;
    this->state = ALIVE;
    this->robotCounter += 1;
    setID();
}
// Returns the ID of a certain robot
int Robot::getID() const{
    return this->id;
}
// Returns the char representation of robot (R if alive, r if dead)
char Robot::getSymbol() const{
    return (state == ALIVE) ? 'R' : 'r';
}
// Stores the last position of a robot, allowing position rollbacks if needed
void Robot::setLastPos(int row, int col){
    Position p1;
    p1.row = row;
    p1.col = col;
    this->LastPos = p1;
}
// Returns the row of a robot
int Robot::getRow() const{
    return this->row;
}
// Returns the column of a robot
int Robot::getCol() const{
    return this->col;
}
// Returns the position of a robot
Position Robot::getPosition() const{
    return this->pos;
}
// Returns the last position of a robot
Position Robot::getLastPosition() const{
    return this->LastPos;
}
// Returns true if the robot is alive, false otherwise
bool Robot::isAlive() const{
    return this->alive;
}
// Changes the row position of a robot to a given value
void Robot::setRow(int x){
    this->row = x;
}
// Changes the cloumn position of a robot to a given value
void Robot::setCol(int y){
    this->col = y;
}
// Changes the position of a robot to a given value
void Robot::setPosition(const Position &pos){
    this->row = pos.row;
    this->col = pos.col;
    this->pos = { pos.row, pos.col };
}
// Alters the state of a robot to reflect a collision with another one
void Robot::collisionRobot(){
    this->alive = false;
    this-> state = {STUCK};
}
// Alters the state of a robot to reflect a collision with an electrified post
void Robot::collisionEletrifiedPost(){
    this->alive = false;
    this-> state = {DEAD};
}
// Alters the state of a robot to reflect a collision with an non-electrified post
void Robot::collisionNonEletrifiedPost(){
    this->alive = false;
    this-> state = {STUCK};
}
// Restarts the variable robotCounter back to 0 so a new game can be played with the normal IDs
void Robot::restartID(){
    this->robotCounter = 0;
}
//Sets the ID of a robot
void Robot::setID(){
    this->id = this->robotCounter;
}
