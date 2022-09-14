#include <cmath>
#include "heur.h"
#include <vector>
#include <set>
using namespace std;

// Complete
size_t BFSHeuristic::compute(const Board& b)
{
    return 0U;
}


// To be completed
size_t DirectHeuristic::compute(const Board& b)
{
	//h is the h score to be returned, will update as obstacles are encountered
	size_t h = 0;
	//create a variable for the 'a' vehicle trying to escape
	Vehicle v = b.escapeVehicle();
	//check all the spaces on the board to the right of the 'a' vehicle
	for(int i = v.startc + v.length; i < b.size(); i++){
		//if the space does not equal an invalid vehicle id, then it is a vehicle in the way
		if(b.at(v.startr, i) != Vehicle::INVALID_ID){
			h++;
		}
	}
    return h;
}

// To be completed
size_t IndirectHeuristic::compute(const Board& b)
{
	//create a variable for the 'a' vehicle trying to escape
	Vehicle a = b.escapeVehicle();
	//set to store the ids of the vehicles directly blocking 'a' and set for all blocckers(direct and indiriect)s, only want to store vehicles once
	std::set<Vehicle::VID_T> blockers;
	std::set<Vehicle::VID_T> direcBlockers;
	//check all the spaces on the board to the right of the 'a' vehicle
	for(int i = a.startc + a.length; i < b.size(); i++){
		//if the space does not equal an invalid vehicle id, then it is a vehicle in the way and its id must be added to the lists
		if(b.at(a.startr, i) != Vehicle::INVALID_ID){
			if(direcBlockers.find(b.at(a.startr, i)) == direcBlockers.end())
			direcBlockers.insert( b.at(a.startr, i) );
		}
	}

	//add all the direct blockers to the set of total blockers
	blockers = direcBlockers;

	//iterate through the set of direct blockers and evaluate the vehicles blocking them
	for(std::set<Vehicle::VID_T>::iterator it = direcBlockers.begin(); it != direcBlockers.end(); ++it){
		//get the vehicle associated with the vehicle id
		Vehicle v = b.vehicle(*it);
		//integers to represent how far up or down the vehicle would have to move to free 'a' 
		int up = a.startr - (v.startr + v.length);
		int down = a.startr - v.startr + 1;
		//the final decision on the amount to move, set as up to begin, change if v cannot move up
		int amount = up;
		//bools for whether the the vehicle can move up or down and stay on the board
		bool moveUp = true;
		bool moveDown = true;
		//if the start position plus the move in the up direction is less than 0, it's not viable
		if(v.startr + up < 0){
			moveUp = false;
			amount = down;
		}
		//if the down move takes the end of the vehicle off the board, it's not a viable move
		if(v.startr + down + v.length - 1 >= b.size()){
			moveDown = false;
		}
		//indirect blocking vehicles only count if the direct vehicle only has one viable path to clear 'a'
		//(i.e. one but not both of up and down are true)
		if(moveUp != moveDown){
			//check to make sure the move is not already legal (i.e. there's a vehicle blocking the path)
			if( !b.isLegalMove(*it, amount) ){
				//make sure amount is positive now
				if(amount < 0){
					amount *= -1;
				}
				//now we know the vehicle can only move in one direction (up or down) but is being blocked by another vehicle
				//move through the entire length of the move amount, add any new indirect blocking vehicles to the set
				for(int i = 1; i <= amount; i++){
					if((v.startr - i < 0) || (v.startr + v.length + i >= b.size())){
						break;
					}
					//if it's moving up and the board space above that's being explored is a vehicle
					if(moveUp && b.at(v.startr - i, v.startc) != Vehicle::INVALID_ID){
						//it the vehicle is not in the set already, add it
						if( blockers.find(b.at(v.startr - i, v.startc)) == blockers.end() ){
							blockers.insert( b.at(v.startr - i, v.startc) );
						}
					}
					//if it's moving down and the board space below that's being explored is a vehicle
					else if(moveDown && b.at(v.startr + v.length + i - 1, v.startc) != Vehicle::INVALID_ID){
						//it the vehicle is not in the set already, add it
						if( blockers.find(b.at(v.startr + v.length + i - 1, v.startc)) == blockers.end() ){
							blockers.insert( b.at(v.startr + v.length + i - 1, v.startc) );
						}
					}
				}
			}
		}
	}

	//return the total number of blockers (direct + indirect)
    return blockers.size();
}

