#include "cmdhandler.h"
#include "util.h"
using namespace std;

// Complete
QuitHandler::QuitHandler()
{

}

// Complete
QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

// Complete
Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

// Complete
PrintHandler::PrintHandler()
{

}

// Complete
PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";

}

// Complete
Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

// Add code for other handler class implementations below
IncomingHandler::IncomingHandler() {

}
IncomingHandler::IncomingHandler(Handler* next)
    : Handler(next) {

}
bool IncomingHandler::canHandle(const std::string& cmd) const {
    return cmd == "INCOMING";
}
Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    //bring in the page name from the input file and convert to string
    string name;
    instr >> name;
    //create a webpage pointer to the page associated with our file name
    WebPage* page = eng->retrieve_page(name);

    //if the page doesn't exist (retrieve_page returned NULL) return HANDLER_ERROR
    if (page == NULL) {
        return HANDLER_ERROR;
    }
    //otherwise
    else{
        //create a set of all the incoming links for our page
        WebPageSet inlinks = page->incoming_links();
        //display the number of hits (links in our set) to the ostream
        display_hits(inlinks, ostr);
        //return HANDLER_OK to complete
        return HANDLER_OK;
    }
}


OutgoingHandler::OutgoingHandler() {

}
OutgoingHandler::OutgoingHandler(Handler* next)
    : Handler(next) {

}
bool OutgoingHandler::canHandle(const std::string& cmd) const {
    return cmd == "OUTGOING";
}
Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    //bring in the page name from the input file and convert to string
    string name;
    instr >> name;
    //create a webpage pointer to the page associated with our file name
    WebPage* page = eng->retrieve_page(name);

    //if the page doesn't exist (retrieve_page returned NULL) return HANDLER_ERROR
    if (page == NULL) {
        return HANDLER_ERROR;
    }
    //otherwise
    else{
        //create a set of all the outgoing links for our page
        WebPageSet outlinks = page->outgoing_links();
        //display the number of hits (links in our set) to the ostream
        display_hits(outlinks, ostr);
        //return HANDLER_OK to complete
        return HANDLER_OK;
    }
}


AndHandler::AndHandler() {

}
AndHandler::AndHandler(Handler* next) 
    : Handler(next) {

}
bool AndHandler::canHandle(const std::string& cmd) const {
    return cmd == "AND";
}
Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    //declare a vector of strings to  be passed into the search function and a name string a single file
    std::vector<std::string> terms;
    string name;
    //read in the instr (full of file names/terms for the command) to the vector
    while(instr >> name){
        terms.push_back(name);
    }

    //create a WebPageSet and call the search function (which will generate a set of all the requisite webpages) using the AND combiner
    WebPageSetCombiner* aptr = new AndWebPageSetCombiner;
    WebPageSet final = eng->search(terms, aptr);

    //pass the final set and ostr to display_hits to be outputted
    display_hits(final, ostr);
    //cycle through the set of links and send them to the ostream to be displayed

    //return HANDLER_OK to complete
    return HANDLER_OK;
}


OrHandler::OrHandler() {

}
OrHandler::OrHandler(Handler* next) 
    : Handler(next) {

}
bool OrHandler::canHandle(const std::string& cmd) const {
    return cmd == "OR";
}
Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    //declare a vector of strings to  be passed into the search function and a name string a single file
    std::vector<std::string> terms;
    string name;
    //read in the instr (full of file names/terms for the command) to the vector
    while(instr >> name){
        terms.push_back(name);
    }

    //create a WebPageSet and call the search function (which will generate a set of all the requisite webpages) using the OR combiner
    WebPageSetCombiner* optr = new OrWebPageSetCombiner;
    WebPageSet final = eng->search(terms, optr);

    //pass the final set and ostr to display_hits to be outputted
    display_hits(final, ostr);
    

    //return HANDLER_OK to complete
    return HANDLER_OK;
}


DiffHandler::DiffHandler() {

}
DiffHandler::DiffHandler(Handler* next) 
    : Handler(next) {

}
bool DiffHandler::canHandle(const std::string& cmd) const {
    return cmd == "DIFF";
}
Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    //declare a vector of strings to  be passed into the search function and a name string a single file
    std::vector<std::string> terms;
    string name;
    //read in the instr (full of file names/terms for the command) to the vector
    while(instr >> name){
        terms.push_back(name);
    }

    //create a WebPageSet and call the search function (which will generate a set of all the requisite webpages) using the DIFF combiner
    WebPageSetCombiner* dptr = new DiffWebPageSetCombiner;
    WebPageSet final = eng->search(terms, dptr);

    //pass the final set and ostr to display_hits to be outputted
    display_hits(final, ostr);
    //cycle through the set of links and send them to the ostream to be displayed

    //return HANDLER_OK to complete
    return HANDLER_OK;
}























