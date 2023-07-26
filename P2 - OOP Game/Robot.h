//T02_G10
#ifndef ROBOT_H
#define ROBOT_H

#include "Position.h"

class Robot{
    public:
        Robot(); // Default Robot class constructor, not used
        Robot(int row, int col); // Robot class constructor using it's position
        enum State { ALIVE, STUCK, DEAD }; // Enum type with possible states of a Robot object
        int getID() const; // Returns the ID of a certain robot
        char getSymbol() const; // Returns the char representation of robot (R if alive, r if dead)
        void setLastPos(int row, int col); // Stores the last position of a robot, allowing position rollbacks if needed
        int getRow() const; // Returns the row of a robot
        int getCol() const; // Retruns the column of a robot
        Position getPosition() const; // Returns the position of a robot
        Position getLastPosition() const; // Returns the last position of a robot
        bool isAlive() const; // Returns true if the robot is alive, false otherwise
        void setRow(int row); // Changes the row position of a robot to a given value
        void setCol(int col); // Changes the column position of a robot to a given value
        void setPosition(const Position &pos); // Changes the position of a robot to a given value
        void collisionRobot(); // Alters the state of a robot to reflect a collision with another one
        void collisionEletrifiedPost(); // Alters the state of a robot to reflect a collision with an electrified post
        void collisionNonEletrifiedPost(); // Alters the state of a robot to reflect a collision with an non-electrified post
        void restartID(); // Restarts the variable robotCounter back to 0 so a new game can be played with the normal IDs

    private:
        static int robotCounter; //used to attribute automatically the id to the robots
        int id;
        int row, col;
        bool alive;
        struct Position pos;
        struct Position LastPos;
        void setID(); //Sets the ID of a robot
        State state;
};
#endif //ROBOT_H

