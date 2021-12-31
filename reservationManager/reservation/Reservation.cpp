#include "Reservation.h"

Reservation::Reservation(Room &room, std::string checkInDate, std::string checkOutDate,
                         int adultCount,
                         int childrenCount, Guest &guest)
        : room{room}, checkInDate{checkInDate}, checkOutDate{checkOutDate},
          adultCount{adultCount}, childrenCount{childrenCount}, guest{guest} {
    reservationNumber = boost::uuids::to_string(u); //auto generate uuid for new reservation
    reservationStatus = Reservation::ReservationStatus::WAIT_LIST;
}

std::string Reservation::getReservationNumber() const {
    return reservationNumber;
}

//void Reservation::setReservationNumber(std::string) {
//
//}

std::string Reservation::getCheckInDate() const {
    return checkInDate;
}

void Reservation::setCheckInDate(std::string checkInDate) {
    this->checkInDate = checkInDate;
}

std::string Reservation::getCheckOutDate() const {
    return checkOutDate;
}

void Reservation::setCheckOutDate(std::string checkOutDate) {
    this->checkOutDate = checkOutDate;
}

Reservation::ReservationStatus Reservation::getReservationStatus() const {
    return reservationStatus;
}

void Reservation::getReservationStatus(Reservation::ReservationStatus reservationStatus) {
    this->reservationStatus = reservationStatus;
}

bool Reservation::getIsCreditCardBilled() const {
    return isCreditCardBilled;
}

void Reservation::setCreditCardBilled(bool isCreditCardBilled) {
    this->isCreditCardBilled = isCreditCardBilled;
}

std::vector<Guest> Reservation::getGuests() const {
    return guests;
}

void Reservation::setGuests(std::vector<Guest> &guests) {
    this->guests = guests;
}

std::vector<Room> Reservation::getRooms() const {
    return rooms;
}

void Reservation::setRooms(std::vector<Room> &rooms) {
    this->rooms = rooms;
}

//std::vector<std::string> Reservation::getRoomNumber() {
//    return rooms.g
//}

//CreditCardDetails Reservation::getCreditCardDetails() {
//    return
//}

//void Reservation::setCreditCardDetails(CreditCardDetails) {
//
//}

Guest Reservation::addGuest() {
    return Guest{};
}

//void Reservation::removeGuest(Guest) {
//
//}

int Reservation::getAdultCount() const {
    return adultCount;
}

int Reservation::geChildrenCount() const {
    return childrenCount;
}

bool Reservation::getHasPaid() const {
    return hasPaid;
}

void Reservation::setHasPaid(bool hasPaid) {
    this->hasPaid = hasPaid;
}

//bool Reservation::getCreditCardBilled() const {
//    return isCreditCardBilled;
//}

//void Reservation::setCreditCardBilled(CreditCardDetails) {
//
//}

//void Reservation::removeRoom() {
//
//}


void Reservation::print(std::ostream &os) const {
    os << reservationNumber << "," << room << "," << checkInDate << "," << checkOutDate << "," << adultCount
       << "," << childrenCount << "," << guest << std::endl;

}
