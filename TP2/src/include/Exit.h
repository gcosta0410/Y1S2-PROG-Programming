//T02_G10
#ifndef EXIT_H
#define EXIT_H
	
class Exit{
	public:
		Exit(int row, int col); // Exit class constructor
		int getRow() const; // Returns the row of an exit
		int getCol() const; // Returns the column of an exit

	private:
		int row, col;

};
#endif //EXIT_H
