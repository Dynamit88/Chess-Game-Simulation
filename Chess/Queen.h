/**
	Chess Pieces Simulation
	Queen.h
	Purpose: Queen chess piece functionality

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#ifndef QUEEN_H //Class type redefinition guard
#define QUEEN_H

#include "Bishop.h"
#include "Rook.h"

/* Queen moves horizontally, vertically and by diagonal (Circle) */
class Queen : public Bishop, public Rook {
public:
	static int score; //To keep captures record of Queen type of pieces

	Queen(); //default constructor 
	explicit Queen(const double x_coordinate, const double y_coordinate); // Prevent implicit type coercions
	~Queen() override;

	void move(const bool print) override; // Override base Piece class
	void print() override;
	double radius() const;
	int type() const override;
	std::string getTypeString() const override;
	void incrementScore() override;

	/** OPERATOR OVERLOADS **/
	friend std::ostream & operator << (std::ostream & ostr, const Queen &q);
protected:
	static const int PIECE_TYPE = 55; // Static piece type // 55 - for Queen
	static const double RADIUS;
};
#endif //QUEEN_H