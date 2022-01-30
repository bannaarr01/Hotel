#ifndef HOTEL_UI_H
#define HOTEL_UI_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "../roomManager/room/Room.h"

class UI {
public:
    //Header
    static void header(const int totalWidth, const std::string title, const std::string range,
                       std::vector<std::string> listToDisplay);

    //Overall Menu Display
    static void Launch();

    //Guest Menu Display
    static void guestMenuDisplay();

    static void guestSubMenuDisplay();

    //Room Menu Display
    static void roomMenuDisplay();

    //Display Rooms in tabular format
    static void tabularDisplay(const std::vector<Room> &roomVec);

    //Display RoomUpdate Menu
    static void updateRoomMenuDisplay();

    //Display Reservation Menu
    static void reservationMenuDisplay();

    //Display subMenu for Reservation
    static void reservationSubMenuDisplay();

    //Reservation Options
    static void reservationOptionDisplay();

};


#endif //HOTEL_UI_H
