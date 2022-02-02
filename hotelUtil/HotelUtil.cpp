#include "HotelUtil.h"


//Accept reservation Date (checkIn - CheckOut) to get stay Duration
int reservationDiffDatesInDays(std::string const &s1, std::string const &s2) {
    //creating 2 date Objects
    boost::gregorian::date checkInDate{boost::gregorian::from_string(s1)};
    boost::gregorian::date checkOutDate{boost::gregorian::from_string(s2)};

    // Get the Duration between 2 Dates
    boost::gregorian::date_duration dur = checkOutDate - checkInDate;
    int duration = dur.days();

    return duration;
}

//Accept date formatted as ("yyyy-mm-day") and subtract it from today's date, return int
int differenceDatesInDays(std::string const &s) {
    using namespace boost::gregorian;
    return (day_clock::local_day() - from_string(s)).days();
}


//Search Record
bool numberOfTimes(const std::string &searchName, const std::string &searchId, const std::string &line) {
    std::size_t foundName = line.find(searchName);
    std::size_t foundId = line.find(searchId);
    if (foundName == std::string::npos && foundId == std::string::npos)
        return false;
    else
        return true;
}

//Overload
bool numberOfTimes(const std::string &searchTerm, const std::string &line) {
    std::size_t foundTerm = line.find(searchTerm);
    if (foundTerm == std::string::npos)
        return false;
    else
        return true;
}

//Get Int value of RoomAvailability Enum
int obtainRoomAvailabilityStatus(std::string &roomAvailabilityStatusStr) {
    int result{};
    if (roomAvailabilityStatusStr == "Vacant")
        result = 1;
    else if (roomAvailabilityStatusStr == "Occupied")
        result = 2;
    else if (roomAvailabilityStatusStr == "Reserved")
        result = 3;
    else if (roomAvailabilityStatusStr == "Under Maintenance")
        result = 4;
    return result;
}


//Get Int value of BedType Enum
int obtainBedType(std::string &bedTypeStr) {
    int result{};
    if (bedTypeStr == "Single")
        result = 1;
    else if (bedTypeStr == "Double")
        result = 2;
    else if (bedTypeStr == "Master")
        result = 3;

    return result;
}


//Get Int value of ReservationStatus Enum
int obtainReservationStatus(std::string &reservationStatusStr) {
    int result{};
    if (reservationStatusStr == "Wait List")
        result = 1;
    else if (reservationStatusStr == "Confirmed")
        result = 2;
    else if (reservationStatusStr == "Checked In")
        result = 3;
    else if (reservationStatusStr == "Expired")
        result = 4;

    return result;
}