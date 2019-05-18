/**
	Chess Pieces Simulation
	Bishop.cpp
	Purpose: Bishop piece functionality

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#include "pch.h"
#include "Bishop.h"
#include "Simulation.h"
#include <iostream>

const double Bishop::RADIUS = Piece::HALF_PIECE_SIZE;
int Bishop::score = 0;

Bishop::Bishop() {} // The default base constructor called
Bishop::Bishop(const double x_coordinate, const double y_coordinate): Piece(x_coordinate, y_coordinate) {}
Bishop::~Bishop() {}

using simulation::Simulation;

/**
Moves piece by random distance in random diagonal direction within the game simulation board boundaries.
@param print - if set to be true move messages will be shown.
@return void
*/
void Bishop::move(const bool print) {
	double newX, newY;
	switch (Simulation::randomInt(1, 4)) {
	case 1: // top right
		if (y > RADIUS && x < simulation::REAL_BOARD_WIDTH) { // Can move up and right
			if (simulation::REAL_BOARD_WIDTH - x > y - RADIUS) { // if piece closer to top than to right end of the board
				newY = Simulation::randomDouble(RADIUS, y); // between top end and current y
				x += y - newY;
				y = newY;
			}
			else {
				newX = Simulation::randomDouble(x, simulation::REAL_BOARD_WIDTH); // between curent x and right end
				y -= newX - x;
				x = newX;
			}
		}
		else { // if move not available - try again
			move(print);
			return;
		}
		break;
	case 2: // top left
		if (y > RADIUS && x > RADIUS) { // Can move up and left
			if (x - RADIUS > y - RADIUS) { // if piece closer to top than to left end
				newY = Simulation::randomDouble(RADIUS, y); // between top and current y
				x -= y - newY;
				y = newY;
			}
			else {
				newX = Simulation::randomDouble(RADIUS, x); // between left end and current x
				y -= x - newX;
				x = newX;
			}
		}
		else { // if move not available - try again
			move(print);
			return;
		}
		break;
	case 3: // bottom right
		if (y < simulation::REAL_BOARD_HEIGHT - RADIUS && x < simulation::REAL_BOARD_WIDTH) { // Can move down and right
			if (simulation::REAL_BOARD_HEIGHT - y > simulation::REAL_BOARD_WIDTH - x) {// if piece is closer to the right side of the board
				newX = Simulation::randomDouble(x, simulation::REAL_BOARD_WIDTH); // between curret x and right end
				y += newX - x;
				x = newX;
			}
			else {
				newY = Simulation::randomDouble(y, simulation::REAL_BOARD_HEIGHT); // between current y and bottom
				x += newY - y;
				y = newY;
			}
		}
		else { // if move not available - try again
			move(print);
			return;
		}
		break;
	case 4: // bottom left
		if (y < simulation::REAL_BOARD_HEIGHT - RADIUS &&  x > RADIUS) { // Can move down adn left
			if (simulation::REAL_BOARD_HEIGHT - y > x - RADIUS) { // if piece closer to left than to bottom
				newX = Simulation::randomDouble(RADIUS, x); // between leftmost and current x
				y += x - newX;
				x = newX;
			}
			else {
				newY = Simulation::randomDouble(y, simulation::REAL_BOARD_HEIGHT); // between current y and bottom
				x -= newY - y;
				y = newY;
			}
		}
		else { // if move not available - try again
			move(print);
			return;
		}
		break;
	}
	if (print) {
		std::cout << getTypeString() <<"\t(id:" << getId() << ") moves to " << x << " ; " << y << std::endl;
	}
}

/**
Print operator overloading.
@param ostream - output steam instance
@param ostream - an instance of Bishop class to print
@return ostream back
*/
std::ostream & operator<<(std::ostream & ostr, const Bishop & b) {
	return ostr << std::left << "Bishop" << "\t(id:" << b.id << "\tx:" << b.x << " y:" << b.y << "  radius:" << b.RADIUS << ")" << std::endl;
}

/**
Print to console member function.
@return void
*/
void Bishop::print() {
	std::cout << *this;
}

/**
Return radius of the piece.
@return radius
*/
double Bishop::radius() const {
	return RADIUS;
}

/**
Return numerical type of the piece.
@return type integer
*/
int Bishop::type() const {
	return PIECE_TYPE;
}

/**
Return alphabetical type of the piece.
@return type string
*/
std::string  Bishop::getTypeString() const {
	return "Bishop";
}

/**
Increment score by 1.
@return void
*/
void  Bishop::incrementScore() {
	score++;
}