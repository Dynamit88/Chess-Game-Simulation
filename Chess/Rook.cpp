/**
	Chess Pieces Simulation
	Rook.cpp
	Purpose: Rook chess piece functionality

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#include "pch.h"
#include "Rook.h"
#include "Simulation.h"
#include <iostream>

const double Rook::HALF_SIDE = Piece::HALF_PIECE_SIZE;
int Rook::score = 0;

Rook::Rook() {} // The default base constructor called
Rook::Rook(const double x_coordinate, const double y_coordinate): Piece(x_coordinate, y_coordinate) {}
Rook::~Rook() {}

using simulation::Simulation;

/**
Moves piece by random distance in random (horizontal or vertical) direction within the game simulation board boundaries.
@param print - if set to be true move messages will be shown.
@return void
*/
void Rook::move(const bool print) {
	double newX = x, newY = y;
	switch (Simulation::randomInt(1, 4)) {
	case 1: // Up
		if (y > HALF_SIDE) { // Can move up 
			newY = Simulation::randomDouble(HALF_SIDE, y);
		}
		else { // if move not available - try again
			move(print);
			return;
		}
		break;
	case 2: //Down
		 if (y < simulation::BOARD_HEIGHT - HALF_SIDE) { // Can go down
			newY = Simulation::randomDouble(y, simulation::BOARD_HEIGHT - HALF_SIDE);
		 }
		 else { // if move not available - try again
			 move(print);
			 return;
		 }
		break;
	case 3:
		if (x < simulation::BOARD_WIDTH - HALF_SIDE) { // Can move right and this random move = true
			newX = Simulation::randomDouble(x, simulation::BOARD_WIDTH - HALF_SIDE);
		}
		else { // if move not available - try again
			move(print);
			return;
		}
		break;
	case 4:
		 if (x > HALF_SIDE) { // Can move left
			newX = Simulation::randomDouble(HALF_SIDE, x);
		 }
		 else { // if move not available - try again
			 move(print);
			 return;
		 }
		break;
	default:
		std::cout << "Default called" << std::endl;
	}
	x = newX;
	y =	newY;
	if (print) {
		std::cout << getTypeString() << "\t(id:" << getId() << ") moves to " << x << " ; " << y << std::endl; 
	}
}

/**
Print operator overloading.
@param ostream - output steam instance
@param ostream - an instance of Bishop class to print
@return ostream back
*/
std::ostream & operator<<(std::ostream & ostr, const Rook &r) {
	return ostr << "Rook" << "\t(id:" << r.id << "\tx:" << r.x << " y:" << r.y << "  side length:" << r.size() << ")" << std::endl;
}

/**
Print to console member function.
@return void
*/
void Rook::print() {
	std::cout << *this;
}

/**
Return half of the side length.
@return radius
*/
double Rook::halfSide() const {
	return HALF_SIDE;
}

/**
Return numerical type of the piece.
@return type integer
*/
int Rook::type() const {
	return PIECE_TYPE;
}

/**
Return alphabetical type of the piece.
@return type string
*/
std::string  Rook::getTypeString() const {
	return "Rook";
}

/**
Increment score by 1.
@return void
*/
void  Rook::incrementScore() {
	 score++;
}