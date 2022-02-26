#ifndef HOTEL_UI_H
#define HOTEL_UI_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include "../roomManager/room/Room.h"
#include "../reservationManager/reservation/Reservation.h"
#include <boost/date_time/gregorian/gregorian.hpp>

class UI {
public:
//=======================UI HEADER========================================================================
    //Header
    static void header(const int totalWidth, const std::string title, const std::string range,
                       std::vector<std::string> listToDisplay);
//========================END OF UI HEADER=================================================================



//========================MAIN MENU UI=====================================================================
    //Overall Menu Display
    static void Launch();
//========================END OF MAIN MENU UI==============================================================



//========================GUEST UI=========================================================================
    //Guest Menu Display
    static void guestMenuDisplay();

    //Guest SubMenu Display
    static void guestSubMenuDisplay();

    //Existing Guest?
    static void existingGuestDisplay();
//========================END OF GUEST UI==================================================================


//========================ROOM UI==========================================================================
    //Room Menu Display
    static void roomMenuDisplay();

    //Display RoomUpdate Menu
    static void updateRoomMenuDisplay();

    //Display Rooms in tabular format
    static void tabularDisplay(const std::vector<Room> &roomVec);

//========================END OF ROOM UI===================================================================


//========================RESERVATION UI===================================================================
    //Display Reservation Menu
    static void reservationMenuDisplay();

    //Display subMenu for Reservation
    static void reservationSubMenuDisplay();

    //Manage Existing Reservation
    static void reservationManagementDisplay();

    //Display Rooms in tabular format
    static void reservationTabularDisplay(const std::set<Reservation> &reservationSet);
    //Reservation Options
//========================RESERVATION UI===================================================================
};


#endif //HOTEL_UI_H
