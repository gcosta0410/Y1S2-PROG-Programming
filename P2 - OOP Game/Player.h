//T02_G10
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
    public:
        Player(); // Default Player class constructor, not used
        Player(int Row, int Col, char symbol); // Player class constructor using it's position and char representation
        void setPos(int row, int col); // Sets player position to the given position
        void addRow(int row); // Adds given amount to the row position of the player
        void addCol(int col); // Adds given amount to the column position of the player
        int getRow() const; // Returns the row of the player
        int getCol() const; // Returns the column of the player
        char getSymbol() const; // Returns the char representation (H or h) of the player
        bool isAlive() const; // Returns true if player is alive, false otherwise
        void setAsDead(); // Kills the player
        std::string getName(); // Returns the player's name
    private:
        int Row, Col;
        bool alive;
        char symbol;
        std::string name;
};


#endif //PLAYER_H
