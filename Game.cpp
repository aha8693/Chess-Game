/*
 * Defines functions of Game class such as making a move, checking
 * if a player is in check, checkmate, and stalemate, reading and
 * writing of a game, and more
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */

#include <cassert>
#include "Game.h"
#include "Exceptions.h"
#include "Piece.h"
#include "Board.h"
#include <cstdlib>
#include <vector>

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}

  //Copy constructor
  Game::Game(const Game& origin) {
    this->is_white_turn = origin.is_white_turn;
    this->board = origin.board;
  }

  //Assignment operator
  Game& Game::operator=(const Game& origin) {
    if (this == &origin) {
      throw Exception("Cannot assign to itself");
    }

    is_white_turn = origin.is_white_turn;
    board = origin.board;
    return *this;
  }

  // Attempts to make a move. If successful, the move is made and
	// the turn is switched white <-> black. Otherwise, an exception is thrown
	void Game::make_move(const Position& start, const Position& end) {
		if (start.first < 'A' || start.first > 'H' || start.second < '1' || start.second > '8') { 
      throw Exception("start position is not on board");
    }

    if (end.first < 'A' || end.first > 'H' || end.second < '1' || end.second > '8') { 
      throw Exception("end position is not on board");
    }

    if (board(start) == nullptr) {
      throw Exception("no piece at start position");
    }

    if (board(start)->is_white() != turn_white()) {
      throw Exception("piece color and turn do not match");
    }
    
    if (board(end) == nullptr && !board(start)->legal_move_shape(start, end)) {
      throw Exception("illegal move shape");
    }

    if (board(end) != nullptr && !board(start)->legal_capture_shape(start, end)) {
      throw Exception("illegal capture shape");
    }

    if (int line_type = is_straight_line(start, end)) {
      if (!path_clear(line_type, start, end)) {
        throw Exception("path is not clear");
      }
    }

    if ((board(end) != nullptr) && (board(end)->is_white() == turn_white())) {
      throw Exception("cannot capture own piece");
    }

    // Attempt to move with a replicated game
    Game replicate = *this;
		const Piece* temp = board(start);
    replicate.board.remove_piece(start);
    if (board(end) != nullptr) { // If such move is capture move
      replicate.board.remove_piece(end);
    }
    replicate.board.add_piece(end, temp->to_ascii());
    if (replicate.in_check(replicate.is_white_turn)) {
      throw Exception("move exposes check");
    }

    // Successful move
    this->board.remove_piece(start);
    if (board(end) != nullptr) { // If such move is capture move
      this->board.remove_piece(end);
    }
    this->board.add_piece(end, temp->to_ascii());

    piece_promotion(end); // Piece promotion before chainging the turn

    is_white_turn = (is_white_turn) ? false : true;
	}

  //Assuming the movement is legal, this function checks whether the move is a straight line.
  //Straight line includes horizontal, vertical, or diagonal
  int Game::is_straight_line(const Position& start, const Position& end) const {
    float col_diff = end.first - start.first;
    float row_diff = end.second - start.second;

    if (col_diff == 0) { return 1; } // vertical 
    if (row_diff == 0) { return 2; } // horizontal
    if (std::abs(col_diff / row_diff) == 1) { return 3; } //Diagonal 

    return 0;
  }

  //Assuming start and end positions are in a legal shape, 
  //this function checks whether the path from start to end is clear. 
  //Only paths of straight lines are checked. 
  //Note that moving forward and backward are checked seperately for pieces like pawn, 
  //where only forward movement is allowed. (And also for the mystery piece)
  bool Game::path_clear(const int line_type, const Position& start, const Position& end) const {
    Position cur;
    //Vertical Case
    if (line_type == 1) { 
      if (end.second - start.second > 0) { // moving upward
        cur = start;
        for (int i = start.second + 1; i < end.second; i++) {
          cur.second ++;
          if (board(cur) != nullptr) {
            return false;
          }
        }
        return true;
      }
      else { //moving downward
        cur = start;
        for (int i = start.second - 1; i > end.second; i--) {
          cur.second--;
          if (board(cur) != nullptr) {
            return false;
          }
        }
        return true;
      }
    }

    //Horizontal Case  
    else if (line_type == 2) {
      if (end.first - start.first > 0) { // moving right
        cur = start;
        for (int i = 1 + start.first; i < end.first; i++) {
          cur.first++;
          if (board(cur) != nullptr) {
            return false;
          }
        }
        return true;
      }
      else { //moving left
        cur = start;
        for (int i = start.first - 1; i > end.first; i--) {
          cur.first--;
          if (board(cur) != nullptr) {
            return false;
          }
        }
        return true;
      }
    }

    //Diagonal Case  
    else {
      if ((end.first - start.first > 0) && (end.second - start.second > 0)) { // moving upward-right
        cur = start;
        for (int i = start.second + 1; i < end.second; i++) {
          cur.first++;
          cur.second++;
          if (board(cur) != nullptr) {
            return false;
          }
        }
        return true;
      }
      else if ((end.first - start.first > 0) && (end.second - start.second < 0)) { // moving downward-right
        cur = start;
        for (int i = start.second - 1; i > end.second; i--) {
          cur.first++;
          cur.second--;
          if (board(cur) != nullptr) {
            return false;
          }
        }
        return true;
      }
      else if ((end.first - start.first < 0) && (end.second - start.second < 0)) { // moving downward-left
        cur = start;
        for (int i = start.second - 1; i > end.second; i--) {
          cur.first--;
          cur.second--;
          if (board(cur) != nullptr) {
            return false;
          }
        }
        return true;
      }
      else { // moving upward-left
        cur = start;
        for (int i = start.second + 1; i < end.second; i++) {
          cur.first--;
          cur.second++;
          if (board(cur) != nullptr) {
            return false;
          }
        }
        return true;
      }
    }
    return false;
  }

  // Helper methods for make_move; when pawn is at the end of the board, it is promoted to a queen
  void Game::piece_promotion(const Position& end) {
    if (board(end)->to_ascii() == 'P') {
      if (end.second == '8') {
        this->board.remove_piece(end);
        this->board.add_piece(end, 'Q');
      }
    }

    if (board(end)->to_ascii() == 'p') {
      if (end.second == '1') {
        this->board.remove_piece(end);
        this->board.add_piece(end, 'q');
      }
    }
  }
  

  //Returns true if our piece at a posisition can still make a move
  bool Game::can_move(const Position& pos) const{
    for(Board::const_iterator cit = board.cbegin(); cit!= board.cend(); ++cit){
      //Make a copy of current game
      Game hypothetical_game(*this);
      //Use make_move to see if a move is possible
      try {
        hypothetical_game.make_move(pos, *cit);
      }
      catch(Exception& e){
        continue;
      }
      return true;
    }
    return false;
  }

  // Returns true if the designated player is in check
	bool Game::in_check(const bool& white) const {
	
    Position kings_position; 
    std::vector<Position> opponents;
    if (white){
      for(Board::const_iterator cit = board.cbegin(); cit != board.cend(); ++cit){
	      if (board(*cit)){
          if (board(*cit)->to_ascii() == 'K'){
            kings_position = *cit;
          }
          if (board(*cit)->to_ascii() > 'Z'){ // black pieces
            opponents.push_back(*cit);
          }
        }
      }
    } else {
        for(Board::const_iterator cit = board.cbegin(); cit != board.cend(); ++cit){
	        if (board(*cit)){
            if (board(*cit)->to_ascii() == 'k') {
              kings_position = *cit;
            }
            if (board(*cit)->to_ascii() < 'a') { // white pieces
              opponents.push_back(*cit);
            }
          }
        }
      }
    int line_type = 0;
    for (std::vector<Position>::const_iterator cvit = opponents.cbegin(); cvit != opponents.cend(); ++cvit) {
      if (board(*cvit)->legal_capture_shape(*cvit, kings_position)) {
        line_type = is_straight_line(*cvit, kings_position);
        if (line_type && path_clear(line_type, *cvit, kings_position)) {
          return true;
        }
      }
    }
		return false;
	}

  // Returns true if the designated player is in mate
	bool Game::in_mate(const bool& white) const{
    if(!in_check(white)) { // Make sure player is in check
      return false;
    }
    for(Board::const_iterator cit = board.cbegin(); cit != board.cend(); ++cit){
      if(board(*cit) != nullptr && board(*cit)->is_white() == white){
        if(can_move(*cit)){ // Make sure player cannot make any legal moves
	        return false;
	      }
      }
    }
    return true;
  }
	

  // Returns true if the designated player is in mate
	bool Game::in_stalemate(const bool& white) const {
    for(Board::const_iterator cit = board.cbegin(); cit != board.cend(); ++cit){
      if (board(*cit) != nullptr && board(*cit)->is_white() == white) {
        if(can_move(*cit)) {
          return false;
        }
      }
    }
    return true;

	}

  // Return the total material point value of the designated player
  int Game::point_value(const bool& white) const {
      int points = 0;
      for(Board::const_iterator cit = board.cbegin(); cit!= board.cend(); ++cit){
        if(board(*cit) != nullptr && board(*cit)->is_white() == white){
          points += board(*cit)->point_value();
        }
      }
      return points;
    }

  // Reads the board in from a stream
  std::istream& operator>> (std::istream& is, Game& game) {
		//Make sure board is empty
    game.board.clear_board();

    //Add/load pieaces to board
    char get_piece;
		for(int row = '8'; row >= '1'; row--){
      for(int col = 'A'; col <= 'H'; col++){
        is >> get_piece;
        //std::cout << get_piece;
        if(get_piece != '\n' && get_piece != '-'){
          Position pos = Position(col, row);
          game.board.add_piece(pos, get_piece);
        }
      }
      //std::cout << std::endl;
    }

    //Get ninth line of who's turn, where 'w' denotes the white pieces and 'b' denotes the black pieces. 
    //For files representing in-progress games, this character indicates which player's turn is next, but 
    //in the case of a game that has reached checkmate or stalemate, the letter on the ninth line will indicate 
    //the player whose turn it was when the game ended.
    char turn;
    is >> turn;

    //Failure to load game due to inelligble player turn char
    std::cout << turn << std::endl;
    if(turn != 'w' && turn != 'b'){
      throw Exception();
    }

    //See if it is the white player's turn
    game.is_white_turn = (turn == 'w');
		return is;
	}

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
   /////////////////////////////////////
  // Writes the board out to a stream
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}
