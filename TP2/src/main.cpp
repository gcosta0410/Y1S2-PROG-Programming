//T02_G10
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include "./include/Robot.h"
#include "./include/Game.h"
#include "./include/Maze.h"
#include "./include/Player.h"
#include "./include/Position.h"
#include "./include/Post.h"
#include "./include/Exit.h"
#include "./include/Timer.h"
#include "./include/Leaderboard.h"
#include "./include/Utils.h"

// Initializing functions to be able to call them anywhere
int menu();
void rules();
void play();
void winners();

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

            // Winners menu
            case 3:
                winners();
                break;

            // Exit menu
            case 0:
                std::cout << "Come back any time soon!"<< std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1)); // Waits for 1 seconds before closing the window
                exit(EXIT_SUCCESS); // Closes the terminal window
            
        }
    }
    return EXIT_SUCCESS;
}

// Function to get user input for menu
int menu(){

    std::string option;
    // Ask for a valid input
    while (true){

        std::cout << "---------------------------" << std::endl;
        std::cout << "|       Robots Game       |" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "1. Rules" << std::endl;
        std::cout << "2. Play" << std::endl;
        std::cout << "3. Winners" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);

        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()){
            std::cout << std::endl << "Thank you for playing..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(EXIT_SUCCESS);
        }

        // Check to see if user input is valid - 0, 1, 2 or 3
        if (isAllDigits(option)){
            if (std::stoi(option) == 0 || std::stoi(option) == 1 || std::stoi(option) == 2 || std::stoi(option) == 3){
                return (std::stoi(option));
            }
            else{
                std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
            }
        }
        else{
            std::cerr << std::endl << "Not a valid input!" << std::endl << std::endl;
        }
    }
}

// Function to retrieve and display the rules to the player
void rules(){

    // Create a text string, which is used to output the text file
    std::string line, next;

    // Read from the Rules.txt text file
    std::ifstream rules("./data/rules.txt");

    // Read the file, line by line
    while(std::getline(rules, line)){

        // Output the text from the file, line by line
        std::cout << line << std::endl;
    }

    // Keep the rules menu alive until user says otherwise
    while(true){

        std::cout << std::endl << "Enter 0 to go back: ";
        std::getline(std::cin, next);

        if (std::cin.eof()){
            std::cout << std::endl << "Thank you for playing..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(EXIT_SUCCESS);
        }

        // Check to see if user input is valid 0
        if (isAllDigits(next)){
            if (std::stoi(next) == 0){
                break;
            }
            else{
                std::cerr << std::endl << "Not a valid input!" << std::endl;
            }
        }
        else{
            std::cerr << std::endl << "Not a valid input!" << std::endl;
        }
    }

    // Close the file
    rules.close();
    std::cout << std::endl;
}

// Function to display the leaderboard of a certain maze
void winners(){

    std::string maze;

    // Always running, asking for the maze which player wants to see the leaderboard, until it is found
    while(true){

        std::cout << "Enter the number of the maze you'd like to see the leaderboard of (1-99) or 0 to go back: ";
        std::getline(std::cin, maze);

        if (std::cin.eof()){
            std::cout << std::endl << "Thank you for playing..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(EXIT_SUCCESS);
        }

        // If user input for maze is a number
        if (isAllDigits(maze)){
            // If user input is not 0
            if (std::stoi(maze) != 0){
                // If user input is between 1-99
                if (std::stoi(maze) > 0 && std::stoi(maze) < 100){
                    Leaderboard winners(stoi(maze)); // Creates object of Leaderboard class using one of the two constructors
                    winners.display();
                }
                else{
                    std::cerr << std::endl << "Enter a valid input!(1-99)" << std::endl;
                }
            }
            else{
                std::cout << std::endl;
                break;
            }
        }
        else{
            std::cerr << std::endl << "Enter a valid input!(i.e. 01)" << std::endl;
        }
    }
}

// Function to play the game, second most inportant funcion because links all the functions and the majority of the classes needed for the game itself to work
void play(){

    bool proceed = true;
    std::string maze, maze_name = "./data/MAZE_";

    // Always running, asking for the maze user wants to play until it is found
    while(true){

        std::cout << std::endl << "Enter the number of the maze you'd like to play (1-99) or 0 to go back: ";
        std::getline(std::cin, maze);

        if (std::cin.eof()){
            std::cout << std::endl << "Thank you for playing..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(EXIT_SUCCESS);
        }

        // If user input for maze is a number
        if (isAllDigits(maze)){
            // If user input is not 0
            if (std::stoi(maze) != 0){
                // If user input is between 1-99
                if (std::stoi(maze) > 0 && std::stoi(maze) < 100){
                    // If maze player asked for exists, loads it
                    if (foundMaze(std::stoi(maze), maze_name)){
                        break;
                    }
                    else {
                        std::cerr << std::endl << "Maze not found. Please choose a different one!" << std::endl;
                    }
                }
                else{
                    std::cerr << std::endl << "Enter a valid input!(1-99)" << std::endl;
                }
            }
            else{
                proceed = false; // Updates proceed status so program doesn't try loading any maze
                std::cout << std::endl;
                break;
            }
        }
        else{
            std::cerr << std::endl << "Enter a valid input!(i.e. 01)" << std::endl;
        }
    }
    // If everything user did went according to plan
    while(proceed){

        std::cout << "Loading maze..." << std::endl << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Makes the user wait 0.5 seconds to simulate the game experience of having to load an actual map
        
        Game game(maze_name); // Creates an object of the Game class
        bool player_won = game.play(); // Plays the game and at the end this variable will have the boolean value associated with the player's victory
        Leaderboard winners(maze_name); // Creates an object of the Leaderboard class, this time using the other constructor
        // If the player won...
        if(player_won){
            // ...checks if leaderboard for the played maze exists, if not creates it and...
            if (!winners.exists()){
                winners.create();
            }
            winners.update(game.getPlayerName(), game.getTime()); // ...updates said leaderboard with the player's name and the time it took them to do so
        }
        winners.display(); // Displays the leaderboard on screen, whether the player won or not
        
        // If player wants to play again
        if(!playAgain()){
            break;
        }
    }
}
