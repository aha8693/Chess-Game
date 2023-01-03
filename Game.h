/*
 * Header file for Game.cpp 
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{

	class Game {

	public:
		// This default constructor initializes a board with the standard
		// piece positions, and sets the state to white's turn
		Game();

		//Destructor
		~Game() {}

		//Copy constructor
		Game(const Game& origin);
		
		//Assignment operator
		Game& operator=(const Game& origin);

		// Returns true if it is white's turn
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		bool turn_white() const { return is_white_turn; }
    
    	/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    	// Displays the game by printing it to stdout
		void display() const { board.display(); }
    
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    	// Checks if the game is valid
		bool is_valid_game() const { return board.has_valid_kings(); }

		// Attempts to make a move. If successful, the move is made and
		// the turn is switched white <-> black. Otherwise, an exception is thrown
		void make_move(const Position& start, const Position& end);

		//Assuming the movement is legal, this function checks whether the move is a straight line.
		//Straight line includes vertical(=1), horizontal(=2), or diagonal(=3)
		int is_straight_line(const Position& start, const Position& end) const;

		//Assuming start and end positions are in a legal shape, 
		//this function checks whether the path from start to end is clear. 
		//Only paths of straight lines are checked. 
		//Note that moving forward and backward are checked seperately for pieces like pawn, 
		//where only forward movement is allowed. (And also for the mystery piece)
		bool path_clear(const int line_type, const Position& start, const Position& end) const;

		// Helper methods for make_move; when pawn is at the end of the board, 
		// it is promoted to a queen
		void piece_promotion(const Position& end);

		// Returns true if the designated player is in check
		bool in_check(const bool& white) const;

		// Returns true if the designated player is in mate
		bool in_mate(const bool& white) const;

		// Returns true if the designated player is in mate
		bool in_stalemate(const bool& white) const;

		//Returns true if our piece at a posisition can still make a move
  		bool can_move(const Position& pos) const;

        // Return the total material point value of the designated player
        int point_value(const bool& white) const;

	

	private:
		// The board
		Board board;

		// Is it white's turn?
		bool is_white_turn;

        // Writes the board out to a stream
        friend std::ostream& operator<< (std::ostream& os, const Game& game);
         
        // Reads the board in from a stream
        friend std::istream& operator>> (std::istream& is, Game& game);
	};
}
#endif // GAME_H
