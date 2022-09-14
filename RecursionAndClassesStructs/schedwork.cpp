

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool valid(const size_t maxShifts, const unsigned int worker, const DailySchedule& sched);
bool scheduleHelper(unsigned int day, unsigned int col,
    const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    for(unsigned int i=0; i<avail.size(); ++i){
        vector<Worker_T> temp;
        for(unsigned int j=0; j<dailyNeed; ++j){
            temp.push_back(INVALID_ID);
        }
        sched.push_back(temp);
    }
    return scheduleHelper(0, 0, avail, dailyNeed, maxShifts, sched);
}

bool valid(const size_t maxShifts, const unsigned int worker, const DailySchedule& sched)
{
    //if they aren't available, return false
    /*if(avail[day][worker] == 0){
        return false;
    }*/
    //check all the people scheduled, count number of times specific worker is scheduled
    unsigned int m=0, c=0;
    for(unsigned int i = 0; i < sched.size(); ++i){
        for(unsigned int j = 0; j < sched[i].size(); ++j){
            if(sched[i][j] == worker){
                m++;
                c++;
            }
        }
        //if one worker is scheduled twice on the same day, return false
        if(c>1){
            return false;
        }
        c=0;
    }
    //if worker is scheduled more than the max shifts, not valid
    if(m > maxShifts){
        return false;
    }
    //otherwise valid
    return true;
}

bool scheduleHelper(unsigned int day, unsigned int col,
    const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched)
{
    //if the day is equal to the number of rows in avail, we have gone through all rows and can return true
    if(day == avail.size()){
        return true;
    }

    //this row of the sched is full for now, move on to the next
    if(col == dailyNeed){
        return scheduleHelper(day+1, 0, avail, dailyNeed, maxShifts, sched);
    }
    //if the spot in the schedule is empty
    else if(sched[day][col] == INVALID_ID){
        //go through all the workers
        for(unsigned int i=0; i<avail[day].size(); ++i){
            //if the worker is available on that day
            if(avail[day][i] == 1){
                sched[day][col] = i;
                //make sure they are valid in the schedule
                if(valid(maxShifts, i, sched)){
                    //move through to next spot
                    if(scheduleHelper(day, col+1, avail, dailyNeed, maxShifts, sched)){
                        return true;
                    }
                }
            }
        }
        //that track didn't work out, so reset and backtrack
        sched[day][col] = INVALID_ID;
    }
    return false;
    //otherwise, spot in sched was filled already so go to next
    /*else{
        return scheduleHelper(day, col+1, avail, dailyNeed, maxShifts, sched);
    }*/
}

