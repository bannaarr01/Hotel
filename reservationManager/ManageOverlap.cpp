
#include "ManageOverlap.h"

// To create a new Interval Search Tree Node
IntervalNode *newNode(Interval value) {
    IntervalNode *temp = new IntervalNode;
    temp->value = new Interval(value);
    temp->max = value.high;
    temp->left = temp->right = nullptr;
    return temp;
}


IntervalNode *insert(IntervalNode *root, Interval value) {
    // Base case: Tree is empty, new node becomes root
    if (root == nullptr)
        return newNode(value);

    // Get low value of interval at root
    int l = root->value->low;

    // If root's low value is smaller, then new interval
    // goes to left subtree
    if (value.low < l)
        root->left = insert(root->left, value);

        // Else, new node goes to right subtree.
    else
        root->right = insert(root->right, value);

    // Update the max value of this ancestor if needed
    if (root->max < value.high)
        root->max = value.high;

    return root;
}

bool doIntervalOVerLap(Interval firstInterval, Interval secondInterval) {
    if (firstInterval.low < secondInterval.high && secondInterval.low < firstInterval.high)
        return true;
    return false;
}


Interval *overlapSearch(IntervalNode *root, Interval intValue) {
    // Base Case, tree is empty
    if (root == nullptr) return nullptr;

    // If given interval overlaps with root
    if (doIntervalOVerLap(*(root->value), intValue))
        return root->value;

    // If left child of root is present and max of left child
    // is greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (root->left != nullptr && root->left->max >= intValue.low)
        return overlapSearch(root->left, intValue);

    // Else interval can only overlap with right subtree
    return overlapSearch(root->right, intValue);
}


void displayConflicting(std::vector<Interval> reservedDates) {
    // Create an empty Interval Search Tree, add first
    // reservedDates
    IntervalNode *root = nullptr;
    root = insert(root, reservedDates.at(0));

    // Process rest of the intervals
    for (int i = 1; i < reservedDates.size(); i++) {
        // If current reservation conflicts with any of the
        // existing intervals, display it
        Interval *res = overlapSearch(root, reservedDates[i]);
        if (res != nullptr)
            std::cout << boost::gregorian::from_undelimited_string(toString(reservedDates[i].low)) << " - "
                      << boost::gregorian::from_undelimited_string(toString(reservedDates[i].high))
                      << " \033[1;31mConflicts with Existing Reservation of[0m "
                      << boost::gregorian::from_undelimited_string(toString(res->low)) << " - "
                      << boost::gregorian::from_undelimited_string(toString(res->high)) << std::endl;
        //to_iso_extended_string(boost::gregorian::from_string("2022/02/07"))

        // Insert this reservation
        root = insert(root, reservedDates[i]);
    }
}

std::string toString(long int n) {
    auto strVal = boost::lexical_cast<std::string>(n);
    return strVal;
}