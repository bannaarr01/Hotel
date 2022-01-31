
#include "Reservation.h"

Reservation::Reservation(std::vector<Room> &rooms, std::string checkInDate, std::string checkOutDate,
                         int adultCount, int childrenCount, std::vector<Guest> &guests)
        : rooms{rooms}, checkInDate{checkInDate}, checkOutDate{checkOutDate}, adultCount{adultCount},
          childrenCount{childrenCount}, guests{guests} {
    reservationNumber = boost::uuids::to_string(u); //auto generate uuid for new reservation
    reservationStatus = Reservation::ReservationStatus::WAIT_LIST;
}


void Reservation::print(std::ostream &os) const {
    os << reservationNumber << ",";
    for (const auto &r: rooms) {
        os << r;
        os << ",";
    }
    os << checkInDate << "," << checkOutDate << "," << reservationStatus
       << "," << adultCount
       << "," << childrenCount << ",";
    for (const auto &g: guests) {
        os << g;
        os << ",";
    }


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

std::vector<Room> Reservation::getRooms() const {
    return rooms;
}

std::vector<Guest> Reservation::getGuests() const {
    return guests;
}

void Reservation::addRoom(Room &room) {
    rooms.emplace_back(room);
}

bool Reservation::operator==(const Reservation &rhs) const {
    return this->reservationNumber == rhs.reservationNumber;
}




