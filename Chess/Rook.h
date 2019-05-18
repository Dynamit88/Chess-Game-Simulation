/**
	Chess Pieces Simulation
	Rook.h
	Purpose: Rook chess piece functionality

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#ifndef ROOK_H //Class type redefinition guard
#define ROOK_H

#include "Piece.h"

/* Rook moves horizontally and vertically (Square) */
class Rook : public virtual Piece {
public:
	static int score; //To keep captures record of Rook type of pieces

	Rook(); //default constructor 
	explicit Rook(const double x_coordinate, const double y_coordinate); // Prevent implicit type coercions
	virtual ~Rook() override;

	void move(const bool print) override; // Does not have to be virtual, because Queen makes use of it
	void print() override;
	double halfSide() const ;
	int type() const override;
	std::string getTypeString() const override;
	void incrementScore()override;
	
	/** OPERATOR OVERLOADS **/
	friend std::ostream & operator << (std::ostream & ostr, const Rook &r);
protected:
	static const int PIECE_TYPE = 44; // Static piece type // 44 - for Rook
	static const double HALF_SIDE;
};
#endif //ROOK_H