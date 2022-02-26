#ifndef HOTEL_HOTELUTIL_H
#define HOTEL_HOTELUTIL_H

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../roomManager/RoomManager.h"
#include <algorithm>

//GLOBAL
//Utility helper functions for Hotel

//Accept reservation Date (CheckOut- checkIn) to get stay Duration
int reservationDiffDatesInDays(std::string const &cInDate, std::string const &cOutDate);

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

//Get Int value of ReservationStatus Enum
int obtainReservationStatus(std::string &reservationStatusStr);

#endif //HOTEL_HOTELUTIL_H
