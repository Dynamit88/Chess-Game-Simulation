/**
	Chess Pieces Simulation
	Simulation.cpp
	Purpose: game's logic 

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#include "pch.h"
#include "Queen.h"
#include "Simulation.h"
#include <iostream>

namespace simulation {
	std::vector<Piece *> Simulation::pieces; // Vector to store pointers to instances Piece class 
	
	/**
	Randomly generates chess pieces (Bishop, Queen or Rook) and assigns them positions so that pieces don't overlap.
	Function attempts to find a space for a new piece on the game board 50 times. If it fails to find one, it throws an error, 
	which means the board is full and can't take any more pieces. 
	@param numberOfPieces - the number of pieces to generate.
	@return void
	*/
	void Simulation::populateBoard(int numberOfPieces) throw (std::runtime_error) {
		Piece *newPiece = NULL;
		for (int i = 0; i < numberOfPieces; i++) {
			int k = 0;
			bool positionOk = false;
			try { 
				switch (randomInt(1, 3)) { //Random piece type
				case 1:
					newPiece = new Bishop();
					break;
				case 2:
					newPiece = new Rook();
					break;
				case 3:
					newPiece = new Queen();
				}
				//find suitable position for the new piece
				while (k < 50 && !positionOk) { //Try 50 times to find a space for the new piece
					if (findPosition(newPiece)) {
						positionOk = true;
						break;
					}
					newPiece->move(); //chnage position
					k++;
				}
				if (!positionOk) {
					throw std::runtime_error("Too many pieces on the board.");
				}
			}
			/*if cannot fit all the elements on board (or if piece's constructor throws an error) - terminate execution*/
			catch (const std::exception& e) { 
				emptyPiecesVector(); // Release memory
				std::cout << e.what() << '\n';
				exit(EXIT_FAILURE); // Terminate with error 
			}
		}
	}

	/**
	Loops through the vector of pieces and checks whether newPiece overlaps with pieces that are already on the board. If it doesn't, 
	the piece gets placed on the board. 
	@param newPiece - newly-created instance of the Piece class.
	@return true if there are no overlaps.
	*/
	bool Simulation::findPosition(Piece * newPiece) {
		for (std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) { //Through every element on board
			if (overlaps(newPiece, (*it))) {
				return false;
			}
		}
		pieces.push_back(newPiece); //Place new piece on the board
		return true; 
	}	

	/**
	Launches game simulation.
	@param maxNumberOfMoves - the limit of movies which applies to each piece.
	@param printMoves - if set to be true move messages will be shown.
	@return void
	*/
	void Simulation::play(const int maxNumberOfMoves, const bool printMoves) {
		int i = 0;
		// Show initial pieces on the board
		std::cout << "Initial pieces on the board: " << std::endl;
		showPiecesOnTheBoard();
		while (i < maxNumberOfMoves && pieces.size() != 1) { // Each piece gets equal nuber of of moves
			int n = 0;
			for (n; n < pieces.size(); n++) { // Through every element on board
				pieces[n]->move(printMoves); // Random move within board's bounds (set true to print moves)
				take(pieces[n]); // Check if the piece overlaps with any other pieces and if so, take them out
			}
			i++;
		}
		std::cout << std::string(70, '=') << std::endl;
		if (pieces.size() == 1) { // If one figure left 
			std::cout << "The winning pieces is: ";
			pieces[0]->print();
		}
		else {
			std::cout << "Simulation has exceeded the maximum number of moves." << std::endl << "Pieces remaining on the board: " << pieces.size() << std::endl;
		}
		std::cout << std::string(70, '=') << std::endl;
		// Present scores
		std::cout << "\t\tSCORES" << std::endl;
		std::cout << "Bishop:" << Bishop::score << "; Rook:" << Rook::score << "; Queen:" << Queen::score << std::endl;
		emptyPiecesVector(); // Release remaining pieces
	}

	/**
	Checks whether moving piece overlaps any other pieces. If so, non-moving pieces removed and score is incremented.
	@param movingPiece - an instance of Piece class that has made a move.
	@return void
	*/
	void Simulation::take(Piece *movingPiece) {
		std::vector<Piece*>::iterator it = pieces.begin();
		while (it != pieces.end()) {
			if (overlaps(movingPiece, (*it))) {
				std::cout << movingPiece->getTypeString() << "\t(id:" << movingPiece->getId() << "  " << movingPiece->getX() << " ; " << movingPiece->getY() << ") takes " << (*it)->getTypeString() << " (id:" << (*it)->getId() << "  " << (*it)->getX() << " ; " << (*it)->getY() << ")" << std::endl;
				delete (*it); // release memory
				it = pieces.erase(it); // pointer to the next element
				movingPiece->incrementScore(); // add score point
			}
			else {
				++it;
			}
		}
	}

	/**
	Function checks whether two instances of Peace base class overlap one another.
	@param p1 - first piece.
	@param p2 - second piece.
	@return true if they overlap.
	*/
	bool Simulation::overlaps(const Piece *p1, const Piece *p2) {
		if (*p1 != *p2) { //If comparing different pieces
			switch (p1->type() * p2->type()) {
			case 121: //(Circle-circle)(Bishop-Bishop)
			case 605: //(Circle-circle)(Bishop-Queen)
			case 3025://(Circle-circle)(Queen-Queen)
			{ //Scope out
				double distance = Piece::PIECE_SIZE; //distance between piece centres
				double deltaX = p2->getX() - p1->getX();
				double deltaY = p2->getY() - p1->getY();
				//If distance between centres of the circles is less than sum of radiuses
				return (deltaX * deltaX + deltaY * deltaY) < (distance * distance); //sqrt((x2 - x1)^2 + (y2 -y1)^2)
			}
			break;
			case 484: //(Circle-square)(Bishop-Rook)
			case 2420: //(Circle-square)(Queen-Rook)
				if (p1->type() == 44) { //If p1 is an instance of Rook 
					return circleOverlapsSquare(p2, p1);
				}
				else {
					return circleOverlapsSquare(p1, p2);
				}
				break;
			case 1936: //(Square-square)(Rook-Rook)
				double x1 = p1->getX() - p1->halfSize(); //Square1 leftmost point
				double y1 = p1->getY() - p1->halfSize(); //Square1 top point
				double x2 = p1->getX() + p1->halfSize(); //Square1 rightmost point
				double y2 = p1->getY() + p1->halfSize(); //Square1 bottom point			

				double x3 = p2->getX() - p2->halfSize(); //Square2 leftmost point
				double y3 = p2->getY() - p2->halfSize(); //Square2 top point
				double x4 = p2->getX() + p2->halfSize(); //Square2 rightmost point
				double y4 = p2->getY() + p2->halfSize(); //Square2 bottom point		

				return
					((x3 > x1 && x3 < x2) && ((y3 > y1 && y3 < y2) || (y4 > y1 && y4 < y2))) // Right corners of 1st square and left corners of second square 
					||
					((x4 > x1 && x4 < x2) && ((y3 > y1 && y3 < y2) || (y4 > y1 && y4 < y2))) // Left corners of 1st square and right corners of second square 
					||
					!((p1->getX() > x4 || x2 < p2->getX()) || (p1->getY() > y4 || y2 < p2->getY())); // One square within the other ovelapings
				break;
			}
		}
		return false;
	}

	/**
	Helper function to check circle-square overlapings. 
	@param circle - either instance of a Bishop or a Queen.
	@param square - and instance of Rook.
	@return true if they overlap.
	*/
	bool Simulation::circleOverlapsSquare(const Piece *circle, const Piece *square) {
		double distance = Piece::PIECE_SIZE; //distance between piece centres
		double deltaX = abs(circle->getX() - square->getX());
		double deltaY = abs(circle->getY() - square->getY());

		if (deltaY >= distance || deltaX >= distance) { return false; } //Circle is too far
		if (deltaX < square->halfSize() || deltaY < square->halfSize()) { return true; }//Circle overlaps a side of the square

		// Calculate distance from square's centre to delta //sqrt((x2 - x1)^2 + (y2 -y1)^2)
		double square_bisectris = (deltaX - square->halfSize()) * (deltaX - square->halfSize()) + (deltaY - square->halfSize()) * (deltaY - square->halfSize());

		return square_bisectris < (circle->halfSize() * circle->halfSize()); //If circle originates closer than lenght of suquare's bisectris
	}

	/**
	Generates random integer in range from min to max.
	@param min - lower boundary.
	@param max - upper boundary.
	@return random integer in range from min to max.
	*/
	int Simulation::randomInt(const int min, const int max) {
		return rand() % (max - min + 1) + min;
	}

	/**
	Generates random double in range from min to max.
	@param min - lower boundary.
	@param max - upper boundary.
	@return random double in range from min to max.
	*/
	double Simulation::randomDouble(const double min, const double max) {
		return (int)(100 * ((max - min) * ((double)rand() / (double)RAND_MAX) + min)) / 100.0;
	}

	/**
	Function to display elements in vector. 
	@return void
	*/
	void Simulation::showPiecesOnTheBoard() {
		for (std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
			(*it)->print();
		}
		std::cout << std::string(70, '=') << std::endl;
	}

	/**
	Erase vector and release memory.
	@return void
	*/
	void Simulation::emptyPiecesVector() {
		for (std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end();) { //Through every element in the vector
			delete (*it); //release memory
			it = pieces.erase(it); //Poiner to the next element
		}
	}
}