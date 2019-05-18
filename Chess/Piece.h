/**
	Chess Pieces Simulation
	Piece.h
	Purpose: class to represent moving chess pieces in game

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#ifndef PIECE_H //Class type redefinition guard
#define PIECE_H

#include<string>
#include <stdexcept>

class Piece {

public:
	static const double PIECE_SIZE;
	static const double HALF_PIECE_SIZE;

	Piece();
	explicit Piece(const double x, const double y) throw (std::invalid_argument); // Prevent implicit type coercions
	virtual~Piece() = 0; // Virtual destructor for abstract class

	/** PURE VIRTUAL FUNCTIONS **/
	virtual void move(bool print = false) = 0;
	virtual void print() = 0;
	virtual int type() const = 0; 
	virtual std::string getTypeString() const = 0;
	virtual void incrementScore() = 0;

	/** GETTERS **/
	double size() const; 
	double halfSize() const; 
	double getX() const;
	double getY() const;
	double getId() const;
	
	/** OPERATOR OVERLOADS **/
	bool operator==(const Piece &rhs) const;
	bool operator!=(const Piece &rhs) const;
protected:
	static int id_couter; //Id assigned to each Piece instance
	int id;
	double x, y;
};
#endif //PIECE_H