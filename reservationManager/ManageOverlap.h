#ifndef HOTEL_MANAGEOVERLAP_H
#define HOTEL_MANAGEOVERLAP_H

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>

namespace mlp {
// Structure to represent an interval
    struct Interval {
        long low, high;
    };

// Structure to represent a node in Interval Search Tree
    struct IntervalNode {
        Interval *value;
        long int max;
        IntervalNode *left, *right;
    };

// To create a new Interval Search Tree Node
    IntervalNode *newNode(Interval value);

// To insert a new Interval Search Tree
// Node - similar to BST Insert. Here the low value of interval is used to maintain BST property
    IntervalNode *insert(IntervalNode *root, Interval value);


// To check if two given intervals overlap
    bool doIntervalOVerLap(Interval firstInterval, Interval secondInterval);


// The main function that searches a given interval intValue in a given Interval Tree.
    Interval *overlapSearch(IntervalNode *root, Interval intValue);


//Display all conflicting reservation dates in a given vector of reserved dates.
    bool displayConflicting(std::vector<Interval> reservedDates);


    std::string toString(long &n);

}
#endif //HOTEL_MANAGEOVERLAP_H
