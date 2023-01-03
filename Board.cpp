/*
 * Defines functions of Board class such as adding and removing pieces
 * displaying the board, determining piece at given position, and more
 * Final Project
 * Anna An, Dee Velazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */

#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"
#include <vector>
#include <string>

using std::endl;
using std::cout;
using std::vector;
using std::map;
using std::string;

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////

  // Default constructor
  Board::Board(){}
  
  // Destructor
  Board::~Board() {
    for(map<Position, Piece*>::iterator it = occ.begin(); it != occ.end(); ++it) {
      delete it->second; // deallocates all memory of Piece pointers in current board
    }
  }
  
  // Copy constructor
  Board::Board(const Board& origin) {
    for (map<Position, Piece*>::const_iterator it = origin.occ.cbegin(); it != origin.occ.cend(); ++it) {
      if (it->second) {
      	this->add_piece(it->first, it->second->to_ascii());
      }
    }
  }
  
  // Assigns a Board to another
  Board& Board::operator=(const Board& origin) {
    if (this == &origin) { // if origin is the same as current Board
      throw Exception("Cannot assign itself");
    } 
    if (!occ.empty()) { // if current board is not empty
      for (map<Position, Piece*>::iterator it = this->occ.begin(); it != this->occ.end(); ++it) {
        delete it->second; // deallocate Piece pointers of current Board
      }
    }
    for (map<Position, Piece*>::const_iterator it = origin.occ.cbegin(); it != origin.occ.cend(); ++it) {
      this->add_piece(it->first, it->second->to_ascii()); // Set Board to origin
    }
    return *this;
  }
  
  // Overloaded operator that returns Piece pointer at given position
  const Piece* Board::operator()(const Position& position) const {
    vector<Position> posVec;
    for (map<Position, Piece*>::const_iterator citFirst = occ.begin(); citFirst != occ.end(); ++citFirst){
      posVec.push_back(citFirst->first); // Make Position vector of all Positions in current Board that have a piece
    }
    for(vector<Position>::const_iterator citSecond = posVec.begin(); citSecond != posVec.end(); ++citSecond){
      if (citSecond->first == position.first && citSecond->second == position.second){ // when Position matches
        return occ.at(position); // return Piece pointer at position
      }
    }	 
    return nullptr; // return nullptr if no matches
  }
  
  // Adds piece to Board
  void Board::add_piece(const Position& position, const char& piece_designator) {

    //Pointer to specified position. Will be used to see if there is a piece at that location.
    const Piece* piece_checker = (*this)(position);

    // Piece pointer to test piece_designator
    Piece* testPiece = create_piece(piece_designator);
    
    //An invalid piece designator is provided
    if(testPiece == nullptr){
      throw Exception("invalid designator");
    }

    //The specified position is already occupied on the board.
    if(piece_checker != nullptr){
      throw Exception("position is occupied");
    }

    //The specified position is not on the board.
    if(position.first < 'A' || position.first > 'H' || position.second < '1' || position.second > '8'){
      throw Exception("invalid position");
    }

    // Add piece to position of current board
    occ[position] = testPiece;
  }

  // Helper function for make_move method in Game.cpp
	// This function assumes the given position is valid, 
	// since it is also called by make_move (and related functions). 
  void Board::remove_piece(const Position& position) {
    //Removes piece from map AKA board
    occ.erase(position);
    //Deallocating piece memmory by getting rid of pointer to piece
    delete (*this) (position);
  }

  void Board::display() const { 
    //Print out position letter labels at top of board
    cout << " ";
    for(char c = 'A'; c <= 'H'; c++){
      Terminal::color_fg(true, Terminal::BLACK); // make labels bright
      cout << c;
      Terminal::set_default();
    }
    cout << endl;
    for (Board::const_iterator it = cbegin(); it != cend(); ++it){
      const Piece* piece = (*this)(*it); // get Piece pointer at location
      string pieceString = "";
      bool isEven = (int)((*it).second) % 2 == 0; // true if position number is even
      bool isOddASC = (int)((*it).first) % 2 != 0; // true if position letter is A, C, E...
      if (piece){ // if there is piece at location
        pieceString = piece->to_unicode(); // get Chess piece character
      }
      else{
        pieceString = " "; // make string a space
      }            
      if((*it).first == 'A'){ // if position on very left of board
        Terminal::color_fg(true, Terminal::BLACK); // Make labels bright
        cout << (*it).second; // Label left side of board with position numbers
        if(piece && piece->is_white()){ 
          Terminal::set_default();  
        }
        if((isEven && isOddASC) || (!isEven && !isOddASC)){ 
          Terminal::color_bg(Terminal::CYAN); // Make every other square on board Cyan
        }
        else {
          Terminal::color_bg(Terminal::YELLOW); // Make every other square Yellow
        }
              cout << pieceString;  
              Terminal::set_default();
      }
      else if((*it).first == 'H') { // if position on very right of board
        Terminal::color_fg(true, Terminal::BLACK);
        if(piece && piece->is_white()){
          Terminal::set_default();
        }
        if((isEven && isOddASC) || (!isEven && !isOddASC)){
                Terminal::color_bg(Terminal::CYAN);
        }
        else {
          Terminal::color_bg(Terminal::YELLOW);
        }
              cout << pieceString;
        Terminal::set_default();
        Terminal::color_fg(true, Terminal::BLACK); // make position number labels dark
              cout << (*it).second; // print position number labels on right side
        Terminal::set_default();
        cout << endl; // output newline
      }
      else { // every position not on very right or very left of board
        Terminal::color_fg(true, Terminal::BLACK);
	      if (piece && piece->is_white()){
	        Terminal::set_default();
	      }
        if((isEven && isOddASC) || (!isEven && !isOddASC)){
          Terminal::color_bg(Terminal::CYAN);
        }
        else {
          Terminal::color_bg(Terminal::YELLOW);
	      }
	      cout << pieceString;
	      Terminal::set_default();
      }
    }
    cout << " ";
    
    //Print out position letter labels at bottom of board
    for(char c = 'A'; c <= 'H'; c++){
	    Terminal::color_fg(true, Terminal::BLACK); // make labels bright
    	cout << c;
	    Terminal::set_default();
    }
    cout << endl;
  }     
  
  // Checks to make sure there is 1 white king piece and 1 black king piece
  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin(); it != occ.end(); it++) {
      if (it->second) {
	      switch (it->second->to_ascii()) {
	        case 'K':
	          white_king_count++;
	          break;
	        case 'k':
	          black_king_count++;
	          break;
	      }
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  //Clears the board
  int Board::clear_board(){
    for(std::map<Position, Piece*>:: const_iterator cit = occ.cbegin(); cit != occ.cend(); ++cit){
      delete (cit->second);
    }

    occ.clear();

    return 0;
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        const Piece* piece = board(Position(c, r));
              if (piece) {
          os << piece->to_ascii();
        } else {
          os << '-';
        }
      }
      os << std::endl;
    }
    return os;
  }
}

