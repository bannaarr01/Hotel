#ifndef HOTEL_HOTELUTIL_H
#define HOTEL_HOTELUTIL_H

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp> //calculate days difference
#include "../roomManager/RoomManager.h"
#include <algorithm>

//GLOBAL
//Utility helper functions for Hotel

//Accept reservation Date (checkIn - CheckOut) to get stay Duration
int reservationDiffDatesInDays(std::string const &s1, std::string const &s2);

//Accept date formatted as ("yyyy-mm-day") and subtract it from today's date, return int
int differenceDatesInDays(std::string const &s);

//Search Substring inside record
bool numberOfTimes(const std::string &searchName, const std::string &searchId, const std::string &line);

//Search Substring inside record
bool numberOfTimes(const std::string &searchTerm, const std::string &line);

//Get Int value of RoomAvailability Enum
int obtainRoomAvailabilityStatus(std::string &roomAvailabilityStatusStr);


//Get Int value of BedType Enum
int obtainBedType(std::string &bedTypeStr);


#endif //HOTEL_HOTELUTIL_H
