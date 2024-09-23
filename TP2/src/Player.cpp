//T02_G10
#include <iostream>
#include <thread>
#include <chrono>
#include "./include/Player.h"
#include "./include/Utils.h"

// Default Player class constructor, not used
Player::Player(){}
// Player class constructor using it's position and char representation
Player::Player(int Row, int Col, char symbol){
    this->Row = Row;
    this->Col = Col;
    this->symbol = symbol;
    this->alive = true;
}
// Sets player position to the given position
void Player::setPos(int Row, int Col){
    this->Row = Row;
    this->Col = Col;
}
// Adds given amount to the row position of the player
void Player::addRow(int row){
    this->Row += row;
}
// Adds given amount to the column position of the player
void Player::addCol(int col){
    this->Col += col;
}
// Returns the row of the player
int Player::getRow() const{
    return Row;
}
// Returns the column of the player
int Player::getCol() const{
    return Col;
}
// Returns the char representation (H or h) of the player
char Player::getSymbol() const{
    return symbol;
}
// Returns true if player is alive, false otherwise
bool Player::isAlive() const{
    return alive;
}
// Kills the player
void Player::setAsDead(){
    symbol = 'h';
    alive = false;
}

std::string Player::getName(){
    
    while(true){
        // Ask for player's name
        std::cout << "Type your name (max 15 characters, may have whitespaces): ";
        std::getline(std::cin, this->name);

        if (std::cin.eof()){
            std::cout << std::endl << "Thank you for playing..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(EXIT_SUCCESS);
            }

        // If name is valid (String with only alphanumeric characters and less than 15 of them)
        if(isValidName(this->name) && this->name.length() <= 15){
            return this->name;
        }
        std::cout << "Please enter a valid name with no special characters!" << std::endl << std::endl;
    }
}
