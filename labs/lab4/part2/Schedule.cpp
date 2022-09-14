#include <iostream>
#include <map>
#include "Schedule.h"

using namespace std;

Schedule::Schedule(string name)
{
    mName = name;
}

bool Schedule::dropCourse(std::string name)
{
    // TO DO: if the course was not already in the map, return false
    // otherwise, remove it from the map and return true!
    if(courseMap.find(name) == courseMap.end()){
        return false;
    }
    else{
        courseMap.erase(name);
        return true;
    }

}

bool Schedule::addCourse(Course* c)
{
    // TO DO: if the course was already in the map, return false
    // otherwise, add it to the map and return true!
    if(courseMap.find(c->getCourseName()) != courseMap.end()){
        return false;
    }
    else{
        courseMap.insert(std::make_pair(c->getCourseName(), c));
        return true;
    }
    
}

void Schedule::printAllAssignments()
{
    // TO DO: print out the name of each course, followed by the set of assignments.
    // for each assignment, display its name, its type (essay vs hw vs exam), and whether or not it was completed.
    // formatting is up to you, but make sure it's easy to read!
    for(std::map<std::string, Course*>::iterator it = courseMap.begin(); it != courseMap.end(); ++it){
        Course c = *(it->second);
        cout << c.getCourseName() << endl;
        for(std::set<Assignment*>::iterator iter = c.getAssignmentSet().begin(); iter != c.getAssignmentSet().end(); ++iter){
            Assignment* a = *iter;
            
            cout << a->getName() << endl;
            cout << a->getType() << endl;
            
            if(a->isComplete()){
                cout << "Complete" << endl;
            }
            else{
                cout << "Not Complete" << endl;
            }
            
        }
    }
}

std::map<std::string, Course*> Schedule::getCourses()
{
    return courseMap;
}