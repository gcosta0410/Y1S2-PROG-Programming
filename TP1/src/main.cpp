//T02_G10
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <filesystem>

// To avoid using std:: (bad practice but won't affect such a small project)
using namespace std;

// Initializing functions to be able to call them anywhere
int menu();
void rules();
void play();
bool foundMaze(int maze, string &maze_name);
void findDimensions(string str, size_t &numLine, size_t &numCol);
vector< vector<char> > creatingMaze(string maze_name);
bool isAllDigits(const string &str);
void showMaze(vector< vector<char> > maze);
void playerMove(int &x, int &y, bool &GameEnd, bool &died, vector< vector<char> > &maze);
void findPlayer(int &x, int &y, vector< vector<char> > &maze);
bool allowedMove(char &move);
string formatTime(long long ms);
void makeLeaderboard(string maze_name, string formated_time);
void findRobots(vector<int> &robotsPos, vector< vector<char> > &maze, int &RobotsAlive);
bool isValidName(const string &str);
vector<int> findBestMove(int x, int y, int xRobot, int yRobot);
void moveRobotsNormal(int x, int y, vector< int > &robotsPos, vector< vector<char> > &maze, bool &GameEnd, bool &died , int &RobotsAlive);
void moveRobotsHard(int x, int y, vector< int > &robotsPos, vector< vector<char> > &maze, bool &GameEnd, bool &died , int &RobotsAlive);
void printLeaderboard(string maze_name);
void undoMovement(string move, int& x, int& y);

// Main() function, self explanatory, most important function
int main(){

    while(true){
        // Chooses between the menu tabs
        switch(menu()){

            // Rules menu
            case 1:
                rules();
                break;

                // Play menu
            case 2:
                play();
                break;

                // Exit menu
            case 0:
                cout << "Come back any time soon!"<< endl;
                this_thread::sleep_for(chrono::seconds(1)); // Waits for 2 seconds before closing the window
                exit(EXIT_SUCCESS); // Closes the terminal window
        }
    }
    return EXIT_SUCCESS;
}

