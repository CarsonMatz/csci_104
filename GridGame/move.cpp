#include "move.h"


// Complete
Move::Move(Board* board)
{
    m.first = Vehicle::INVALID_ID;
    m.second = 0;
    b = board;
    g = 0;
    h = 0;
    prev = NULL;
}

// To be completed
Move::Move(const Board::MovePair& move, Board* board,  Move *parent)
{
	m = move;
    b = board;
    g = parent->g + 1;
    h = 0;
    prev = parent;
}

// To be completed
Move::~Move()
{

}

// To be completed
bool Move::operator<(const Move& rhs) const
{
	//f score is g+h
	//if lhs f does not equal rhs f, return result of lhs f < rhs f (if lhs f is less then true, if rhs is less then false)
	if((this->g + this->h) != (rhs.g + rhs.h)){
		return (this->g + this->h) < (rhs.g + rhs.h);
	}
	//otherwise the f scores are equal
	//if the h scores are not equal, return result of lhs h < rhs h
	else if(this->h != rhs.h){
		return this->h != rhs.h;
	}
	//if both f and h are equal, return result of lhs board < rhs board (compares the size of the boards)
	else{
		return this->b < rhs.b;
	}
}

// To be completed
void Move::score(Heuristic *heur) 
{
	h = heur->compute( *(this->b) );
}
