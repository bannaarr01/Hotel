
#include "Reservation.h"

Reservation::Reservation(Room &room, std::string checkInDate, std::string checkOutDate,
                         int adultCount, int childrenCount, Guest &guest, std::string reservationNumber,
                         bool isCreditCardBilled,
                         bool hasPaid, ReservationStatus reservationStatus)
        : room{room}, checkInDate{checkInDate}, checkOutDate{checkOutDate}, adultCount{adultCount},
          childrenCount{childrenCount}, guest{guest}, reservationNumber{reservationNumber},
          isCreditCardBilled{isCreditCardBilled},
          hasPaid{hasPaid}, reservationStatus{reservationStatus} {
    //reservationNumber = boost::uuids::to_string(u); //auto generate uuid for new reservation
}


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

////            std::cout << r.roomNumber = roomNumber << ","
////               << r.roomAvailabilityStatus = roomAvailabilityStatusToString(roomAvailabilityStatus)
////               << "," << bedTypeToString(bedType) << "," << ((isWifiEnabled == 0) ? "No" : "Yes")
////               << "," << roomTypePtr->getRoomTypeName() << "," << roomTypePtr->getPrice() << ",";
////            for (auto &rsv: reservedDates) {
////                j["checkInDate"] = rsv.checkInDate;
////                j["checkOutDate"] = rsv.checkOutDate;
////            }
////            os << ",";
void Reservation::print(std::ostream &os) const {
    os << reservationNumber << "," << room.getRoomNumber() << ","
       << room.roomAvailabilityStatusToString(room.getRoomAvailabilityStatus()) << ","
       << room.bedTypeToString(room.getBedType()) << "," << ((room.getWifiEnabled() == 0) ? "No" : "Yes") << ","
       << room.getRoomType()->getRoomTypeName() << "," << room.getRoomType()->getPrice() << ","
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





