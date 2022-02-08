
#include "Reservation.h"

Reservation::Reservation(Room &room, std::string checkInDate, std::string checkOutDate,
                         int adultCount, int childrenCount, Guest &guest, bool isCreditCardBilled,
                         bool hasPaid, ReservationStatus reservationStatus, const std::string &reservationNumber)
        : room{room}, checkInDate{checkInDate}, checkOutDate{checkOutDate}, adultCount{adultCount},
          childrenCount{childrenCount}, guest{guest}, isCreditCardBilled{isCreditCardBilled},
          hasPaid{hasPaid}, reservationStatus{reservationStatus}, reservationNumber{boost::uuids::to_string(u)} {
    //reservationNumber = boost::uuids::to_string(u); //auto generate uuid for new reservation
}

//Reservation::Reservation(std::vector<Room> &rooms, std::string checkInDate, std::string checkOutDate,
//                         int adultCount, int childrenCount, std::vector<Guest> &guests)
//        : rooms{rooms}, checkInDate{checkInDate}, checkOutDate{checkOutDate}, adultCount{adultCount},
//          childrenCount{childrenCount}, guests{guests} {
//    reservationNumber = boost::uuids::to_string(u); //auto generate uuid for new reservation
//    reservationStatus = Reservation::ReservationStatus::WAIT_LIST;
//}


//void Reservation::print(std::ostream &os) const {
//    os << reservationNumber << ",";
//    for (const auto &r: rooms) {
//        os << r;
//        os << ",";
//    }
//    os << checkInDate << "," << checkOutDate << "," << reservationStatus
//       << "," << adultCount
//       << "," << childrenCount << ",";
//    for (const auto &g: guests) {
//        os << g;
//        os << ",";
//    }
//
//
//}

std::string Reservation::reservationStatusToString(Reservation::ReservationStatus reservationStatus) const {
    std::string result;
    switch (reservationStatus) {
        case Reservation::ReservationStatus::WAIT_LIST:
            result = "Wait List";
            break;
        case Reservation::ReservationStatus::CHECKED_IN:
            result = "Checked In";
            break;
        case Reservation::ReservationStatus::CONFIRMED:
            result = "Confirmed";
            break;
        case Reservation::ReservationStatus::CHECKED_OUT:
            result = "Checked Out";
            break;
    }
    return result;
}

void Reservation::print(std::ostream &os) const {
    os << reservationNumber << "," << room << ","
       << checkInDate << "," << checkOutDate << "," << reservationStatusToString(reservationStatus)
       << "," << adultCount << "," << childrenCount << "," << guest << "," << isCreditCardBilled << "," << hasPaid
       << std::endl;
}

std::string Reservation::getReservationNumber() const {
    return reservationNumber;
}

std::string Reservation::getCheckInDate() const {
    return checkInDate;
}


Reservation::ReservationStatus Reservation::getReservationStatus() const {
    return reservationStatus;
}

//std::vector<Room> Reservation::getRooms() const {
//    return rooms;
//}

Room Reservation::getRoom() const {
    return room;
}

//std::vector<Guest> Reservation::getGuests() const {
//    return guests;
//}
Guest Reservation::getGuest() const {
    return guest;
}

//void Reservation::addRoom(Room &room) {
//    rooms.emplace_back(room);
//}
void Reservation::addRoom(Room &room) {
    this->room = room;
}

bool Reservation::operator==(const Reservation &rhs) const {
    return this->guest == rhs.guest;
}

bool Reservation::operator<(const Reservation &rhs) const {
    return this->reservationNumber < rhs.reservationNumber;
}

std::string Reservation::getCheckOutDate() const {
    return checkOutDate;
}

bool Reservation::getHasPaid() const {
    return hasPaid;
}

int Reservation::getAdultCount() const {
    return adultCount;
}

int Reservation::getChildrenCount() const {
    return childrenCount;
}





