// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
//recursive function
void generateWords(int length, int currentSize, int blanks, std::string s, std::string floating,
    const std::set<std::string>& dict, std::set<std::string>& possibilities);
//function that genereates a copy of a string but removes a character
std::string deleteChar(const std::string& string, char c);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    //create a variation of in that isn't constant for me to modify
    std::string s = in;
    std::string f = floating;
    int size = s.size();
    //set to store list of word options
    std::set<std::string> results;
    //find the number of blanks in a string
    int blanks = 0;
    for(auto c : s){
        if(c == '-'){
            blanks++;
        }
    }
    //call the recursion
    generateWords(size, 0, blanks, s, f, dict, results);
    //return the list of options
    return results;
}

// Define any helper functions here
void generateWords(int length, int currentSize, int blanks, std::string s, std::string floating,
    const std::set<std::string>& dict, std::set<std::string>& possibilities)
{
    //if you have fewer blank spaces than floats that have to go in them, the word will not work so quit
    if(blanks < floating.size()){
        return;
    }

    //if whole word(s) has been run through, done with this recursive branch
    if(currentSize == length){
        //if all floating letters were used and the word is in the dictionary, it's good to be added
        if(floating.size() == 0 && dict.find(s) != dict.end()){
            if(possibilities.find(s) == possibilities.end()){
                possibilities.insert(s);
            }
        }
        return;
    }

    //if spot in string is a blank
    if(s[currentSize] == '-'){
        for(char c = 'a'; c <= 'z'; c++){
            s[currentSize] = c;
            //if the character is one of the floatings, recurse but remove the char from the list of floats
            if(floating.find(c) != floating.npos){
                string f = deleteChar(floating, c);
                generateWords(length, currentSize + 1, blanks - 1, s, f, dict, possibilities);
            }
            //otherwise just recurse and normally but still subtract a blank
            else{
                generateWords(length, currentSize + 1, blanks - 1, s, floating, dict, possibilities);
            }
        }
    }
    //otherwise recurse to next letter, do not subtract from blanks
    else{
        generateWords(length, currentSize + 1, blanks, s, floating, dict, possibilities);
    }
}

std::string deleteChar(const std::string& string, char c)
{
    std::string s = string;
    s.erase(s.find(c), 1);
    return s;
}