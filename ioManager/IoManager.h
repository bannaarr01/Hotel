#ifndef HOTEL_IOMANAGER_H
#define HOTEL_IOMANAGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <functional>
#include "../ui/UI.h"
#include "../guestManager/guest/Guest.h"
#include "../roomManager/room/Room.h"
//#include "../hotelUtil/HotelUtil.h"
#include "../reservationManager/reservation/Reservation.h"
#include "../exception/InvalidEntryException.h"
#include <boost/date_time/gregorian/gregorian.hpp>


class IoManager {
//All input and Output method will be here
public:
    //Accept range of valid input and also accept a void function (UI) to display and return valid selection made
    int inputValidation(const int rangeFrom, const int to, std::function<void()> func);

    int inputValidationV2(const int rangeFrom, const int to);

    Guest askInputToCreateNewGuest();

    Room askInputAndCreateNewRoom();

    std::string validateDate(const std::string &title);

    Reservation askInputToMakeReservation();
};


#endif //HOTEL_IOMANAGER_H
