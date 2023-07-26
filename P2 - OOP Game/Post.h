//T02_G10
#ifndef POST_H
#define POST_H

class Post{
    public:
        Post(int row, int col, char symbol); // Post class constructor using it's position and char representation
        enum State { ALIVE, DEAD }; // Enum type with possible states of a Post object
        int getRow() const; // Returns the row of a post
        int getCol() const; // Returns the column of a post
        char getSymbol() const; // Returns the char representation of a post
        bool isElectrified() const; // Returns true if post is electrified (Alive = '*'), false otherwise
        void changeState(); // "Kills" an electrified post

    private:
        int row, col;
        State state;
        char symbol; // '*' - electrified (ALIVE); '+'- non-electrified (DEAD)
};

#endif //POST_H
