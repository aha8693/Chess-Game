/*
 * Header file for Board.cpp that includes custom Board iterator class
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"

namespace Chess
{
  class Board {

		// Throughout, we will be accessing board positions using Position defined in Piece.h.
		// The assumption is that the first value is the column with values in
		// {'A','B','C','D','E','F','G','H'} (all caps)
		// and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

	public:
		// Default constructor
		Board();

		// Non-trivial destructor
		~Board();

		// Copy-constructor -  rule of three
		Board(const Board& origin);

		// = Operator - rule of three
		Board& operator=(const Board& origin);


		// Returns a const pointer to the piece at a prescribed location if it exists,
		// or nullptr if there is nothing there.
		const Piece* operator() (const Position& position) const;

		// Attempts to add a new piece with the specified designator, at the given position.
		// Throw exception for the following cases:
		// -- the designator is invalid, throw exception with error message "invalid designator"
		// -- the specified position is not on the board, throw exception with error message "invalid position"
		// -- if the specified position is occupied, throw exception with error message "position is occupied"
		void add_piece(const Position& position, const char& piece_designator);

		// Helper function for make_move method in Game.cpp
		// This function assumes the given position is valid, 
		// since it is also called by make_move (and related functions). 
		void remove_piece(const Position& position);

		// Displays the board by printing it to stdout
		void display() const;

		// Returns true if the board has the right number of kings on it
		bool has_valid_kings() const;

		// Clears the board
		int clear_board();
                
		// Const_iterator class for Board
	        class const_iterator {
		  	public:
				// Non-default constructor 
				const_iterator(const Position initial) : pos(initial) {}

				// Overloaded operator to increment iterator
		       		const_iterator& operator++() {
					if (pos.first == 'H'){ //if iterator is at very right of board
						pos.second--;
						pos.first = 'A';
						return *this;
					}
					pos.first++;
					return *this;
			 	}		
                                
                                // Overloaded operator to see if two iterators are equal				
		        	bool operator==(const const_iterator& c) const { return pos.first == c.pos.first && pos.second == c.pos.second; }

				// Overloaded operator to see if two iterators are not equal to each other
    		    		bool operator!=(const const_iterator& c) const { return !(*this == c); } 
				
				// Overloaded operator to return position of Board iterator is at
				const Position& operator*() const { return pos; }


		    private:
				// Current position of iterator
				Position pos;
		};
			

		//Method to return top left corner of board
		const_iterator cbegin() const { return const_iterator(Position('A', '8')); }

		//Method to return one down from bottom left corner of board
  		const_iterator cend() const { return const_iterator(Position('A', '0')); }


	private:
	// The sparse map storing the pieces, keyed off locations
	std::map<Position, Piece*> occ;

        // Write the board state to an output stream
        friend std::ostream& operator<< (std::ostream& os, const Board& board);
  	};
}
#endif // BOARD_H
