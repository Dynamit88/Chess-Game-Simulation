/**
	Chess Pieces Simulation
	Bishop.h
	Purpose: Bishop piece functionality

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#ifndef BISHOP_H //Class type redefinition guard
#define BISHOP_H

#include "Piece.h"

/* Bishop moves diagonally (Circle) */
class Bishop : public virtual Piece {
public:
	static int score; //To keep captures record of Bishop type of pieces

	Bishop(); //default constructor 
	explicit Bishop(const double x_coordinate, const double y_coordinate); // Prevent implicit type coercions
	virtual ~Bishop() override;

	void move(const bool print) override; // Does not have to be virtual, because Queen makes use of it
	void print() override;
	double radius() const;
	int type() const override;
	std::string getTypeString() const override;
	void incrementScore() override;

	/** OPERATOR OVERLOADS **/
	friend std::ostream & operator << (std::ostream & ostr, const Bishop &b);
protected:
	static const int PIECE_TYPE = 11; // Static piece type // 44 - for Bishop
	static const double RADIUS;
};
#endif //BISHOP_H