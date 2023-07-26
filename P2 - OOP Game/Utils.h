//T02_G10
#ifndef UTILS_H
#define UTILS_H

#include <string>

bool foundMaze(int maze, std::string &maze_name); // Returns true if MAZE_XX.txt file was found, false otherwise
bool isAllDigits(const std::string &str); // Returns true if all elements in a string as digits, false otherwise
bool isValidName(const std::string &str); // Returns true if player name is valid, false otherwise
bool playAgain(); // Returns true if player wants to play the same map again, false otherwise

#endif //UTILS_H
