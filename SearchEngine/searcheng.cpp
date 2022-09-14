#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "util.h"
using namespace std;

// Helper function that will extract the extension of a filename
std::string extract_extension(const std::string& filename);

std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}


// To be updated as needed 
SearchEng::SearchEng()
{

}

// To be completed
SearchEng::~SearchEng()
{
    parsers_.clear();
    terms_.clear();
    names_.clear();
}

// Complete
void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
    if (parsers_.find(extension) != parsers_.end())
    {
        throw std::invalid_argument("parser for provided extension already exists");
    }
    parsers_.insert(make_pair(extension, parser));
}

// Complete
void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

// To be completed
void SearchEng::read_page(const string& filename)
{

    string ext = extract_extension(filename);

    //throws logic error if no parser for file extension
    if(parsers_.find(ext) == parsers_.end()){
        throw std::logic_error("no parser registered for the file's extension");
    }
    //open the file name
    ifstream ifile(filename.c_str());
    //if the page does not exist (is not in the name/page map) throw invalid argument
    if(ifile.fail()){
        throw std::invalid_argument("page_name does not exist");
    }
    
    //create string sets for outgoing links and search terms
    StringSet outgoingLinks;
    StringSet searchTerms;

    //parse the page using the proper parser
    std::map<std::string, PageParser*>::const_iterator parser_it = parsers_.find(ext);
    parser_it->second->parse(ifile, searchTerms, outgoingLinks);

    //if the page does not exist, create and initialize a new page, add it to the map of name/pages
    if(names_.find(filename) == names_.end()){
        WebPage* npage = new WebPage;
        npage->filename(filename);
        names_.insert(make_pair(filename, npage));
    }
    //now it  exists regardles so assign it to a WebPage* to work with
    std::map<std::string, WebPage*>::iterator page_it = names_.find(filename);
    WebPage* page = page_it->second;

    //update the search terms for the page
    page->all_terms(searchTerms);

    //for loop to run through all the search terms
    for(StringSet::iterator term_it = searchTerms.begin(); term_it != searchTerms.end(); ++term_it){
        //if the term does not already exist in my term/webpage set map, create a new set with the page and add that set/term to the terms map
        if(terms_.find(*term_it) == terms_.end()){
            WebPageSet* nset = new WebPageSet;
            nset->insert(page);
            terms_.insert(make_pair(*term_it, *nset));
        }
        //otherwise, add it to the webpage set for the given term
        else{
            std::map<std::string, WebPageSet>::iterator set_it = terms_.find(*term_it);
            if(set_it->second.find(page) == set_it->second.end()){
                set_it->second.insert(page);
            }
        }
    }

    //for loop to run through the outgoing links
    for(StringSet::iterator link_it = outgoingLinks.begin(); link_it != outgoingLinks.end(); ++link_it){
        //if the page the link points at does not exist, create a new page and add it to the name/page map
        //update the incoming link of the new page to the current page and outgoing link of the current page to the new one
        if(names_.find(*link_it)==names_.end()){
            WebPage* outpage = new WebPage;
            outpage->filename(*link_it);
            names_.insert(make_pair(*link_it, outpage));
            outpage->add_incoming_link(page);
            page->add_outgoing_link(outpage);
        }
        else{
            std::map<std::string, WebPage*>::iterator outpage_it = names_.find(*link_it);
            outpage_it->second->add_incoming_link(page);
            page->add_outgoing_link(outpage_it->second);
        }
    }


}

// To be completed
WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
    //find the map item of the (names, pages) map associated with the page_name
    std::map<std::string, WebPage*>::const_iterator it = names_.find(page_name);
    //if the page doesn't exit, return null
    if(it==names_.end()){
        return NULL;
    }
    //otherwise return the second item of the map (the WebPage*)
    else{
        return it->second;
    }

}

// To be completed
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
    //if the page does not exist (is not in the name/page map) throw invalid argument
    if(names_.find(page_name) == names_.end()){
        throw std::invalid_argument("page_name does not exist");
    }
    //gets the extension of the page and throws logic error if no parser exists for the extensions
    string ext = extract_extension(page_name);
    if(parsers_.find(ext) == parsers_.end()){
        throw std::logic_error("no parser registered for the file's extension");
    }

    //create an iterator to point at the appropriate map item for the parser associated with the given page's extension
    std::map<std::string, PageParser*>::const_iterator it = parsers_.find(ext);
    //open the page, convert string page_name to appropriate istream type
    ifstream ifile(page_name.c_str());
    //call display text for the second element of the iterator (the PageParser*), send it to the ostream
    ostr << it->second->display_text(ifile);
}

// To be completed
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{
    //if no terms are provided, return an empty set
    if(terms.size() == 0){
        WebPageSet empty;
        return empty;
    }
    //if one term is provided
    else if(terms.size() == 1){
        //create an iterator to the term/page set map item for that term and return the corresponding WebPageSet
        std::map<std::string, WebPageSet>::const_iterator it = terms_.find(terms[0]);
        return it->second;
    }
    else{
        //create an iterator to go through the user-inputted terms and a string that converts the term to a base form
        std::vector<std::string>::const_iterator term_it = terms.begin();
        string t = conv_to_lower(*term_it);
        //create an iterator to the term/page set map item for the term, create a webpage set equal to the one for the first term
        std::map<std::string, WebPageSet>::const_iterator page_it = terms_.find(t);
        WebPageSet outSet = page_it->second;
        //move on the the second term provided
        ++term_it;
        //iterate through the whole vector of terms
        while(term_it != terms.end()){
            //standardize the term
            t = conv_to_lower(*term_it);
            //create webpage set equal to the one for that term
            page_it = terms_.find(t);
            WebPageSet setB = page_it->second;
            //combine our final, overall set with the one for the new term using the proper combiner
            outSet = combiner->combine(outSet, setB);
            //move to the next term
            ++term_it;
        }
        //return the final webpage set
        return outSet;
    }

}

// Add private helper function implementations here

