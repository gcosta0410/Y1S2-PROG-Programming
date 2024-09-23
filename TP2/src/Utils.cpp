//T02_G10
#include <iostream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>
#include <cctype>
#include "./include/Utils.h"
#include "./include/Player.h"
#include "./include/Leaderboard.h"


// Returns true if MAZE_XX.txt file was found, false otherwise
bool foundMaze(int maze, std::string &maze_name){

    // Reset variable in case of valid input but non-existent MAZE_XX.txt file
    maze_name = "./data/MAZE_";

    // Check to see if user input is < 10 to have MAZE_0X.txt format
    if(maze < 10){
        maze_name += "0" + std::to_string(maze) + ".txt";
    }
    else{
        maze_name += std::to_string(maze) + ".txt";
    }

    std::ifstream infile(maze_name); // Search for file
    return infile.good(); // File found/not found
}

// Returns true if all elements in a string as digits, false otherwise
bool isAllDigits(const std::string &str){

    // Iterates each caracter in a string and checks if it's an integer or not
    for(char c: str){
        if (!isdigit(c)){
            return false;
        }
    }
    return true;
}

// Returns true if player name is valid, false otherwise
bool isValidName(const std::string &str){

    // Iterates each caracter in a string and checks if it's a valid char or not (alphanumeric or white space)
    for (const char c : str){
        if (!isspace(c) && !isalnum(c)){
            return false;
        }
    }
    return true;
}

// Returns true if player wants to play the same map again, false otherwise
bool playAgain(){

    std::string option;

    // Ask if player wants to play again
    while(true){

        std::cout << "Do you want to play again?" << std::endl;
        std::cout << "1. Yes" << std::endl;
        std::cout << "2. No" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);
        std::cout << std::endl;

        if (std::cin.eof()){
            std::cout << "Thank you for playing..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(EXIT_SUCCESS);
        }

        if(option == "1"){
            return true;
        } 
        else if(option == "2"){
            return false;
        }
        else{
            std::cerr << "Not a valid input!" << std::endl << std::endl;
        }
    }
}
