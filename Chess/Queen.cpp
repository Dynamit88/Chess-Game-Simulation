/**
	Chess Pieces Simulation
	Queen.cpp
	Purpose: Queen chess piece functionality

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#include "pch.h"
#include "Queen.h"
#include "Simulation.h"
#include <iostream>

const double Queen::RADIUS = Piece::HALF_PIECE_SIZE;
int Queen::score = 0;

Queen::Queen() {} // The default base constructor called
Queen::Queen(const double x_coordinate, const double y_coordinate) :  Piece(x_coordinate, y_coordinate) {}
Queen::~Queen() {}

using simulation::Simulation;

/**
Moves piece by random distance in random (diagonal, horizontal or vertical) direction within the game simulation board boundaries.
@param print - if set to be true move messages will be shown.
@return void
*/
void Queen::move(const bool print) {
	if (Simulation::randomInt(0, 1)) {
		Bishop::move(print); //Re-use bishop's move function
	}
	else {
		Rook::move(print); //Re-use rook's move function
	}
}

/**
Print operator overloading.
@param ostream - output steam instance
@param ostream - an instance of Bishop class to print
@return ostream back
*/
std::ostream & operator<<(std::ostream & ostr, const Queen & q) {
	return ostr << std::left << "Queen" << "\t(id:" << q.id << "\tx:" << q.x << " y:" << q.y << "  radius:" << q.RADIUS << ")" << std::endl;
}

/**
Print to console member function.
@return void
*/
void Queen::print() {
	std::cout << *this;
}

/**
Return radius of the piece.
@return radius
*/
double Queen::radius() const {
	return RADIUS;
}

/**
Return numerical type of the piece.
@return type integer
*/
int Queen::type() const {
	return PIECE_TYPE;
}

/**
Return alphabetical type of the piece.
@return type string
*/
std::string  Queen::getTypeString() const {
	return "Queen";
}

/**
Increment score by 1.
@return void
*/
void  Queen::incrementScore() {
	score++;
}