// Function to get user input for menu
int menu(){

    string option;

    // Ask for a valid input
    while (true){

        cout << "---------------------------" << endl;
        cout << "|       Robots Game       |" << endl;
        cout << "---------------------------" << endl;
        cout << "1. Rules" << endl;
        cout << "2. Play" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose an option from the above: ";

        getline(cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (cin.eof()){
            cout << endl << "Thank you for playing..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            exit(EXIT_SUCCESS);
        }

        // Check to see if user input is valid - 0, 1 or 2
        if (isAllDigits(option)){
            if (stoi(option) == 0 || stoi(option) == 1 || stoi(option) == 2){
                break;
            }
            else{
                cerr << endl << "Not a valid input!" << endl << endl;
            }
        }
        else{
            cerr << endl << "Not a valid input!" << endl << endl;
        }
    }
    return (stoi(option));
}

// Function to retrieve and display the rules to the player
void rules(){

    // Create a text string, which is used to output the text file
    string line, next;

    // Read from the Rules.txt text file
    ifstream rules("./data/rules.txt");

    // Read the file, line by line
    while (getline(rules, line)){

        // Output the text from the file, line by line
        cout << line << endl;
    }

    // Keep the rules menu alive until user says otherwise
    while(true){

        cout << endl << "Enter 0 to go back: ";
        getline(cin, next);

        if (cin.eof()){
            cout << endl << "Thank you for playing..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            exit(EXIT_SUCCESS);
        }

        // Check to see if user input is valid 0
        if (isAllDigits(next)){
            if (stoi(next) == 0){
                break;
            }
            else{
                cerr << endl << "Not a valid input!" << endl;
            }
        }
        else{
            cerr << endl << "Not a valid input!" << endl;
        }
    }

    // Close the file
    rules.close();
    cout << endl;
}

// Function to search for the maze in the games directories
bool foundMaze(int maze, string &maze_name){

    // Reset variable in case of valid input but non-existent MAZE_XX.txt file
    maze_name = "./data/MAZE_";

    // Check to see if user input is < 10 to have MAZE_0X.txt format
    if(maze < 10){
        maze_name += "0" + to_string(maze) + ".txt";
    }
    else{
        maze_name += to_string(maze) + ".txt";
    }

    ifstream infile(maze_name); // Search for file
    return infile.good(); // File found/not found
}

// Function to get maze size from first line of MAZE_XX.txt
void findDimensions(string str, size_t &numLine, size_t &numCol){

    stringstream ss;
    vector<int> dimension;

    // Storing the whole string into a string stream
    ss << str;
    string temp;
    int found;

    // Runs until end of file
    while (!ss.eof()){

        // Extracting word by word from stream
        ss >> temp;

        // Checking the given word is integer or not
        if (stringstream(temp) >> found){
            dimension.push_back((int)found);
        }

        // To save from space at the end of string
        temp = "";
    }
    // Storing maze size in two variables for later use
    numLine = dimension[0]; numCol = dimension[1];
}

// Function to create a 2D vector to store the maze info
vector< vector<char> > creatingMaze(string maze_name){

    string line, dimension;
    size_t numCol, numLine;
    vector< vector<char> > maze;
    ifstream maze_txt(maze_name); // Read from MAZE_XX.txt file

    getline(maze_txt, dimension);
    findDimensions(dimension, numLine, numCol);

    cout << "Size: " << numLine << "x" << numCol << endl; // Display the size of the maze on screen

    // Iterates through the lines of the MAZE_XX.txt file and stores all the elements in it in a 2D vector
    while(getline(maze_txt, line)){

        vector<char> maze_line;

        // Iterates through the columns of the maze
        for (int idx = 0; idx < numCol; idx++){
            maze_line.push_back(line[idx]);
        }

        maze.push_back(maze_line);
    }
    maze_txt.close();
    return maze;
}

// Function to verify if a given string is only comprised of digits
bool isAllDigits(const string &str){

    // Iterates each caracter in a string and checks if it's an integer or not
    for(char c: str){
        if (!isdigit(c)){
            return false;
        }
    }
    return true;
}

// Function to display the maze on screen
void showMaze(vector< vector<char> > maze){

    int numCols, numLines;
    numLines = maze.size();
    numCols = maze[0].size();

    // Iterates through the 2D vector that stores the maze and displays it, element by element
    for(int i = 0; i<numLines; i++){
        for(int j = 0; j < numCols; j++){
            cout << maze[i][j];
        }
        cout << endl;
    }
}

// Function to undo player movement in case they try to go onto a dead robots body
void undoMovement(string move, int& x, int& y){
    switch(move[0]){
        case 'W':
            y += 1;
            break;
        case 'A':
            x += 1;
            break;
        case 'X':
            y += -1;
            break;
        case 'D':
            x += -1;
            break;
        case 'Q':
            x += 1;
            y += 1;
            break;
        case 'E':
            x += -1;
            y += 1;
            break;
        case 'Z':
            x += 1;
            y += -1;
            break;
        case 'C':
            x += -1;
            y += -1;
            break;
        case 'S':
            break;
    }
}

// Function to move the player when user says so
void playerMove(int &x, int &y, bool &GameEnd, bool &died, vector< vector<char> > &maze){

    string move;

    // Ask user for player movement
    while (true){

        cout << "Movement: ";
        getline(cin, move);

        if (cin.eof()){
            cout << endl << "Thank you for playing..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            exit(EXIT_SUCCESS);
        }

        // Check if input has more than 1 character -> invalid input
        if(move.length() != 1){
            cerr << endl << "Not a valid player movement. The valid movements are:\nForward, backwards, left or right by pressing W, X, A, D\nDiagonally by pressing Q, E, Z, C\nStay in place by pressing S" << endl;
        }
        else{

            // Check if input is allowed by the game
            if (allowedMove(move[0])){

                maze[y][x] = ' '; // Removes the player from his spot

                // Moves player's coordinates according to user input
                switch(move[0]){
                    case 'W':
                        y += -1;
                        break;
                    case 'A':
                        x += -1;
                        break;
                    case 'X':
                        y += 1;
                        break;
                    case 'D':
                        x += 1;
                        break;
                    case 'Q':
                        x += -1;
                        y += -1;
                        break;
                    case 'E':
                        x += 1;
                        y += -1;
                        break;
                    case 'Z':
                        x += -1;
                        y += 1;
                        break;
                    case 'C':
                        x += 1;
                        y += 1;
                        break;
                    case 'S':
                        break;
                }

                // Check for collision with eletric fence or enemy robot
                if((maze[y][x] == '*') || (maze[y][x] == 'R')){
                    maze[y][x] = 'h'; // Displays dead player on screen
                    GameEnd = true; // Updates game state
                    died = true; // Updates player state
                    break;
                }
                else if (maze[y][x] == 'r'){
                    cerr << endl << "You are not allowed to move to a cell occupied by a destroyed robot. Do you really want to die?" << endl << endl;
                    undoMovement(move, x, y);
                }
                else{
                    maze[y][x] = 'H'; // Moves player to new spot
                    break;
                }

            }
            // Valid input but invalid movement
            else{
                cerr << endl << "Not a valid player movement. The valid movements are:\nForward, backwards, left or right by pressing W, X, A, D\nDiagonally by pressing Q, E, Z, C\nStay in place by pressing S" << endl;
            }
        }
    }
}

// Function to verify move is legal
bool allowedMove(char &move){

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

// Function to find the player inside the maze
void findPlayer(int &x, int &y, vector< vector<char> > &maze){

    int numCols, numLines;
    numLines = maze.size();
    numCols = maze[0].size();

    // Iterates through entire maze until player's found
    for (int i = 0; i<numLines; i++){
        for (int j = 0; j < numCols; j++){
            if (maze[i][j] == 'H'){
                x = j; y = i; // Saves player's position
            }
        }
    }
}

// Function to format time from ms to hh:mm:ss.ms
string formatTime(long long ms){

    // Convert milliseconds to hours - 3 600 000 milliseconds in an hour
    long long hr = ms / 3600000;
    ms = ms - 3600000 * hr;

    // 60 000 milliseconds in a minute
    long long min = ms / 60000;
    ms = ms - 60000 * min;

    // 1 000 milliseconds in a second
    long long sec = ms / 1000;
    ms = ms - 1000 * sec;


    string formated_time = "";
    vector<long long> time = {hr, min, sec, ms};

    // For element with index i in time vector, format time string to have 0s if number is <10
    for(int i = 0; i < time.size(); i++){

        // To solve a bug where sometimes the ms part of the timer would show up as "39" instead of "390"
        if(i == 3 && to_string(time[i]).length() < 3){
            if(time[i] < 10){
                formated_time += "0" + to_string(time[i]) + "0";
            }
            else{
                formated_time += to_string(time[i]) + "0";
            }
        }
        else{
            if(time[i] < 10){
                formated_time += "0" + to_string(time[i]);
            }
            else{
                formated_time += to_string(time[i]);
            }
            if(i == 0 || i == 1){
                formated_time += ":";
            }
            else if(i == 2){
                formated_time += ".";
            }
        }
    }
   return formated_time;
}

// Function to check if MAZE_XX_WINNERS.txt exists, if not creates it
void makeLeaderboard(string maze_name, string formated_time){

    string winner_name, dir = "./data/", filename = dir + maze_name.substr(8,7) +"_WINNERS.txt";

    while(true){

        // Check if the folder exists
        if (!filesystem::exists(dir)) {            
            // Create the folder
            if (!filesystem::create_directory(dir)) {
                std::cerr << "Failed to create directory: " << dir << std::endl;
            }
        }

        // If MAZE_XX_WINNERS.txt file exists
        if(ifstream(filename)){

            // Ask for player name
            cout << "Type your name (max 15 characters): ";
            getline(cin, winner_name);

            if (cin.eof()){
                cout << endl << "Thank you for playing..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                exit(EXIT_SUCCESS);
            }

            // If name is valid
            if(isValidName(winner_name) && winner_name.length() <= 15){

                string line;
                vector<string> lb_entries;
                int n_line = 0;

                // Open MAZE_XX_WINNERS.txt file in write only mode
                ofstream leaderboard_write(filename, ios::app);

                // Append to the end of the file
                cout << "Updating leaderboard..." << endl;
                leaderboard_write << formated_time << " - " << winner_name;
                leaderboard_write.close();

                // Open MAZE_XX_WINNERS.txt file in read only mode
                ifstream leaderboard_read(filename);

                // Store all leaderboard entries in a vector
                while(!leaderboard_read.eof()){

                    getline(leaderboard_read, line);
                    lb_entries.push_back(line);
                    n_line++;
                }
                leaderboard_read.close();

                // Sort the leaderboard entries first by time, then by name
                sort(lb_entries.begin()+3, lb_entries.end());

                // Check if leaderboard has more than 10 entries to delete those past the limit
                if(lb_entries.size() > 13){

                    // Truncates the vector from the 10th leaderboard entry forward
                    lb_entries.erase(lb_entries.begin()+13, lb_entries.end());
                }

                // Reopens the file and will overwrite any pre-existent leaderboard
                ofstream leaderboard_updated(filename, ios::trunc);

                // Updates leaderboard
                for(string entry : lb_entries){
                    leaderboard_updated << entry << endl;
                }

                leaderboard_updated.close();
                break;
            }
            // If name not valid
            else if(isValidName(winner_name) && winner_name.length() > 15){
                cerr << endl << "Name has more than 15 characters! Please retry." << endl << endl;
            }
            else{
                cerr << endl << "Not a valid name input!" << endl << endl;
            }
        }
        // If file doesn't exist
        else{

            // Attempt to create the file
            cout << "Creating leaderboard..." << endl;
            ofstream leaderboard(filename);

            // Check if file was created
            if(!leaderboard){
                cerr << "File could not be created" << endl;
            }
            else{
                // Format the file to have a table like shape
                leaderboard << "------------------------------" << endl;
                leaderboard << "|    TIME    -     PLAYER    |" << endl;
                leaderboard << "------------------------------" << endl;

                leaderboard.close();
            }
        }
    }
}

// Function to verify if a given string is only comprised of chars
bool isValidName(const string &str){

    // Iterates each caracter in a string and checks if it's a valid char or not (alphanumeric or white space)
    for (const char c : str){
        if (!isspace(c) && !isalnum(c)){
            return false;
        }
    }
    return true;
}

// Function to find all robots and store their positions
void findRobots(vector<int> &robotsPos, vector< vector<char> > &maze, int &RobotsAlive ){

    int numCols, numLines;
    numLines = maze.size();
    numCols = maze[0].size();

    // Iterates through the maze, locates robots and stores them in a robot position vector
    for (int i = 0; i<numLines; i++){
        for (int j = 0; j < numCols; j++){
            if (maze[i][j] == 'R'){
                robotsPos.push_back(j);
                robotsPos.push_back(i);
                RobotsAlive+= 1;
            }
        }
    }
}

// Function to find best robot moves, based on player position
vector<int> findBestMove(int x, int y, int xRobot, int yRobot){

    int best_x, best_y;
    vector<int> best_move;

    if(xRobot > x){
        best_x = xRobot-1;
    }
    else if(xRobot < x){
        best_x = xRobot+1;
    }
    else{
        best_x = xRobot;
    }

    if(yRobot > y){
        best_y = yRobot-1;
    }
    else if(yRobot < y){
        best_y = yRobot+1;
    }
    else{
        best_y = yRobot;
    }

    best_move.push_back(best_x);
    best_move.push_back(best_y);
    return best_move;
}

// Function to count the robots left alive for game management
void countRobots(vector< vector<char> > maze, int& RobotsAlive){

    RobotsAlive = 0;

    for(int i = 0; i<maze.size(); i++){
        for(int j = 0; j < maze[0].size(); j++){
            if((maze[i][j]) == 'R'){
                RobotsAlive+=1;
            }
        }
    }
}

// Function to move all the robots according to Normal mode rules, one by one
void moveRobotsNormal(int x, int y, vector< int > &robotsPos, vector< vector<char> > &maze, bool &GameEnd, bool &died, int &RobotsAlive){

    int xRobot, yRobot;
    vector<int> best_move;

    // Traverses the vector with all the robot positions and calculates the best move for each robot, based on the players position, updating it's position
    for (int i = 0; i < robotsPos.size(); i+=2){

        xRobot = robotsPos[i]; yRobot = robotsPos[i+1];

        if (maze[yRobot][xRobot] == 'R'){

            best_move = findBestMove(x, y, xRobot, yRobot);

            if(maze[best_move[1]][best_move[0]] == '*'){

                maze[yRobot][xRobot] = ' ';
                maze[best_move[1]][best_move[0]] = 'r';
                robotsPos[i] = best_move[0]; robotsPos[i+1] = best_move[1];
            }
            else if(maze[best_move[1]][best_move[0]] == 'R'){

                maze[yRobot][xRobot] = ' ';
                maze[best_move[1]][best_move[0]] = 'r';
                robotsPos[i] = best_move[0]; robotsPos[i+1] = best_move[1];
            }
            else if(maze[best_move[1]][best_move[0]] == 'H'){

                maze[yRobot][xRobot] = ' ';
                maze[best_move[1]][best_move[0]] = 'h';
                robotsPos[i] = best_move[0]; robotsPos[i+1] = best_move[1];
                GameEnd = true;
                died = true;
            }
            else if(maze[best_move[1]][best_move[0]] == ' '){

                maze[yRobot][xRobot] = ' ';
                maze[best_move[1]][best_move[0]] = 'R';
                robotsPos[i] = best_move[0]; robotsPos[i+1] = best_move[1];
            }
            else if(maze[best_move[1]][best_move[0]] == 'r'){

                maze[yRobot][xRobot] = ' ';
                maze[best_move[1]][best_move[0]] = 'r';
                robotsPos[i] = best_move[0]; robotsPos[i+1] = best_move[1];

            }
        }
    }
    countRobots(maze, RobotsAlive);

    if(RobotsAlive == 0){
        GameEnd = true;
    }
}

// Function to move the robots according to Hard mode rules
void moveRobotsHard(int x, int y, vector< int > &robotsPos, vector< vector<char> > &maze, bool &GameEnd, bool &died , int &RobotsAlive){

    int xRobot, yRobot;
    vector<int> best_move;

    // Calculates the best move for each robot and stores it in a vector
    for (int i = 0; i < robotsPos.size(); i+=2){

        xRobot = robotsPos[i]; yRobot = robotsPos[i+1];

        if (maze[yRobot][xRobot] == 'R'){

            best_move = findBestMove(x, y, xRobot, yRobot);
            maze[yRobot][xRobot] = ' ';
            robotsPos[i] = best_move[0]; robotsPos[i+1] = best_move[1];}
    }

    // Updating robots position in maze
    for (int i = 0; i < robotsPos.size();i+=2){
        if(maze[robotsPos[i+1]][robotsPos[i]] == '*'){
            maze[robotsPos[i+1]][robotsPos[i]] = 'r';
        }

        else if(maze[robotsPos[i+1]][robotsPos[i]] == 'R'){
            maze[robotsPos[i+1]][robotsPos[i]] = 'r';
        }


        else if(maze[robotsPos[i+1]][robotsPos[i]]== 'H'){
            maze[robotsPos[i+1]][robotsPos[i]] = 'h';
            GameEnd = true;
            died = true;
        }

        else if(maze[robotsPos[i+1]][robotsPos[i]] == ' '){
            maze[robotsPos[i+1]][robotsPos[i]] = 'R';

        }
        else if(maze[robotsPos[i+1]][robotsPos[i]] == 'r'){
            maze[robotsPos[i+1]][robotsPos[i]] = 'r';
        }
    }
    countRobots(maze, RobotsAlive);

    if(RobotsAlive == 0){
        GameEnd = true;
    }
}

// Function to print the leaderboard at the end of each game
void printLeaderboard(string maze_name){

    string line, filename = maze_name.substr(0,7) +"_WINNERS.txt";

    if(!ifstream(filename)){
        cerr << "There's no leaderboard for the current level yet. Be the first one on it!" << endl;
    }
    else{
        ifstream leaderboard(filename);

        cout << endl;
        while(!leaderboard.eof()){
            getline(leaderboard, line);
            cout << line << endl;
        }
    }
}

// Function to play the game, second most inportant funcion because links all the functions needed for the game itself to work
void play(){
    string option;
    int x, y, RobotsAlive = 0;
    bool GameEnd = false, died = false, proceed = true;
    string difficulty, maze, maze_name = "./data/MAZE_";
    vector< vector<char> > maze_map;
    vector< int > robotsPos;

    // Always running, asking for maze player wants to play until it is found
    while(true){

        cout << endl << "Enter the number of the maze you'd like to play (1-99) or 0 to go back: ";
        getline(cin, maze);

        if (cin.eof()){
            cout << endl << "Thank you for playing..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            exit(EXIT_SUCCESS);
        }

        // If user input for maze is a number
        if (isAllDigits(maze)){
            // If user input is not 0
            if (stoi(maze) != 0){
                // If maze player asked for exists, loads it
                if (foundMaze(stoi(maze), maze_name)){
                    break;
                }
                else {
                    cerr << endl << "Maze not found. Please choose a different one!" << endl;
                }
            }
            else{
                proceed = false; // Updates proceed status so program doesn't try loading any maze
                cout << endl;
                break;
            }
        }
        else{
            cerr << endl << "Enter a valid input!(i.e. 01)" << endl;
        }
    }

    // If everything user did went according to plan
    if (proceed){

        // Ask user for difficulty mode wanted
        while(true){
            cout << endl;
            cout << "-------------------------" << endl;
            cout << "|   Select  Difficulty  |" << endl;
            cout << "-------------------------" << endl;
            cout << "1. Normal" << endl;
            cout << "2. Hard" << endl;
            cout << "Choose an option from the above: ";

            getline(cin, difficulty);

            if (cin.eof()){
                cout << endl << "Thank you for playing..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                exit(EXIT_SUCCESS);
            }

            if(difficulty == "1" ){
                difficulty = "Normal";
                break;
            }
            else if(difficulty == "2"){
                difficulty = "Hard";
                break;
            }
            else{
                cerr << "Not a valid input!" << endl;
            }
        }

        cout << endl <<"You selected " << difficulty << " difficulty."<< endl;
        cout << "Loading maze..." << endl << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); // Makes the user wait 0.5 seconds to simulate the game experience of having to load an actual map
        while(true){
        // Loads maze onto screen
        maze_map = creatingMaze(maze_name);
        findPlayer(x,y,maze_map);
        findRobots(robotsPos,maze_map, RobotsAlive);

        // Initialize game timer using <chrono>
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        // While game is running (player alive and enemy robots left) update map
        while (!GameEnd){

                showMaze(maze_map);
                cout << "Robots alive: " << RobotsAlive << endl;
                cout << endl;
                playerMove(x, y, GameEnd, died, maze_map);

                // Move robots according to difficulty chosen
                if (difficulty == "Normal"){
                    moveRobotsNormal(x, y, robotsPos, maze_map, GameEnd, died, RobotsAlive);
                }
                else if (difficulty == "Hard"){
                    moveRobotsHard(x, y, robotsPos, maze_map, GameEnd, died, RobotsAlive);
                }
            }

            // Terminate game timer and calculate time elapsed
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            chrono::steady_clock::duration time_elapsed = end - start;
            long long elapsed_time = chrono::duration_cast<chrono::milliseconds>(time_elapsed).count();
            string formated_time = formatTime(elapsed_time);

            // Show last map state before game ended
            showMaze(maze_map);
            cout << "Robots alive: " << RobotsAlive << endl;

            // Boo/congratulate player for his performance on the game and print the game time
            cout << endl << "Game Over! " << endl << (died ? "You died by hitting a fence/robot. What a noob!" : "Winner winner, chicken dinner!") << endl;
            cout << "Your game lasted for: " << formated_time;
            cout << endl;

            // Go to leaderboard input if player won
            if(!died){

                // Check if leaderboard for played level already exists, if not, create it
                makeLeaderboard(maze_name, formated_time);
            }

            printLeaderboard(maze_name); // Self explanatory function name
            
            // Ask if player wants to play again
            while(true){

                cout << "Do you want to play again?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "Choose an option from the above: ";

                getline(cin, option);
                cout << endl;

                if (cin.eof()){
                    cout << "Thank you for playing..." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    exit(EXIT_SUCCESS);
                }

                if(option == "1" || option == "2"){
                    break;
                }
                else{
                    cerr << "Not a valid input!" << endl << endl;
                }
            }

            // If yes, play again, if not, go to menu
            if(option == "1"){
                GameEnd = false;
                died = false;
            }
            else{
                break;
            }
        }
    }
}
