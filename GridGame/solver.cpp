#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "solver.h"

using namespace std;

// To be completed
Solver::Solver(const Board& b, Heuristic *heur)
: b_(b), heur_(heur)
{

}

// To be completed
Solver::~Solver()
{

}

// To be completed
bool Solver::run()
{
    return !solution_.empty();
}

// To be completed
Board::MovePairList Solver::solution() const
{
	/*open_list.push(Start State)
	while(open_list is not empty)
	1. s ← remove min. f-value state from open_list
	(if tie in f-values, select one w/ larger g-value)
	2. Add s to closed list
	3a. if s = goal node then trace path back to start; STOP!
	3b. Generate successors/neighbors of s, compute their f
	values, and add them to open_list if they are
	not in the closed_list (so we don’t re-explore), or
	if they are already in the open list, update them if
	they have a smaller f value*/


	Board::MovePairList open_list = b_.potentialMoves();
	Board::MovePairList closed_list;
	while( !open_list.empty() ){
		Board::MovePair move = open_list.back();
		open_list.pop_back();
		size_t f = heur_->compute(b_);
	}
    // Avoid compiler warnings - replace this
    return Board::MovePairList();
}

// Complete
size_t Solver::numExpansions() const
{
    return expansions_;
}
