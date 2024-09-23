//T02_G10
#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "Position.h"
#include "Player.h"
#include "Maze.h"
#include "Robot.h"
#include "Post.h"
#include "Exit.h"
#include "Timer.h"

class Game {
    public:
        Game(const std::string& filename); // Game class constructor
        bool play(); // Implements the game loop; returns true if player wins, false otherwise
        std::string getPlayerName(); // Returns player name to add to the leaderboard
        std::string getTime(); // Returns game timer to add to the leaderboard, using the format hh::mm::ss.ms
    private:
        bool isPlayer(int row, int col) const; // Returns true if the player is at given position, false otherwise
        bool isPost(int row, int col) const; // Returns true if a post is at given position, false otherwise
        bool isRobot(int row, int col) const; // Returns true if a robot is at given position, false otherwise
        bool isExit(int row, int col) const; // Returns true if an exit is at given position, false otherwise
        void getPostSymbol(int row,int col, const Maze& maze) const; // Displays the symbol (* or +) of a post object at given position
        void getRobotSymbol(int row,int col) const; // Displays the symbol (R or r) of a robot object at given position
        bool isRobotAlive(Position pos) const; // Returns true if a robot is at given position is alive, false otherwise
        bool isPostEletrified(Position pos, const Maze& maze) const; // Returns true if an electrified post is at given position, false otherwise
        void showGameDisplay() const; // Displays the current state of the maze
        bool isValid(char move); // Returns true if player movement is valid, false otherwise
        void PlayerMove(); // Asks for wanted movement and moves the player according to user input
        void undoMovement(std::string move); // Undos a player movement
        bool checkCollision(Robot &robot, Maze &maze); // Returns true if theres a colision between robots, false otherwise
        void moveRobot(Robot &robot); // Moves one specific robot
        void undoRobotMovement(Robot &robot); // Undos a robot movement
        void moveRobots(); // Moves all the robots to the nearby contiguous cell thats closest to the player
        int countRobots() const; // Returns the number of robots alive
        void checkGameState(); // Checks if player is alive
        void restartID(); // Restarts the robotID counter in case of new game


private:
        Player player;
        Maze maze;
        Timer timer;
        std::vector<Robot> robots;
        std::vector<Exit> exits;
        bool GameEnd = false;
};

#endif //GAME_H
