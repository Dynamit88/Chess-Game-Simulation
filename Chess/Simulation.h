/**
	Chess Pieces Simulation
	Simulation.h
	Purpose: game's logic

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#ifndef SIMULATION_H //Class type redefinition guard
#define SIMULATION_H

#include "Piece.h"
#include <vector>

namespace simulation {
	static const int BOARD_WIDTH = 100; // The width of the chess game simulation board
	static const int BOARD_HEIGHT = 200; // The height of the chess game simulation board
	static const double REAL_BOARD_WIDTH = BOARD_WIDTH - Piece::HALF_PIECE_SIZE; // Half of piece size offset
	static const double REAL_BOARD_HEIGHT = BOARD_HEIGHT - Piece::HALF_PIECE_SIZE; // Half of piece size offset

	static class Simulation {
	public:
		static void populateBoard(const int numberOfPieces) throw (std::runtime_error);
		static void play(const int maxNumberOfMoves, const bool printMoves = false);
		static int randomInt(const int min, const int max); // Used widely among classes to make arbitrary decisions
		static double randomDouble(const double min, const double max);
		static void showPiecesOnTheBoard();

	private:
		/** SIMULATION HELPER FUNCTIONS **/
		static bool overlaps(const Piece *p1, const Piece *p2);
		static bool circleOverlapsSquare(const Piece *circle, const Piece *square);
		static void emptyPiecesVector();
		static void take(Piece * newPiece);
		static bool findPosition(Piece *p);

		static std::vector<Piece *> pieces; //Vector to store pointers to instances of Piece class
	};
}
#endif //SIMULATION_H