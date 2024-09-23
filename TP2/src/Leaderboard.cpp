//T02_G10
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "./include/Leaderboard.h"  

// Default Leaderboard class constructor, not used
Leaderboard::Leaderboard(){}
// Leaderboard class constructor using the number of the maze
Leaderboard::Leaderboard(int maze){

    // Check to see if user input is < 10, to have MAZE_0X.txt format
    if(maze < 10){
        this->maze_name = "./data/MAZE0" + std::to_string(maze);
        this->filename += "0" + std::to_string(maze) + "_WINNERS.txt";
    }
    else{
        this->maze_name = "./data/MAZE" + std::to_string(maze);
        this->filename += std::to_string(maze) + "_WINNERS.txt";
    }
}
// Leaderboard class constructor using the name of the maze file
Leaderboard::Leaderboard(const std::string& maze_name){
    this->maze_name += maze_name.substr(12,2);
	this->filename = "./data/" + maze_name.substr(7,7) +"_WINNERS.txt";
}
// Returns true if the MAZE_XX_WINNERS.txt file already exists, false otherwise
bool Leaderboard::exists(){

    std::ifstream infile(this->filename); // Search for file
    return infile.good(); // File found/not found
}
// Creates the MAZE_XX_WINNERS.txt file with the appropriate leaderboard header
void Leaderboard::create(){
    // Attempt to create the file
    std::cout << "Creating leaderboard..." << std::endl;
    std::ofstream leaderboard(this->filename);

    // Check if file was created
    if(!leaderboard){
        std::cerr << "File could not be created" << std::endl;
    }
    else{
        // Format the file to have a table like shape
        leaderboard << "------------"<< this->maze_name << "------------" << std::endl;
        leaderboard << "|    TIME    -     PLAYER    |" << std::endl;
        leaderboard << "------------------------------" << std::endl;

        leaderboard.close();
    }
}
// Updates the contents of the MAZE_XX_WINNERS.txt file
void Leaderboard::update(const std::string &player_name, const std::string &formated_time){
    
    std::string line;
    std::vector<std::string> lb_entries;
    int n_line = 0;

    std::cout << filename << std::endl;

    // Open MAZE_XX_WINNERS.txt file in write only mode
    std::ofstream leaderboard_write(filename, std::ios::app);

    // Append to the end of the file
    std::cout << "Updating leaderboard..." << std::endl;
    leaderboard_write << formated_time << " - " << player_name;
    leaderboard_write.close();

    // Open MAZE_XX_WINNERS.txt file in read only mode
    std::ifstream leaderboard_read(filename);

    // Store all leaderboard entries in a std::vector
    while(!leaderboard_read.eof()){

        std::getline(leaderboard_read, line);
        lb_entries.push_back(line);
        n_line++;
    }
    leaderboard_read.close();

    // Sort the leaderboard entries first by time, then by name
    std::sort(lb_entries.begin()+3, lb_entries.end());

    // Check if leaderboard has more than 10 entries to delete those past the limit
    if(lb_entries.size() > 13){

        // Truncates the std::vector from the 10th leaderboard entry forward
        lb_entries.erase(lb_entries.begin()+13, lb_entries.end());
    }

    // Reopens the file and will overwrite any pre-existent leaderboard
    std::ofstream leaderboard_updated(filename, std::ios::trunc);

    // Updates leaderboard
    for(std::string entry : lb_entries){
        leaderboard_updated << entry << std::endl;
    }

    leaderboard_updated.close();
}
// Displays the contents of the MAZE_XX_WINENRS.txt file
void Leaderboard::display(){

    if(this->exists()){
        std::string line;
        std::ifstream leaderboard(filename);

        std::cout << std::endl;
        // Prints out the leaderboard line by line
        while(!leaderboard.eof()){
            std::getline(leaderboard, line);
            std::cout << line << std::endl;
        }
    }
    else{
        std::cout << "There's no leaderboard for this map yet, be the first on it!" << std::endl << std::endl;
    }
}
