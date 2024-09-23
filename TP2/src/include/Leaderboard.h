//T02_G10
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>

class Leaderboard{
	public:
		Leaderboard(); // Default Leaderboard class constructor, not used
		Leaderboard(int maze); // Leaderboard class constructor using the number of the maze
		Leaderboard(const std::string& maze_name); // Leaderboard class constructor using the name of the maze file
		bool exists(); // Returns true if the MAZE_XX_WINNERS.txt file already exists, false otherwise
		void create(); // Creates the MAZE_XX_WINNERS.txt file with the appropriate leaderboard header
		void update(const std::string &player_name, const std::string &formated_time); // Updates the contents of the MAZE_XX_WINNERS.txt file
		void display(); // Displays the contents of the MAZE_XX_WINENRS.txt file

	private:
		std::string maze_name = "MAZE"; //Will have the format MAZEXX
		std::string filename = "./data/MAZE_";
};
#endif //LEADERBOARD_H
