T02_G10

GROUP MEMBERS:
- Gustavo Gomes Moura Almeida da Costa, up202004187
- Ricardo Almeida Cavalheiro, up202005103

PROGRAM DEVELOPMENT STATE:
    Base goals accomplised:
-All objectives were accomplished.

    Changed original aspects:
-The layout of the MAZE_XX_WINNERS.txt file was changed to have the time of completion first and then the player name, up to a maximum of 10 entries. 
This helped us sort the leaderboard way easier than if we had gone with the suggested layout.
-We used the exit() function, which we were told was a system call and had to check for compatibility issues, worked fine on windows and linux.

    Extra stuff added:   
-A second level of difficulty was added to the game: Hard. Normal mode works as requested. Hard mode will move all the robots at the same time so they will never crash into eachother before moving.
-Added a "Play Again" feature at the end of each map so the user doesn't have to go through all the menus again.

    Observations:
-The game.exe file can't run on windows systems without a C++ compiler installed, we assumed this was normal.
-To run the game on linux it has to be compiled there first since .exe is not a compatible windows-linux file.
-We tested the program on smaller and bigger mazes, works as expected.

    Ideas not implemented (because we were told not to or just remembered them too late):
-Initially we had a directory system were we'd have everything sorted by mazes but gave that up when told it isn't ideal for project evaluation.
-Make a seperate leaderboard for Normal and Hard mode for each level, all within the same MAZE_XX_WINNERS.txt file.
-We had a python script to create maze templates. We thought about implementing it in C++ but we just gave that up as it wasn't needed. 

MAIN DIFFICULTIES:
-File reading and writting, speacially for the leaderboard updating. That one gave us an headache.
-Figuring how to use <chrono> to setup a timer was also troublesome.
-Often finding ourselves not totally understanding what the other did on certain parts of the code. 
We believe that whoever tackled a certain aspect of the program first would then have an easier time doing what was related to that aspect afterwards.
-Not being able to use the latest and greatest C++ features, like format(), because it may not be compatible with some systems.
-Figuring out how to verify user input using std::cin. 
We later switched to getline() because it would allow us to validate user input and not have to constantly clear the input buffer which used to cause halting problems.
