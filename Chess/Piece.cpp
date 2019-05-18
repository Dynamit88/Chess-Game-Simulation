/**
	Chess Pieces Simulation
	Piece.cpp
	Purpose: class to represent moving chess pieces in game

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#include "pch.h"
#include "Piece.h"
#include <string>
#include "Simulation.h"
#include <stdlib.h>

 int Piece::id_couter = 1;
 const double Piece::PIECE_SIZE = 8.85; // Every piece is the same size
 const double Piece::HALF_PIECE_SIZE = PIECE_SIZE / 2;

 /**
 Default base class constructor. Places piece in the top-left corner of the game simulation board.
 */
Piece::Piece(): id(id_couter++) {
	x = PIECE_SIZE; 
	y = PIECE_SIZE; 
}

/**
Base class constructor. Throws an error if coordinates passed on are outside of the game board boundaries.
@param x_coordinate - x coordinate of new Piece.
@param y_coordinate - y coordinate of new Piece.
*/
Piece::Piece(const double x_coordinate, const double y_coordinate) throw (std::invalid_argument) : id(id_couter++){
	if (x_coordinate >= HALF_PIECE_SIZE && y_coordinate >= HALF_PIECE_SIZE) { //within minimal bounds
		if (x_coordinate <= simulation::BOARD_WIDTH && y_coordinate <= simulation::BOARD_HEIGHT) { // within maximal bounds
			x = x_coordinate;
			y = y_coordinate;
		}
		else {
			throw std::invalid_argument("Coordinates must be within the board bounds");
		}
	}
	else {
		throw std::invalid_argument("Coordinates must be grater or equal to 0!");
	}
}

Piece::~Piece() {}

/**
Return size of the piece.
@return size
*/
double Piece::size() const {
	return PIECE_SIZE;
}

/**
Return half of a piece size (radius/half side).
@return half of the size
*/
double Piece::halfSize() const {
	return HALF_PIECE_SIZE;
}

/**
Return unique identifier of a piece.
@return int id
*/
double  Piece::getId() const {
	return id;
}

/**
Return x coordinate.
@return x
*/
double Piece::getX() const {
	return x;
}

/**
Return y coordinate.
@return y
*/
double Piece::getY() const {
	return y;
}

/**
Piece equality operator.
@return true if pieces's ids match
*/
bool Piece::operator==(const Piece & rhs) const {
	return this->id == rhs.id;
}

/**
Piece inequality operator.
@return true if piece's ids don't match
*/
bool Piece::operator!=(const Piece & rhs) const {
	return !(*this == rhs);
}