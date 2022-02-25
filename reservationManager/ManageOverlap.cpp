
#include "ManageOverlap.h"

// To create a new Interval Search Tree Node
mlp::IntervalNode *mlp::newNode(mlp::Interval value) {
    auto *temp = new mlp::IntervalNode;
    temp->value = new mlp::Interval(value);
    temp->max = value.high;
    temp->left = temp->right = nullptr;
    return temp;
}


mlp::IntervalNode *mlp::insert(mlp::IntervalNode *root, mlp::Interval value) {
    // Base case: Tree is empty, new node becomes root
    if (root == nullptr)
        return mlp::newNode(value);

    // Get low value of interval at root
    int l = root->value->low;

    // If root's low value is smaller, then new interval
    // goes to left subtree
    if (value.low < l)
        root->left = mlp::insert(root->left, value);

        // Else, new node goes to right subtree.
    else
        root->right = mlp::insert(root->right, value);

    // Update the max value of this ancestor if needed
    if (root->max < value.high)
        root->max = value.high;

    return root;
}

bool mlp::doIntervalOVerLap(mlp::Interval firstInterval, mlp::Interval secondInterval) {
    if (firstInterval.low < secondInterval.high && secondInterval.low < firstInterval.high)
        return true;
    return false;
}


mlp::Interval *mlp::overlapSearch(mlp::IntervalNode *root, mlp::Interval intValue) {
    // Base Case, tree is empty
    if (root == nullptr) return nullptr;

    // If given interval overlaps with root
    if (mlp::doIntervalOVerLap(*(root->value), intValue))
        return root->value;

    // If left child of root is present and max of left child
    // is greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (root->left != nullptr && root->left->max >= intValue.low)
        return mlp::overlapSearch(root->left, intValue);

    // Else interval can only overlap with right subtree
    return mlp::overlapSearch(root->right, intValue);
}


bool mlp::displayConflicting(std::vector<mlp::Interval> reservedDates) {
    // Create an empty Interval Search Tree, add first
    // reservedDates
    mlp::IntervalNode *root = nullptr;
    root = mlp::insert(root, reservedDates.at(0));

    // Process rest of the intervals
    for (int i = 1; i < reservedDates.size(); i++) {
        // If current reservation conflicts with any of the
        // existing intervals, display it
        mlp::Interval *res = mlp::overlapSearch(root, reservedDates[i]);
        if (res != nullptr) {
            std::cout << "\n\n" << boost::gregorian::from_undelimited_string(mlp::toString(reservedDates[i].low))
                      << " - "
                      << boost::gregorian::from_undelimited_string(mlp::toString(reservedDates[i].high))
                      << " \033[1;31mConflicts with Existing Reservation of[0m "
                      << boost::gregorian::from_undelimited_string(mlp::toString(res->low)) << " - "
                      << boost::gregorian::from_undelimited_string(mlp::toString(res->high)) << std::endl;
            return true;
        } else {
            //to_iso_extended_string(boost::gregorian::from_string("2022/02/07"))
            // Insert this reservation
            root = mlp::insert(root, reservedDates[i]);
        }
    }
    return false;
}

std::string mlp::toString(long &n) {
    std::string strVal{};
    std::stringstream ss{};
    ss << n;
    ss >> strVal;
    return strVal;
}