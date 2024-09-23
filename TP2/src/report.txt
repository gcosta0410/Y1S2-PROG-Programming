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
-When option 3.Winners is selected on the menu and the user asks for a non-existent MAZE_XX_WINNERS.txt file the original output text "Empty list" was changed to a more user friendly version.

    Extra stuff added:   
-Along with the original classes asked, we created a class for the Leaderboard of a maze (contents of the MAZE_XX_WINNERS.txt file) and for the game Timer.
-We added a "Play Again" functionality at the end of each maze so the user doesnt have to go through everything again if they wish to play the same map.
-We have two extra files called "Utils.h/cpp" with all the functions we use that aren't related to the main() function unlike the rules(), winners(), menu() and play() functions are

    Observations:
-The game.exe file can't run on windows systems without a C++ compiler installed, we assumed this was normal.
-To run the game on linux it has to be compiled there first since .exe is not a compatible windows-linux file.
-We tested the program on smaller, bigger and even different shaped, like triangular, mazes, works as expected.

    Ideas not implemented (because we were told not to or just remembered them too late):
-We had a python script to create maze templates. We thought about implementing it in C++ but we just gave that up as it wasn't needed. 
-On the first project we had a difficulty system implemented. 
Sadly, we had to give that up as we felt it was a task we couldn't complete with the time we had, without jeopardizing the base project.

MAIN DIFFICULTIES:
-Often finding ourselves not totally understanding what the other did on certain parts of the code. 
We believe that whoever tackled a certain aspect of the program first would then have an easier time doing what was related to that aspect afterwards.
-Using classes proved to be a challenge at start but when we picked up on how to do it, it became way easier.
-Regarding the basic features asked for, we don't necessarily think this project came out better than the last because we used OOP. 
Since the majority of the code was already done and only had to be adapted, changing something we knew was working fine into something different that had the same purpose felt a bit pointless.
-Working with so many files at once was quite the overwelming task.
-Multiple file compilation was not easy to figure out on VSCode and if wasn't for the help of our friends from group T02_G11 we would've spent a lot of time figuring it out.
