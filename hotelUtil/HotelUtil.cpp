#include "HotelUtil.h"


//Accept reservation Date (checkIn - CheckOut) to get stay Duration
int reservationDiffDatesInDays(std::string const &cInDate, std::string const &cOutDate) {
    using namespace boost::gregorian;
    //creating 2 date Objects
    date chkInDate{from_undelimited_string(cInDate)};
    date chkOutDate{from_undelimited_string(cOutDate)};

    // Get the Duration between 2 Dates
    date_duration dur = chkOutDate - chkInDate;
    int duration = static_cast<int>(dur.days());

    return duration;
}

//Accept date formatted as ("yyyy-mm-day") and subtract it from today's date, return int
int differenceDatesInDays(std::string const &s) {
    using namespace boost::gregorian;
    //day_clock::universal_day()//from_string(s)//day_clock::local_day()
    auto diff = (from_undelimited_string(s) - day_clock::universal_day()).days();

    return static_cast<int>(diff);
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
    else if (reservationStatusStr == "Checked Out")
        result = 4;

    return result;
}