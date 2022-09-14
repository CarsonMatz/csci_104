#include "searcheng.h"
#include "combiners.h"


// Complete the necessary code
#include <set>
using namespace std;
//Constructors, don't need to do/initialize anything
AndWebPageSetCombiner::AndWebPageSetCombiner(){

}
OrWebPageSetCombiner::OrWebPageSetCombiner(){

}
DiffWebPageSetCombiner::DiffWebPageSetCombiner(){

}

WebPageSet AndWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB){
	//create new set to be returned
	WebPageSet setAnd;
	//iterate through setA
	for(set<WebPage*>::iterator it=setA.begin(); it != setA.end(); it++){
		//if the link is in setB and not in my final set, add it to the final set 
		if(setB.find(*it) != setB.end()){
			if(setAnd.find(*it) == setAnd.end()){
				setAnd.insert(*it);
			}
		}
	}
	//return my final set
	return setAnd;
}

WebPageSet OrWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB){
	//create new set to be returned
	WebPageSet setOr;
	//iterate through setA and add all its elements to the final set
	for(set<WebPage*>::iterator it=setA.begin(); it != setA.end(); it++){
		setOr.insert(*it);
	}
	//iterate through setB and add any links that are not already in the final set to the final set
	for(set<WebPage*>::iterator it=setB.begin(); it != setB.end(); it++){
		if(setOr.find(*it) == setOr.end()){
			setOr.insert(*it);
		}
	}
	//return my final set
	return setOr;
}

WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB){
	//create new set to be returned
	WebPageSet setDiff;
	//iterate through setA and add all its elements to the final set
	for(set<WebPage*>::iterator it=setA.begin(); it != setA.end(); it++){
		setDiff.insert(*it);
	}
	//iterate through setB and add remove any elemnts from the final set that occur in setB (only left with links in setA and not setB)
	for(set<WebPage*>::iterator it=setB.begin(); it != setB.end(); it++){
		if(setDiff.find(*it) != setDiff.end()){
			setDiff.erase(*it);
		}
	}
	//return my final set
	return setDiff;
}
