#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;

// To be completed
void MDParser::parse(std::istream& istr, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // Complete your code below
    // Initialize the current term and link as empty strings.
    string term = "";
    string link = "";

    // Get the first character from the file.
    char c = istr.get();
    char prev = c;

    // Continue reading from the file until input fails.
    while(!istr.fail()){
        //check to see if c is the start of a link
        if(c=='(' && prev==']'){
            //update c to be the first char of the link
            c = istr.get();
            //go until hitting the end of the link
            while(c != ')'){
                //add the char to the link and then get the next char
                link += c;
                prev = c;
                c = istr.get();
            }
            //if we have alink to add, add it
            if(link != ""){
                allOutgoingLinks.insert(link);
                
            }
            link = "";
        }
        //check if c is a character to split terms but not start a link
        else if (!isalnum(c)){
            // If we have a term to add, convert it to a standard case and add it
            if(term != ""){
                term = conv_to_lower(term);
                allSearchableTerms.insert(term);
            }
            term = "";
        }
        // Otherwise we continually add to the end of the current term.
        else{
            term += c;
        }
        //Update prev
        prev = c;
        // Attempt to get another character from the file.
        c = istr.get();
    }
    // Since the last term in the file may not have punctuation, there may be a valid term in
    // the "term" variable, so we need to insert it into the allSearchableTerms set.
    if(term != "")
    {
        term = conv_to_lower(term);
        allSearchableTerms.insert(term);
    }
}

// To be completed
std::string MDParser::display_text(std::istream& istr)
{
    std::string retval = "";
    char c = istr.get();
    char prev = c;
    // Continue reading from the file until input fails.
    while (!istr.fail()) {
        //make sure not to print links
        if(c=='(' && prev==']'){
            while(c != ')' && !istr.fail()){
                prev = c;
                c = istr.get();
            }
            c = istr.get();
        }
        if(!istr.fail()){
            retval += c;
            prev = c;
            c = istr.get();
        }
    }
    return retval;

}


