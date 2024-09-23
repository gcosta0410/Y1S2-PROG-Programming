//T02_G10
#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <thread>
#include "./include/Game.h"
#include "./include/Player.h"
#include "./include/Maze.h"
#include "./include/Post.h"
#include "./include/Exit.h"
#include "./include/Timer.h"

// Game class constructor that takes a string = "MAZE_XX.txt" as parameter
Game::Game(const std::string& filename){

    std::string line, line_txt;
    std::ifstream maze_txt(filename); // Read from MAZE_XX.txt file

    std::getline(maze_txt, line_txt);

    std::stringstream ss;
    std::vector<int> dimension;
    // Storing the whole string into a string stream
    ss << line_txt;
    std::string temp;
    int found;

    // Runs until end of file
    while (!ss.eof()){

        // Extracting word by word from stream
        ss >> temp;

        // Checking the given word is integer or not
        if (std::stringstream(temp) >> found){
            dimension.push_back((int)found);
        }

        // To save from space at the end of string
        temp = "";
    }
    // Storing maze size into an integer vector for Maze class object criation

    Maze newmaze(dimension[0],dimension[1]); // Creating new Maze class object
    this->maze = newmaze;

    std::cout << "Size: " << this->maze.getnumRows() << "x" << this->maze.getnumCols() << std::endl; // Display the size of the maze on screen

    int aux = 0;
    // Iterates through the lines of the MAZE_XX.txt file and stores each different element (Post, Robot, Player and Exit) into it's own Class vector
    while(std::getline(maze_txt, line)){

        // Iterates through the columns of the maze
        for (int idx = 0; idx < line.size()+1; idx++){
            if (line[idx] == 'H'){
                Player player1(aux,idx,'H');
                this->player = player1;
            }
            if(line[idx]=='R'){
                Robot robot(aux,idx);
                robots.push_back(robot);
            }
            if(line[idx] == '*'){
                maze.addPost(Post(aux,idx,'*'));
            }
            if(line[idx] == '+'){
                maze.addPost(Post(aux,idx,'+'));
            }
            if(line[idx] == 'O'){
                Exit exit(aux,idx);
                exits.push_back(exit);
            }
        }
    aux += 1;
    }
    maze_txt.close();
}
// Returns true if the player is at given position, false otherwise
bool Game::isPlayer(int row, int col) const {
    if(row == player.getRow() && col == player.getCol()){
        return true;
    }
    return false;
}
// Returns true if a post is at given position, false otherwise
bool Game::isPost(int row, int col) const {
    for(auto &post : maze.getPosts()){
        if(row == post.getRow() && col == post.getCol()){
            return true;
        }
    }
    return false;
}
// Returns true if a robot is at given position, false otherwise
bool Game::isRobot(int row, int col) const{
    for(auto robot : robots){
        if(row ==robot.getRow() && col == robot.getCol()){
            return true;
        }
    }
    return false;
}
// Returns true if an exit is at given position, false otherwise
bool Game::isExit(int row, int col) const{
    for(auto exit : exits){
        if(row ==exit.getRow() && col == exit.getCol()){
            return true;
        }
    }
    return false;
}
// Displays the symbol (* or +) of a post object at given position
void Game::getPostSymbol(int row, int col, const Maze& maze) const{
    for(auto &post : maze.getPosts()){
        if(row == post.getRow() && col == post.getCol()){
            std::cout << post.getSymbol();
            break;
        }
    }
}
// Displays the symbol (R or r) of a robot object at given position
void Game::getRobotSymbol(int row, int col) const{
    for(auto robot : robots){
        if(row == robot.getRow() && col == robot.getCol()){
            std::cout << robot.getSymbol();
            break;
        }
    }
}
// Returns true if a robot is at given position is alive, false otherwise
bool Game::isRobotAlive(Position pos) const{
    for(auto robot : robots){
        if(pos.row == robot.getRow() && pos.col == robot.getCol()){
            return robot.isAlive();
        }
    }
    return false;
}
// Returns true if an electrified post is at given position, false otherwise
bool Game::isPostEletrified(Position pos, const Maze& maze) const{
    for(auto post : maze.getPosts()){
        if(pos.row == post.getRow() && pos.col == post.getCol()){
            return post.isElectrified();
        }
    }
    return false;
}
// Displays the current state of the maze
void Game::showGameDisplay() const{
    // For each row of the maze...
    for(int row = 0; row < maze.getnumRows(); row++){
        // ...for each column of the maze
        for(int col = 0; col < maze.getnumCols() ; col++){
            if(isPlayer(row, col)){
                std::cout << player.getSymbol();
            }
            else if(isRobot(row, col)){
                getRobotSymbol(row, col);
            }
            else if(isPost(row,col)){
                getPostSymbol(row, col, maze);
            }
            else if(isExit(row, col)){
                std::cout << 'O';
            }
            else{
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Robots Alive:" << countRobots() << std::endl << std::endl;
}
// Returns true if player movement is valid, false otherwise
bool Game::isValid(char move){

    move = toupper(move); // Make sure either "q" or "Q" is a valid input
    char allowedMove[9] = {'W','A','X','D','Q','E','Z','C','S'}; // All possible moves

    // Checks if input is on allowed list
    for(int i = 0; i < 9; i++){
        if (allowedMove[i] == move){
            return true;
        }
    }
    return false;
}
// Asks for wanted movement and moves the player according to user input
void Game::PlayerMove(){
    while (true){
        std::string move;
        std::cout << "Movement: ";
        std::getline(std::cin, move);

        if (std::cin.eof()){
            std::cout << std::endl << "Thank you for playing..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(EXIT_SUCCESS);
        }

        // Check if input has more than 1 character -> invalid input
        if(move.length() != 1){
            std::cerr << std::endl << "Not a valid player movement. The valid movements are:\nForward, backwards, left or right by pressing W, X, A, D\nDiagonally by pressing Q, E, Z, C\nStay in place by pressing S" << std::endl;
        }
        else{
            // Check if input is allowed by the game
            if (isValid(move[0])){
                // Moves player's coordinates according to user input
                switch(toupper(move[0])){
                    case 'W':
                        player.addRow(-1);
                        break;
                    case 'A':
                        player.addCol(-1);
                        break;
                    case 'X':
                        player.addRow(1);
                        break;
                    case 'D':
                        player.addCol(1);
                        break;
                    case 'Q':
                        player.addRow(-1);
                        player.addCol(-1);
                        break;
                    case 'E':
                        player.addRow(-1);
                        player.addCol(1);
                        break;
                    case 'Z':
                        player.addRow(1);
                        player.addCol(-1);
                        break;
                    case 'C':
                        player.addRow(1);
                        player.addCol(1);
                        break;
                    case 'S':
                        break;
                }

                Position pos{};
                pos.col = player.getCol();
                pos.row = player.getRow();

                // Check for player collision with post, robot or exit
                if(isPost(player.getRow(),player.getCol())){
                    if(isPostEletrified(pos, this->maze)){
                        player.setAsDead();
                        GameEnd = true; // Updates game state
                        undoMovement(move); // Keep the player on the spot he was before dying, but this time dead
                        showGameDisplay();
                        std::cout << "Game Over!";
                        std::cout << std::endl << "Did you really just try to move into an electrified post?" << std::endl;
                        break;
                    }
                    else{
                        std::cerr << std::endl << "You are not allowed to move to a cell occupied by a non-electrified posts." << std::endl << std::endl;
                        undoMovement(move); // Prevent the player from going into a non electrified post
                    }
                }
                else if (isRobot(player.getRow(),player.getCol()) && isRobotAlive(pos)) {
                    player.setAsDead();
                    GameEnd = true; // Updates game state
                    undoMovement(move); // Keep the player on the spot he was before dying, but this time dead
                    showGameDisplay();
                    std::cout << "Game Over!" << std::endl;
                    std::cout << "So you just tried to walk into a Robot, really?" << std::endl;
                    break;
                }
                else if (isRobot(player.getRow(),player.getCol()) && !isRobotAlive(pos)){
                    std::cerr << std::endl << "You are not allowed to move to a cell occupied by a destroyed robot. Do you have a death wish?" << std::endl << std::endl;
                    undoMovement(move); // Prevent the player from going into a stuck/dead robot

                }
                else if(isExit(player.getRow(), player.getCol())){
                    GameEnd = true;
                    showGameDisplay();
                    break;
                }
                else{ 
                    break;
                }

            }
            // Valid input but invalid movement
            else{
                std::cerr << std::endl << "Not a valid player movement. The valid movements are:\nForward, backwards, left or right by pressing W, X, A, D\nDiagonally by pressing Q, E, Z, C\nStay in place by pressing S" << std::endl;
            }
        }
    }
}
// Undos a player movement
void Game::undoMovement(std::string move){
    switch(toupper(move[0])){
        case 'W':
            player.addRow(1);
            break;
        case 'A':
            player.addCol(1);
            break;
        case 'X':
            player.addRow(-1);
            break;
        case 'D':
            player.addCol(-1);
            break;
        case 'Q':
            player.addRow(1);
            player.addCol(1);
            break;
        case 'E':
            player.addRow(1);
            player.addCol(-1);
            break;
        case 'Z':
            player.addRow(-1);
            player.addCol(1);
            break;
        case 'C':
            player.addRow(-1);
            player.addCol(-1);
            break;
        case 'S':
            break;
    }
}
// Returns true if theres a colision between a given robot and another one, exit, player or post, false otherwise
bool Game::checkCollision(Robot &robot1, Maze &maze){
    
    int robotID = robot1.getID();
    // Checks if robot has collided with another one, representing them both by "r" on the same cell
    for (auto &robot2: robots){
        if(robot2.getID() != robotID){
            if((robot2.getCol() == robot1.getCol()) &&(robot2.getRow() == robot1.getRow())){
                robot2.collisionRobot();
                robot1.collisionRobot();
                return true;
            }
        }
    }
    // Prevents robot from going to an exit. We believe it's impossible on a square map with the exits on the borders but you never know
    for(auto exit: exits){
        if(isExit(robot1.getRow(),robot1.getCol())){
            undoRobotMovement(robot1);
        }
    }
    // Checks if robot has collided with a player
    if((robot1.getCol() == player.getCol()) && (robot1.getRow() == player.getRow())){
        undoRobotMovement(robot1); // Puts robot on the spot he was before killing the player
        player.setAsDead(); // Kills the player
        GameEnd = true; // Updates game state
        showGameDisplay();
        std::cout << "Game Over!" << std::endl;
        std::cout << "The Robot (ID:" << robot1.getID() << ") killed you. What a noob!" << std::endl;
        return true;
    }
    // Check if robot has collided a post, electrified or not, and acts accordingly
    for (auto &post: maze.getPosts()){
        if((post.getCol() == robot1.getCol()) &&(post.getRow() == robot1.getRow())){
            if(post.isElectrified()){
                post.changeState();
                robot1.collisionEletrifiedPost();
                undoRobotMovement(robot1);
            }
            else if(!post.isElectrified()){
                robot1.collisionNonEletrifiedPost();
            }
            return true;
        }
    }
    return false;
}
// Moves one specific robot to the nearby contiguous cell thats closest to the player
void Game::moveRobot(Robot &robot1){
    if(robot1.getCol() > player.getCol()){
        robot1.setCol(robot1.getCol() - 1);
    }
    else if(robot1.getCol() < player.getCol()){
        robot1.setCol(robot1.getCol() + 1);
    }

    if(robot1.getRow() > player.getRow()){
        robot1.setRow(robot1.getRow() - 1);
    }
    if(robot1.getRow() < player.getRow()){
        robot1.setRow(robot1.getRow() + 1);
    }
}
// Undos a robot movement
void Game::undoRobotMovement(Robot &robot1) {
    robot1.setPosition(robot1.getLastPosition());
}
// Moves all the robots to the nearby contiguous cell thats closest to the player
void Game::moveRobots(){
    if(!GameEnd){
        for(auto &robot : robots){
            if(robot.isAlive()){
                robot.setLastPos(robot.getRow(),robot.getCol()); // Sets current position to the last position
                moveRobot(robot); // Attempts to move the robot to the new position
                checkCollision(robot, this->maze); // Checks for collision with other objects
            }
        }
    }
}
// Returns the number of robots alive
int Game::countRobots() const{
    int counter = 0;
    for(auto robot : robots){
        if (robot.isAlive()){
            counter+=1;
        }
    }
    return counter;
}
// Checks if player is alive
void Game::checkGameState(){
    if(!player.isAlive()){
        GameEnd = true;
    }
}
// Restarts the robotID counter in case of new game
void Game::restartID() {
    Robot RobotAux;
    RobotAux.restartID();
}
// Implements the game loop; returns true if player wins, false otherwise
bool Game::play(){

    Timer newtimer; // Creates new timer class object
    this->timer = newtimer;
    // While game is not over
    while(!GameEnd){
        showGameDisplay(); // Shows the map
        PlayerMove(); // Moves the player
        moveRobots(); // Moves the robot
        checkGameState(); // Checks if game is over
    }
    timer.stop(); // Stops the timer game timer
    restartID(); // Restarts robot IDs

    // If player won
    if(player.isAlive()){
        std::cout << "You managed to exit the maze. Well Done!!" << std::endl;
        std::cout << "Your game lasted for: " << timer.getTime() << std::endl;
        return true;
    }
    std::cout << "Your game lasted for: " << timer.getTime() << std::endl;
    return false;
}
// Returns player name to add to the leaderboard
std::string Game::getPlayerName(){
    return this->player.getName();
}
// Returns game timer to add to the leaderboard, using the format hh::mm::ss.ms
std::string Game::getTime(){
    return this->timer.getTime();
}
