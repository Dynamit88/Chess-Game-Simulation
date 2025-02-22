/**
	Chess Pieces Simulation
	Game.cpp
	Purpose: program entry point

	@author Ivan Mykolenko (B5015987)
	@date 05/12/2018
*/

#include "pch.h"
#include "Simulation.h"
#include <time.h>   /* time */

const int NUMBER_OF_PIECES = 10; // Number of chess pieces to begin with
const int MAX_NUMBER_OF_MOVES = 120; // Limit of moves

using simulation::Simulation;

int main() {
	srand(time(NULL)); /* initialize random seed: */
	Simulation::populateBoard(NUMBER_OF_PIECES);
	Simulation::play(MAX_NUMBER_OF_MOVES, false); // set second parameter to true to print move messages
	system("pause");
	return 0;
}







